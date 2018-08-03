#include "main.h"

#ifndef Enemy_H
#define Enemy_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z,  color_t color);
    glm::vec3 position;
    float rotation;
    float speed;
    float movx;
    float movz;
    float size;
    float height;
    float  temp;
    float tempspeed;
    bool alive ;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    bounding_box_t bounding_box();
  
  

private:
    VAO *object;
    VAO *object1;

};

#endif // Enemy_H
    