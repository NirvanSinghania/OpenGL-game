#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this-> speed = 0.1f;
    this-> movx = (rand()%3)-1;
    this-> movz = (rand()%3)-1;
    this -> size = 7.0f ;
    height = 7.0f;
    this -> alive = 1;
    this -> life_left = 5;
    

     float vertex_buffer_data[] = {
        -7.0f,-7.0f,-7.0f,
        -7.0f,-7.0f, 7.0f,
        -7.0f, 7.0f, 7.0f,
         7.0f, 7.0f,-7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f,-7.0f,
         7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f,-7.0f,
         7.0f,-7.0f,-7.0f,
         7.0f, 7.0f,-7.0f,
         7.0f,-7.0f,-7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f,-7.0f,
         7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f, 7.0f,
        -7.0f,-7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
        -7.0f,-7.0f, 7.0f,
         7.0f,-7.0f, 7.0f,
         7.0f, 7.0f, 7.0f,
         7.0f,-7.0f,-7.0f,
         7.0f, 7.0f,-7.0f,
         7.0f,-7.0f,-7.0f,
         7.0f, 7.0f, 7.0f,
         7.0f,-7.0f, 7.0f,
         7.0f, 7.0f, 7.0f,
         7.0f, 7.0f,-7.0f,
        -7.0f, 7.0f,-7.0f,
         7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f,-7.0f,
        -7.0f, 7.0f, 7.0f,
         7.0f, 7.0f, 7.0f,
        -7.0f, 7.0f, 7.0f,
         7.0f,-7.0f, 7.0f,

         


         0.0f, 7.0f, 0.0f,
         0.0f,  20.0f, 0.0f,
         7.0f, 7.0f, -7.0f,

          0.0f, 7.0f, 0.0f,
         0.0f,  20.0f, 0.0f,
         7.0f, 7.0f, 7.0f,

          0.0f, 7.0f, 0.0f,
         0.0f,  20.0f, 0.0f,
         -7.0f, 7.0f, -7.0f,

          0.0f, 7.0f, 0.0f,
         0.0f,  20.0f, 0.0f,
         -7.0f, 7.0f, 7.0f
    };
  
   

    this->object = create3DObject(GL_TRIANGLES, 4*9+12,  vertex_buffer_data, color, GL_FILL);



   
}

void Boss::draw(glm::mat4 VP ) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
   

}
void Boss::tick()
{
     this->position.x += speed*this->movx;
     this->position.z += speed*this->movz;

}
bounding_box_t Boss::bounding_box() {
    float _x = this->position.x, _y = this->position.y, _z = this->position.z;
    bounding_box_t bbox = { _x, _y, _z, this->size, this->size, this->size};
    return bbox;
}
void Boss::kill()
{
    
    (this-> life_left)--;
    if (this->life_left <=0)
        alive = 0;
}


void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}