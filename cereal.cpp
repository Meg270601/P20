#include "cereal.h"
#include <safe_queue.h>
#include <QDebug>
#include <cmath>
#include <array>
#include <QTimer>

void delay(int n);

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
//    for (int i = 0; i < 32; i++) {
//        coords.enqueue(bin[i]); //adds serial data to queue.
//    }

    while (pins[4] == 0);
    pins[0] = 1;
    while(pins[4] == 1);
    pins[0] = 0;
    while (pins[1] == 0);
    for (int i = 0; i < 32; i++) {
        pins[2] = bin[i];
    }
    pins[0] = 1;
    pins[0] = 0;
    while (pins[1] == 0);
    //decerealiser(bin);
}

void Cereal::in(int x, int y) {
    cerealiser(x, y);
}

void Cereal::clear_screen() {
    //clear screen is encoded as 10000
    cerealiser(10000, 10000);
}
int Cereal::get_coord(int x){
    return(bin[x]);
}

void Cereal::toggle() {
    pins[4] = ~pins[4];
}
