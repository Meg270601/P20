#ifndef CEREAL_H
#define CEREAL_H

class Cereal
{
public:
    Cereal();
    void cerealiser(int x, int y);
    void decerealiser(int bin);

public slots:
    void draw(int x, int y);
    void clear_screen();

private:
    int bin[32];

};

#endif // CEREAL_H
