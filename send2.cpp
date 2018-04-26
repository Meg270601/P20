#include "send2.h"
#include "ui_send.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>

std::vector<int> pointsx;
std::vector<int> pointsy;

Send::Send(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Send)
{
    ui->setupUi(this);
}

Send::~Send()
{
    delete ui;
}

void Send::mouseMoveEvent(QMouseEvent * cursor)
{
    // get click position
    qDebug() << "Mouse x " << cursor->x() << " Mouse y " << cursor->y();
    pointsy.push_back(cursor->y());
    pointsx.push_back(cursor->x());
    update();
}
void Send::paintEvent(QPaintEvent * event)
{
   qDebug() << "painting";
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
