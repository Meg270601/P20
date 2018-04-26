#include "cereal.h"
#include <QDebug>

Cereal::Cereal()
{
}

void Cereal::cerealiser(int x, int y) {
    for (int i = 0; i < 16; i++) {
        bin[i] = (x >> i) & 1;
        qDebug() << bin[i];
    }
    for (i = 0; i < 16; i++) {
        bin[i+16] = (y >> i) &1;
        qDebug() << bin[i+16];
    }
}

void Cereal::decerealiser(int bin) {
    for (int i = 0; i < 16; i++) {
        x += bin[i] * pow(2, i);
    }
    for (int i = 0; i < 16; i++) {
        y += bin[i+16] * pow(2, i);
    }
}

void Cereal::draw(int x, int y) {
    cerealiser(x, y);
}

void Cereal::clear_screen() {

}
