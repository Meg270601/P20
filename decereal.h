#ifndef DECEREAL_H
#define DECEREAL_H
#include <QObject>
class DeCereal : public QObject
{
    Q_OBJECT
public:
    DeCereal();

    void decerealiser(int bin[]);

private:

    int x = 0;
    int y = 0;
signals:
    void clear_out();
};


#endif // DECEREAL_H
