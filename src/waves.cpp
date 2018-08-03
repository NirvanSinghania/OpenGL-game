#include "waves.h"
#include "main.h"

Waves::Waves(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    int total_vertices = 6;
    has_boat_hit =1 ;
    static const GLfloat vertex_buffer_data[] =
     {
         0.0, 0.01, 0.0,
        0.0, 0.01,-5.0,
        100.0, 0.01, 10.0,

        0.0, 0.01, 0.0,
        0.0, 0.01,-5.0,
       -100.0, 0.01, 10.0
     

      
    };
    this->object = create3DObject(GL_TRIANGLES, total_vertices, vertex_buffer_data, color, GL_FILL);
}
void Waves::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Waves::set_position(float _x, float _y, float _z)
{
    this->position = glm::vec3(_x, _y, _z);
}
void Waves::set_hit_for_boat()
{
    has_boat_hit = 1;
}
