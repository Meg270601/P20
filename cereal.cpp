#include "cereal.h"
//#include <safe_queue.h>
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
   new_packet = 1;
    //decerealiser(bin);
}

void Cereal::in(int x, int y) {
    cerealiser(x, y);
}

void Cereal::clear_screen() {
    //clear screen is encoded as 10000
    cerealiser(10000, 10000);
}
int Cereal::get_packet(){
    return new_packet;
}
void Cereal::set_packet(int x){
    new_packet = x;
}
