#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z, color_t color) {
   

    this->position = glm::vec3(x, y, z);
    this -> rotation = 0;
    this-> speed = 0.1f;
    this-> movx = (rand()%3)-1;
    this-> movz = (rand()%3)-1;
    this -> hasgift = 1;
    this -> size = 3;
    height = 18.0f; 
    

    int n = 20;
    int reqd = n*9*20;

    float vertex_buffer_data[reqd] = {};

    
    const double pi = 4*atan(1);
    double diff = (2*pi)/(double)n;
    int cur =0;

    double size = 5.0f;

    for (unsigned int j=0;j<20;j++)
    {
        double angle =0;
        for (int i=0;i<n;i++)
        {

            //Origin
            float lol = j*0.5f;
            vertex_buffer_data[cur++] = lol;;
            vertex_buffer_data[cur++] = 0.0f; 
            vertex_buffer_data[cur++] = 0.0f;

            //Point with lower angle
            vertex_buffer_data[cur++] = lol;
            vertex_buffer_data[cur++] = size*cos(angle);
            vertex_buffer_data[cur++] = size*sin(angle);
            

            

            //Point with higher angle
            angle+= diff;
            vertex_buffer_data[cur++]= lol;
            vertex_buffer_data[cur++]= size*cos(angle);
            vertex_buffer_data[cur++]= size*sin(angle);
           

        }
    }


      n = 180;
    reqd = n*9;
    GLfloat buffer[reqd] = {};

    double angle =0;
 
    cur =0;

   size = 3.0f;


    for (int i=0;i<n;i++)
    {
        //Origin
        buffer[cur++] = 0.0;
        buffer[cur++] = height; 
        buffer[cur++] = 0.0f;

        //Point with lower angle
        buffer[cur++] = size*cos(angle);
        buffer[cur++] = height + size*sin(angle);
        buffer[cur++] = 0.0f;

        

        //Point with higher angle
        angle+= diff;
        buffer[cur++]=size*cos(angle);
        buffer[cur++]= height + size*sin(angle);
        buffer[cur++]=0.0f;

    }



    this->object = create3DObject(GL_TRIANGLES, 20*3*20,  vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, reqd/3,  buffer, COLOR_YELLOW, GL_FILL);
   
}

void Barrel::draw(glm::mat4 VP ) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if (this->hasgift)
        draw3DObject(this->object1);

}
void Barrel::tick()
{
     position.x += speed*movx;
     position.z += speed*movz;

}

void Barrel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

