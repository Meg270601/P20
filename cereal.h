#ifndef CEREAL_H
#define CEREAL_H

#include <QObject>

class Cereal : public QObject
{
    Q_OBJECT
public:
    Cereal();
    void cerealiser(int x, int y);
    void decerealiser(int bin[]);

signals:
    void out(int x, int y);
    void clear_out();

public slots:
    void in(int x, int y);
    void clear_screen();

private:
    int bin[32];
    int x = 0;
    int y = 0;

};

#endif // CEREAL_H
