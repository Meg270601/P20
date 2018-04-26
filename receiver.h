#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>

namespace Ui {
class Receiver;
}

class Receiver : public QWidget
{
    Q_OBJECT

public:
    explicit Receiver(QWidget *parent = 0);
    ~Receiver();
    void add_x(int x);
    void add_y(int y);

public slots:
    void draw(int x, int y);

private:
    Ui::Receiver *ui;
    std::vector<int> pointsx;
    std::vector<int> pointsy;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // RECEIVER_H
