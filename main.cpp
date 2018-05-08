#include <QApplication>
#include <QDebug>
#include <QObject>
#include <pthread.h>
#include <wiringPi.h>
#include <queue>
#include <iostream>
#include "send.h"
#include "receive.h"
#include "cereal.h"
//#include <safe_queue.h>
#include <decereal.h>

#include <QMutex>

void delay(int n);
void* send(void* thread_arg);
void* receive(void* thread_arg);

typedef struct _thread_data_t{
    int thread_id;
    //Receive r;
   // Send s

    //Cereal c;
   // DeCereal d;
    bool pins[5];
}t_data;

QMutex Mutex;

int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI

    QApplication a(argc, argv);
    t_data data;
/*
    data.s.setWindowTitle("Send");
    data.s.show();

    data.r.setWindowTitle("Receive");
    data.r.show();
*/
    // starting worker thread(s)
    int rc;
    int sc;
    pthread_t send_thread;
    pthread_t receive_thread;

    sc = pthread_create(&send_thread, NULL, send, static_cast<void*>(&data));
    if (sc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }
    rc = pthread_create(&receive_thread, NULL, receive, static_cast<void*>(&data));
    if (rc) {
        qDebug() << "Unable to start receive thread.";
        exit(1);
    }
   // pthread_join(send_thread,NULL);
    //pthread_join(receive_thread,NULL);
    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}

void* send(void* thread_arg)
{
    long tid = (long)1;
    t_data* my_data;
    my_data = static_cast<t_data*>(thread_arg);
    Send s;
    Cereal c;
    s.setWindowTitle("Send");
    s.show();

    qDebug() << "Send thread " << tid << "started.";
    QObject::connect(&s, SIGNAL(clear_screen()),
                     &c, SLOT(clear_screen()));
    QObject::connect(&s, SIGNAL(draw(int,int)),
                         &c, SLOT(in(int,int)));

    while(1){
        while (c.new_packet == 1) {
            Mutex.lock();
            my_data->pins[4] = 1;
            Mutex.unlock();
        //  qDebug() << "starting transmission";
            for (int i = 0; i < 32; i++) {
                Mutex.lock();
                my_data->pins[2] = bin[i];
                my_data->pins[0] = 1;
                Mutex.unlock();
               // qDebug() << "handshake1";
                while (my_data->pins[1] == 0);
                Mutex.lock();
                my_data->pins[0] = 0;
                Mutex.unlock();
                while (my_data->pins[1] == 1);
            }
            Mutex.lock();
            my_data->pins[4] = 0;
            Mutex.unlock();
        }
    }

    //queue serial data.
    // end thread
    pthread_exit(NULL);
}

void* receive(void* thread_arg)
{
    DeCereal d;
    long tid = (long)2;
    t_data* my_data;
    int i;
    Receive r;
    int bin[32];
    my_data = static_cast<t_data*>(thread_arg); // the structure data is now stored as my_data in this thread. This is the name used to access variables inside the struct.
    qDebug() << "Receive thread " << tid << "started." ;

    r.setWindowTitle("Receive");
    r.show();

    QObject::connect(&d, SIGNAL(clear_out()),
                    &r, SLOT(clear_screen()));

    QObject::connect(&d, SIGNAL(out(int,int)),
                   &r, SLOT(draw(int,int)));

    while (1) {
        i = 0;
        Mutex.lock();
        while (my_data->pins[4] == 1) {
            if (my_data->pins[0] == 1) {
                Mutex.lock();
                bin[i] = my_data->pins[2];
                my_data->pins[1] = 1;
                Mutex.unlock();
//                qDebug() << "handshake2";
                while (my_data->pins[0] == 1);
                Mutex.lock();
                my_data->pins[1] = 0;
                Mutex.unlock();
                i++;
            }
            if (i > 32) qDebug() << "Exception!";
        }
        d.decerealiser(bin);
    }

    // end thread
    pthread_exit(NULL);
}

