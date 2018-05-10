#ifndef Receive_H
#define Receive_H

#include <QWidget>
#include <QObject>

namespace Ui {
class Receive;
}

class Receive : public QWidget
{
    Q_OBJECT

public:
    explicit Receive(QWidget *parent = 0);
    ~Receive();
    void add_x(int x);
    void add_y(int y);

public slots:
    void draw(int x, int y);
    void clear_screen();

private:
    Ui::Receive *ui;
    std::vector<u_int16_t> pointsx;
    std::vector<u_int16_t> pointsy;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // Receive_H
