#include "main.h"

#ifndef Wind_H
#define Wind_H


class Wind {
public:
    Wind() {}
    Wind(float speed,float acc);
    void start();
    void move();
    float  speedx;
    float speedz;
    float accx;
    float accz;
    bool  windon;
    int  duration;
    int  curcount ;
private:
    VAO *object;
};

#endif // Wind_H