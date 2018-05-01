#ifndef DECEREAL_H
#define DECEREAL_H
#include <QObject>
class DeCereal : public QObject
{
    Q_OBJECT
public:
    DeCereal();
    int handshake(bool pins[]);
    void decerealiser(int bin[]);

private:
    int x = 0;
    int y = 0;
signals:
    void out(int x, int y);
    void clear_out();
};


#endif // DECEREAL_H
