#include <QApplication>
#include <QDebug>
#include <QObject>
#include <pthread.h>
#include <wiringPi.h>
#include <queue>
#include <iostream>
#include "send.h"
#include "receiver.h"
#include "cereal.h"
#include <safe_queue.h>
#include <decereal.h>

#include <QMutex>

void delay(int n);
void* send(void* thread_arg);
void* receive(void* thread_arg);

typedef struct _thread_data_t{
    int thread_id;
    Receiver r;
    Send s;
    Cereal c;
    DeCereal d;

}t_data;


int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI

    QApplication a(argc, argv);
    t_data data;

    data.s.setWindowTitle("Send");
    data.s.show();

    data.r.setWindowTitle("Receive");
    data.r.show();

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


    qDebug() << "Send thread " << tid << "started.";
    QObject::connect(&my_data->s, SIGNAL(clear_screen()),
                     &my_data->c, SLOT(clear_screen()));
    QObject::connect(&my_data->s, SIGNAL(draw(int,int)),
                         &my_data->c, SLOT(in(int,int)));
    while(1){

    }
    //
    //queue serial data. W
    // end thread
    pthread_exit(NULL);
}

void* receive(void* thread_arg)
{
    long tid = (long)2;
    t_data* my_data;
    int i;
    int bin[32];
    my_data = static_cast<t_data*>(thread_arg); // the structure data is now stored as my_data in this thread. This is the name used to access variables inside the struct.
    qDebug() << "Receive thread " << tid << "started." ;
    QObject::connect(&my_data->d, SIGNAL(clear_out()),
                    &my_data->r, SLOT(clear_screen()));

    QObject::connect(&my_data->d, SIGNAL(out(int,int)),
                   &my_data->r, SLOT(draw(int,int)));

    while (1) {
        i = 0;
        while (my_data->c.get_pin(4) == 1) {
            if (my_data->c.get_pin(0) == 1) {
                my_data->c.set_pin(1, 1);
                while (my_data->c.get_pin(0) == 1);
                my_data->c.set_pin(1, 0);
                bin[i] = my_data->c.get_pin(2);
            }
            i++;
            if (i > 32) qDebug() << "Exception!";
        }
    }

    // end thread
    pthread_exit(NULL);
}

