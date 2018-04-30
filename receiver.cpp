#include "receiver.h"
#include "ui_receive.h"
#include <safe_queue.h>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>

Receiver::Receiver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receive)
{
    ui->setupUi(this);
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::paintEvent(QPaintEvent * event)
{
    qDebug() << "painting r";
    QPainter painter(this);
    QPen pen;
    QFont font;
    QColor color;
    color.black();
    font.setPixelSize(30);
    pen.setWidth(4);
    pen.setColor(color);
    painter.setPen(pen);
    painter.setFont(font);
    for (int i = 0; i < pointsx.size(); i++) {
        painter.drawPoint(pointsx[i], pointsy[i]);
    }
}

void Receiver::add_x(int x) {
    pointsx.push_back(x);
}

void Receiver::add_y(int y) {
    pointsy.push_back(y);
}

void Receiver::draw(int x, int y) {
    pointsx.push_back(x);
    pointsy.push_back(y);
    update();
}

void Receiver::clear_screen() {
    pointsx.clear();
    pointsy.clear();
    update();
}
