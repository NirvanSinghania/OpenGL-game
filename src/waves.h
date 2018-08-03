#include "main.h"

#ifndef Waves_H
#define Waves_H


class Waves {
public:
    Waves() {}
    Waves(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    bool has_boat_hit;
    void set_hit_for_boat();
   
private:
    VAO *object;
};

#endif // Waves_H
