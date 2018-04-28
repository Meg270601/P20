#include "cereal.h"
#include <QDebug>
#include <cmath>
#include <array>

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
    decerealiser(bin);
}

void Cereal::decerealiser(int bin[32]) {
    x = 0;
    y = 0;
    for (int i = 0; i < 16; i++) {
        x += (bin[i] * pow(2, i));
    }
    for (int i = 0; i < 16; i++) {
        y += (bin[i+16] * pow(2, i));
    }
    qDebug() << x << " " << y;
    //clear screen is encoded as 10000
    if (x == 10000 & y == 10000) {
        clear_out();
    }
    out(x, y);
}

void Cereal::in(int x, int y) {
    cerealiser(x, y);
}

void Cereal::clear_screen() {
    //clear screen is encoded as 10000
    cerealiser(10000, 10000);
}
