#ifndef CEREAL_H
#define CEREAL_H

#include <QObject>
#include <safe_queue.h>
#include <QMutex>

class Cereal : public QObject
{
    Q_OBJECT
public:
    Cereal();
    void cerealiser(int x, int y);
    void decerealiser(int bin[]);
    int get_coord(int x);
    SafeQueue<int> coords;
    int get_pin(int i);
    void set_pin(int i, int x);

signals:
    void out(int x, int y);
    void clear_out();

public slots:
    void in(int x, int y);
    void clear_screen();

private:
    int bin[32];
    int handshake();
    int x = 0;
    int y = 0;
    bool pins[5];
    QMutex Mutex;

};

#endif // CEREAL_H
