#ifndef SEND_H
#define SEND_H

#include <QMainWindow>
#include "ui_send.h"

class Send : public QWidget, private Ui::Send
{
    Q_OBJECT

public:
    explicit Send(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent * cursor);
    void paintEvent(QPaintEvent *event);
};

#endif // SEND_H
