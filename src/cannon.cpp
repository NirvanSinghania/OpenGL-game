#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    timer = 0;
    release = 0;
    accy = 0;
   
    sp_x =0, sp_z =0;
    angle = 0;

    const float side_length = 4.0f;
    static const GLfloat vertex_buffer_data[] = {

          side_length,-side_length,-side_length,
         side_length, side_length, side_length,
         side_length,-side_length, side_length,
        
         side_length, side_length, side_length,
         side_length, side_length,-side_length,
        -side_length, side_length,-side_length,
        
         side_length, side_length, side_length,
        -side_length, side_length,-side_length,
        -side_length, side_length, side_length,
        
         side_length, side_length, side_length,
        -side_length, side_length, side_length,
         side_length,-side_length, side_length,

        
        -side_length,-side_length,-side_length,
        -side_length, side_length, side_length,
        -side_length, side_length,-side_length,
        
         side_length,-side_length, side_length,
        -side_length,-side_length, side_length,
        -side_length,-side_length,-side_length,
        
        -side_length, side_length, side_length,
        -side_length,-side_length, side_length,
         side_length,-side_length, side_length,
        
         side_length, side_length, side_length,
         side_length,-side_length,-side_length,
         side_length, side_length,-side_length, 


        -side_length,-side_length,-side_length,
        -side_length,-side_length, side_length,
        -side_length, side_length, side_length,

         side_length, side_length,-side_length,
        -side_length,-side_length,-side_length,
        -side_length, side_length,-side_length,
        
         side_length,-side_length, side_length,
        -side_length,-side_length,-side_length,
         side_length,-side_length,-side_length,
        
         side_length, side_length,-side_length,
         side_length,-side_length,-side_length,
        -side_length,-side_length,-side_length
        

    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    this->position.x -= sp_x*sin(angle);
    this->position.z -= sp_x*cos(angle);
    this-> timer += 1;
    if(this->timer > 120){
        sp_z = 0;
        release = 0;
        timer = 0;
    }
}


void Cannon::shoot(float _theta){
    sp_x = 12.0f;
    angle = _theta;
}

bounding_box_t Cannon::bounding_box() {

    bounding_box_t bbox = { this->position.x, this->position.y, this->position.z, 8, 8, 8 };
    return bbox;
}
