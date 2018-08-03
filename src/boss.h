#include "main.h"

#ifndef Boss_H
#define Boss_H


class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z,  color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
    void kill();
    float speed;
    float movx;
    float movz;
    float size;
    float height;
    bool alive ;
    int life_left;

private:
    VAO *object;
    VAO *object1;

};

#endif // Boss_H
    