#include "decereal.h"
//#include <safe_queue.h>
#include <QDebug>
#include <cmath>
#include <array>

DeCereal::DeCereal()
{
}


void DeCereal::decerealiser(int bin[32]) {
    x = 0;
    y = 0;
    for (int i = 0; i < 16; i++) {
        x += (bin[i] * pow(2, i));
    }
    for (int i = 0; i < 16; i++) {
        y += (bin[i+16] * pow(2, i));
    }
//    qDebug() << x << " " << y;
    //clear screen is encoded as 10000
    if ((x == 10000) & (y == 10000)) {
        clear_out();
    }
    out(x,y);

}

int DeCereal::handshake(bool pins[]) {
    qDebug() << "handshake2";
    if (pins[0] == 1) {
        pins[1] = 1;
        while (pins[0] == 1);
        pins[1] = 0;
        return 0;
    }
    return 1;
}

