#include "decereal.h"
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

