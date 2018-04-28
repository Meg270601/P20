#include <QApplication>
#include <QDebug>
#include <QObject>
#include <pthread.h>
#include <wiringPi.h>

#include "send.h"
#include "receiver.h"
#include "cereal.h"

void* send(void* thread_id);
void* receive(void* thread_id);

int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);
    Send s;
    s.setWindowTitle("Send");
    s.show();
    Receiver r;
    r.setWindowTitle("Receive");
    r.show();
    Cereal c;

    QObject::connect(&s, SIGNAL(draw(int,int)),
                     &c, SLOT(in(int,int)));
    QObject::connect(&c, SIGNAL(out(int,int)),
                     &r, SLOT(draw(int,int)));
    QObject::connect(&s, SIGNAL(clear_screen()),
                     &c, SLOT(clear_screen()));
    QObject::connect(&c, SIGNAL(clear_out()),
                     &r, SLOT(clear_screen()));

    // starting worker thread(s)
    int rc;
    int sc;
    pthread_t send_thread;
    pthread_t receive_thread;
    sc = pthread_create(&send_thread, NULL, send, (void*)1);
    if (sc) {
        qDebug() << "Unable to start send thread.";
        exit(1);
    }
    rc = pthread_create(&receive_thread, NULL, receive, (void*)2);
    if (rc) {
        qDebug() << "Unable to start send thread.";
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

void* send(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Send thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}

void* receive(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Receive thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}
