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
    int get_x(int i);
    int get_y(int i);
//    int count = 0;

signals:
    void draw(int x, int y);
    void clear_screen();

private:
    Ui::Send *ui;
    std::vector<u_int16_t> pointsx;
    std::vector<u_int16_t> pointsy;
private slots:
    void on_clear_screen_button_clicked();

protected:
    void mouseMoveEvent(QMouseEvent * cursor);
    void paintEvent(QPaintEvent *event);

};

#endif // SEND_H
