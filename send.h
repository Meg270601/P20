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
    int count = 0;

signals:
    void draw(int x, int y);

private:
    Ui::Send *ui;
    std::vector<int> pointsx;
    std::vector<int> pointsy;
private slots:
    void on_pushButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent * cursor);
    void paintEvent(QPaintEvent *event);

};

#endif // SEND_H
