#include "cereal.h"
#include <safe_queue.h>
#include <QDebug>
#include <cmath>
#include <array>
#include <QMutex>


Cereal::Cereal()
{
}

void Cereal::cerealiser(int x, int y) {
    for (int i = 0; i < 16; i++) {
        bin[i] = (x >> i) & 1;
    }
    for (int i = 0; i < 16; i++) {
        bin[i+16] = (y >> i) &1;
    }

    pins[4] = 1;
    for (int i = 0; i < 32; i++) {
        if (!handshake()) {
        pins[2] = bin[i];
        qDebug() <<"handshake1";
        }
    }
    pins[4] = 0;

    //decerealiser(bin);
}

void Cereal::in(int x, int y) {
    cerealiser(x, y);
}

void Cereal::clear_screen() {
    //clear screen is encoded as 10000
    cerealiser(10000, 10000);
}

int Cereal::handshake() {
    pins[0] = 1;
    while (pins[1] == 0);
    pins[0] = 0;
    return 0;
}
int Cereal::get_pin(int i){
    Mutex.lock();
    qDebug() << "lock";
    int x = pins[i];
    Mutex.unlock();
    qDebug() << "unlock";
    return x;

}
void Cereal::set_pin(int i,int x){
    Mutex.lock();
    qDebug() << "lock";
    pins[i] = x;
    Mutex.unlock();
    qDebug() << "unlock";
}
