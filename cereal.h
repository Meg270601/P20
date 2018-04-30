#ifndef CEREAL_H
#define CEREAL_H

#include <QObject>
#include <safe_queue.h>

class Cereal : public QObject
{
    Q_OBJECT
public:
    Cereal();
    void cerealiser(int x, int y);
    void decerealiser(int bin[]);
    int get_coord(int x);
    SafeQueue<int> coords;
    bool pins[5];

signals:
    void out(int x, int y);
    void clear_out();

public slots:
    void in(int x, int y);
    void clear_screen();
    void toggle();

private:
    int bin[32];


    int x = 0;
    int y = 0;

};

#endif // CEREAL_H
