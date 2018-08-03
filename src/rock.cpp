#include "rock.h"
#include "main.h"

Rock::Rock(float x, float y, float z, float size, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->size = size;
   
    const int n = 180;
    const int reqd = n*9;
    GLfloat vertex_buffer_data[reqd] = {};

    double angle =0;
    const double pi = 4*atan(1);
    double diff = (2*pi)/(double)n;
    int cur =0;
    rock_collision = 0;
    health_affect = (rand()%5)+1;


    for (unsigned int i=0; i<n ;i++)
    {
        //Origin
        vertex_buffer_data[cur++]=0.0;
        vertex_buffer_data[cur++]= 6.0; 
        vertex_buffer_data[cur++]=0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++]=size*cos(angle);
        vertex_buffer_data[cur++]= 0.0f;

        vertex_buffer_data[cur++]=size*sin(angle);
        

        //Point with higher angle
        angle+= diff;
        vertex_buffer_data[cur++]=size*cos(angle);
        vertex_buffer_data[cur++]= 0.0f;

        vertex_buffer_data[cur++]=size*sin(angle);
    }

    this->object = create3DObject(GL_TRIANGLES, reqd/3,  vertex_buffer_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rock::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

