#include "enemy.h"
#include "main.h"

Enemy::Enemy(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this -> temp = y;
    this-> speed = 0.1f;
    this -> tempspeed = 0.1f;
    this-> movx = (rand()%3)-1;
    this-> movz = (rand()%3)-1;
    this -> size = (rand()%4)+4 ;
    height = (rand()%6)+ 18.0f;
    this -> alive = 1;

    
  
    const int n = 20;
    const int reqd = n*9;
    GLfloat vertex_buffer_data[2*reqd] = {};

    double angle =0;
    const double pi = 4*atan(1);
    double diff = (2*pi)/(double)n;
    int cur =0;

    if (rand()%2)
    {
    for (unsigned int i=0;i<n;i++)
    {
        //Origin
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 10.0; 
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = size*cos(angle);
        vertex_buffer_data[cur++] =  0.0f;

        vertex_buffer_data[cur++] = size*sin(angle);
        

        //Point with higher angle
        angle+= diff;
        vertex_buffer_data[cur++]=size*cos(angle);
        vertex_buffer_data[cur++]= 0.0f;

        vertex_buffer_data[cur++]=size*sin(angle);

        angle-= diff;
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = -10.0; 
        vertex_buffer_data[cur++] = 0.0f;

        //Point with lower angle
        vertex_buffer_data[cur++] = size*cos(angle);
        vertex_buffer_data[cur++] =  0.0f;

        vertex_buffer_data[cur++] = size*sin(angle);
        

        //Point with higher angle
        angle+= diff;
        vertex_buffer_data[cur++]=size*cos(angle);
        vertex_buffer_data[cur++]= 0.0f;

        vertex_buffer_data[cur++]=size*sin(angle);
    }
    }
    else
    {


    for (unsigned int i=0;i<n;i++)
    {
        //Origin
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = 10.0; 

        //Point with lower angle
        vertex_buffer_data[cur++] = size*cos(angle);

        vertex_buffer_data[cur++] = size*sin(angle);
        vertex_buffer_data[cur++] =  0.0f;
        

        //Point with higher angle
        angle+= diff;
        vertex_buffer_data[cur++]=size*cos(angle);

        vertex_buffer_data[cur++]=size*sin(angle);
        vertex_buffer_data[cur++]= 0.0f;

        angle-= diff;
        vertex_buffer_data[cur++] = 0.0;
        vertex_buffer_data[cur++] = 0.0f;
        vertex_buffer_data[cur++] = -10.0; 

        //Point with lower angle
        vertex_buffer_data[cur++] = size*cos(angle);

        vertex_buffer_data[cur++] = size*sin(angle);
        vertex_buffer_data[cur++] =  0.0f;
        

        //Point with higher angle
        angle+= diff;
        vertex_buffer_data[cur++]=size*cos(angle);

        vertex_buffer_data[cur++]=size*sin(angle);
        vertex_buffer_data[cur++]= 0.0f;

    }
    }


    this->object = create3DObject(GL_TRIANGLES, 6*n,  vertex_buffer_data, color, GL_FILL);



   
}

void Enemy::draw(glm::mat4 VP ) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
   

}
void Enemy::tick()
{
     this->position.x += speed*this->movx;
     this->position.z += speed*this->movz;
     if ((this->position.y < (this->temp) -(this->height)) && tempspeed<0 )
        tempspeed = -tempspeed;
     if ((this->position.y >(this->temp) +(this->height - 2.0f)) && tempspeed>0 )
        tempspeed = -tempspeed;
     this->position.y += tempspeed;

}
bounding_box_t Enemy::bounding_box() {
    float _x = this->position.x, _y = this->position.y, _z = this->position.z;
    bounding_box_t bbox = { _x, _y, _z, this->size, this->size, this->size};
    return bbox;
}


void Enemy::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
