#include <QApplication>
#include <QDebug>

#include <pthread.h>
#include <wiringPi.h>

#include "send.h"
#include "receiver.h"
#include "cereal.h"

void* send(void* thread_id);

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
                     &r, SLOT(draw(int,int)));
    QObject::connect(&s, SIGNAL(draw(int,int)),
                     &c, SLOT(draw(int,int)));
    QObject::connect(&s, SIGNAL(clear_screen()),
                     &r, SLOT(clear_screen()));

    // starting worker thread(s)
    int rc;
    pthread_t send_thread;
    rc = pthread_create(&send_thread, NULL, send, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
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
    qDebug() << "Worker thread " << tid << "started.";

    // end thread
    pthread_exit(NULL);
}
