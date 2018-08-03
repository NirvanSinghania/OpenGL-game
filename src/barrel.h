#include "main.h"

#ifndef Barrel_H
#define Barrel_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z,  color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    float speed;
    int movx,movz;
    bool hasgift;
    float size;
    float height;

private:
    VAO *object;
    VAO *object1;

};

#endif // Barrel_H
