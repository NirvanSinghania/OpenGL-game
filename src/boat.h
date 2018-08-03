#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float speed;
    float speedy;
    float accy;
    float health;
   
    bool collide ;
    bool alive;
    int points, mon_killed ;
    void jump();
    void upd_health(float val);
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void tick_on_wind(float _x,float _y);
    void move_left();
    void move_right();
    void move_back(float angle);
    void move_front(float angle);
    void kill();
   

private:

    
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    
    
   
};

#endif // BOAT_H
