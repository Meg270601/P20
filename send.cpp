#include "send.h"
#include "ui_send.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <vector>

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
//    qDebug() << "Mouse x " << cursor->x() << " Mouse y " << cursor->y();
    pointsy.push_back(cursor->y());
    pointsx.push_back(cursor->x());
    update();
    draw(cursor->x(), cursor->y());

}
void Send::paintEvent(QPaintEvent * event)
{
//   qDebug() << "painting s";
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
    //painter.drawLine(pointsx[i], pointsy[i], pointsx[i-1], pointsy[i-1]);
       painter.drawPoint(pointsx[i], pointsy[i]);
   }
}

void Send::on_clear_screen_button_clicked()
{
    pointsx.clear();
    pointsy.clear();
    clear_screen();
    update();
}
