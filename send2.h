#ifndef SEND_H
#define SEND_H

#include <QWidget>

namespace Ui {
class Send;
}

class Send : public QWidget
{
    Q_OBJECT

public:
    explicit Send(QWidget *parent = 0);
    ~Send();

private:
    Ui::Send *ui;

protected:
    void mouseMoveEvent(QMouseEvent * cursor);
    void paintEvent(QPaintEvent *event);
};

#endif // SEND_H
