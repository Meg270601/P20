#ifndef RECEIVER_H
#define RECEIVER_H

#include <QWidget>
#include <QObject>

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
    void clear_screen();

private:
    Ui::Receive *ui;
    std::vector<u_int16_t> pointsx;
    std::vector<u_int16_t> pointsy;

protected:
    void paintEvent(QPaintEvent *event);
/*
private slots:
    void on_exit_button_clicked();*/
};

#endif // RECEIVER_H
