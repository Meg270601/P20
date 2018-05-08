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
//#include <safe_queue.h>
#include <decereal.h>

#include <QMutex>

void delay(int n);
void* send(void* thread_arg);
void* receive(void* thread_arg);
void set_pin(int i, int x);
int get_pin(int i);
bool pins[5];
QMutex Mutex2;

struct s_data{
    int thread_id;
    Send s;
    Cereal c;
};
struct r_data{
    int thread_id;
    Receiver r;
    DeCereal d;
};



int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI

    QApplication a(argc, argv);
    s_data s_data;
    r_data r_data;

    s_data.s.setWindowTitle("Send");
    s_data.s.show();

    r_data.r.setWindowTitle("Receive");
    r_data.r.show();

    // starting worker thread(s)
    int rc;
    int sc;
    pthread_t send_thread;
    pthread_t receive_thread;

    sc = pthread_create(&send_thread, NULL, send, static_cast<void*>(&s_data));
    if (sc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }
    rc = pthread_create(&receive_thread, NULL, receive, static_cast<void*>(&r_data));
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
    s_data* my_data;
    my_data = static_cast<s_data*>(thread_arg);


    qDebug() << "Send thread " << tid << "started.";
    QObject::connect(&my_data->s, SIGNAL(clear_screen()),
                     &my_data->c, SLOT(clear_screen()));
    QObject::connect(&my_data->s, SIGNAL(draw(int,int)),
                         &my_data->c, SLOT(in(int,int,bool[])));
    while(my_data->c.get_packet()){
        Mutex2.lock();
        pins[4] = 1;
        Mutex2.unlock();
    //    qDebug() << "starting transmission";
        for (int i = 0; i < 32; i++) {
            Mutex2.lock();
            pins[2] = my_data->c.bin[i];
            pins[0] = 1;
            Mutex2.unlock();
    //        qDebug() << "handshake1";
            while (pins[1] == 0);
            Mutex2.lock();
            pins[0] = 0;
            Mutex2.unlock();
            while (pins[1] == 1);
        }
        my_data->c.set_packet(0);
        Mutex2.lock();
        pins[4] = 0;
        Mutex2.unlock();
    }
    //
    //queue serial data. W
    // end thread
    pthread_exit(NULL);
}

void* receive(void* thread_arg)
{
    long tid = (long)2;
    r_data* my_data;
    int i;
    int bin[32];
    my_data = static_cast<r_data*>(thread_arg); // the structure data is now stored as my_data in this thread. This is the name used to access variables inside the struct.
    qDebug() << "Receive thread " << tid << "started." ;
    QObject::connect(&my_data->d, SIGNAL(clear_out()),
                    &my_data->r, SLOT(clear_screen()));

    QObject::connect(&my_data->d, SIGNAL(out(int,int)),
                   &my_data->r, SLOT(draw(int,int)));

    while (1) {
        i = 0;
        while (get_pin(4) == 1) {
            if (get_pin(0) == 1) {
                bin[i] = get_pin(2);
                set_pin(1, 1);
//                qDebug() << "handshake2";
                while (get_pin(0) == 1);
                set_pin(1, 0);
                i++;
            }
            if (i > 32) qDebug() << "Exception!";
        }
        my_data->d.decerealiser(bin);
    }

    // end thread
    pthread_exit(NULL);
}
int get_pin(int i){
    Mutex2.lock();
//    qDebug() << "lock";
   int x = pins[i];
   Mutex2.unlock();
//   qDebug() << "unlock";
    return x;

}
void set_pin(int i,int x){
    Mutex2.lock();
//    qDebug() << "lock";
    pins[i] = x;
    Mutex2.unlock();
//    qDebug() << "unlock";
}

