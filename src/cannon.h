#include "main.h"

#ifndef Cannon_H
#define Cannon_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float angle;
    float sp_x;
    float sp_z;
    float accy;
    int release;
    int timer;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void shoot(float angle);
   
 
    bounding_box_t bounding_box();


private:
    VAO *object;
};

#endif // Cannon_H
