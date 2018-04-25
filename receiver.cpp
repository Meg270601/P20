#include "receiver.h"
#include "ui_receiver.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

Receiver::Receiver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::paintEvent(QPaintEvent * event)
{
   /*QPainter painter(this);
   QPen pen;
   QFont font;
   font.setPixelSize(30);
   pen.setWidth(4);
   painter.setPen(pen);
   painter.setFont(font);*/
}
