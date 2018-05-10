#include "receive.h"
#include "ui_receive.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>

Receive::Receive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Receive)
{
    ui->setupUi(this);
}

Receive::~Receive()
{
    delete ui;
}

void Receive::paintEvent(QPaintEvent * event)
{
//    qDebug() << "painting r";
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
    for (u_int i = 0; i < pointsx.size(); i++) {
      //  painter.drawLine(pointsx[i], pointsy[i], pointsx[i-1], pointsy[i-1]);
        painter.drawPoint(pointsx[i], pointsy[i]);
    }
}

void Receive::draw(int x, int y) {
    pointsx.push_back(x);
    pointsy.push_back(y);
    update();
}

void Receive::clear_screen() {
    pointsx.clear();
    pointsy.clear();
    update();
}
