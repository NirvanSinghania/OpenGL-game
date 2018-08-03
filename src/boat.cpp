#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 3;
    this-> speedy = 0;
    this ->  accy = 0;
    this-> health = 100.0;
    this ->alive = 1;
    this -> collide = 0;
    this-> points = 0;
    this -> mon_killed = 0;
    this -> alive = 1;
    

 
    static const GLfloat vertex_buffer_data[] = {
       

        //right 
        -10.0, -4.0f, 8.0f,
        10.0, 4.0f, 2.0f,
        -10.0, 4.0f, 8.0f,
        -10.0, -4.0f, 8.0f,
        10.0, 4.0f, 2.0f,
        10.0, -4.0f, 2.0f,

        //left 
         10.0, 4.0f, -2.0f,
        -10.0, -4.0f, -8.0f,
        10.0, -4.0f, -2.0f,
        10.0, 4.0f, -2.0f,
        -10.0, -4.0f, -8.0f,
        -10.0, 4.0f, -8.0f,

       

        //back 
         10.0, 4.0f, 2.0f,
        10.0, -4.0f, -2.0f,
        10.0, -4.0f, 2.0f,
        10.0, 4.0f, 2.0f,
        10.0, -4.0f, -2.0f,
        10.0, 4.0f, -2.0f,


           //front
        -10.0, -4.0f, -8.0f,
        -10.0, 4.0f, 8.0f,
        -10.0, 4.0f, -8.0f,
        -10.0, -4.0f, -8.0f,
        -10.0, 4.0f, 8.0f,
        -10.0, -4.0f, 8.0f,
        //center
          -10.0, 0.1f, 8.0f,
        10.0, 0.1f, -2.0f,
        10.0, 0.1f, 2.0f,
        -10.0, 0.1f, 8.0f,
        10.0, 0.1f, -2.0f,
        -10.0, 0.1f, -8.0f,


        //pole

           7.5f, -4.0f, 1.5f,
        9.5f, -4.0f, 1.5f,
        10.5f, 35.0f, 0.0f,

        9.5f, -4.0f, 1.5f,
        9.5f, -4.0f, -1.5f,
        10.5f, 35.0f, 0.0f,

        9.5f, -4.0f, -1.5f,
        7.5f, -4.0f, -1.5f,
        10.5f, 35.0f, 0.0f,

        9.5f, -4.0f, -1.5f,
        9.5f, -4.0f, 1.5f,
        10.5f, 35.0f, 0.0f,

        //sails big
         3.0, 25.0f, 10.0f,
        12.0f, 15.0f, 0.0f,
        3.0, 15.0f, 10.0f,
        3.0, 25.0f, 10.0f,
        12.0f, 15.0f, 0.0f,
        12.0f, 25.0f, 0.0f,

        3.0, 25.0f, -10.0f,
        12.0f, 15.0f, 0.0f,
        3.0, 15.0f, -10.0f,
        3.0, 25.0f, -10.0f,
        12.0f, 15.0f, 0.0f,
        12.0f, 25.0f, 0.0f,






        
    };
    int cur = 0;
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+cur, COLOR_KHAKI, GL_FILL);
    cur += 18;
    this->object2 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+cur, COLOR_KHAKI  , GL_FILL);
    cur += 18;
    this->object3 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+cur, COLOR_KHAKI, GL_FILL);
    cur += 18;
    
    this->object4 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+cur, COLOR_YELLOW, GL_FILL);
    cur += 18;
    
    this->object5 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data+cur, COLOR_CRIMSON    , GL_FILL);
    cur += 18;
    
    this->object6 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data+cur, COLOR_BROWN, GL_FILL);
    cur += 36;
    
    this->object7 = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data+cur, COLOR_WHITE, GL_FILL);
     
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate   = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));


    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
    draw3DObject(this->object7);

  
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::upd_health(float val)
{
    this->health += val;
    
    if (this->health <= 0.0f )
    {
        this->health = 0.0;
        this->alive = 0;
    }

}
void Boat::tick() {

    speedy += accy;
    this->position.y += speedy;
    if(this->position.y<63){
        this->position.y = 63;
        speedy = 0;
        accy = 0;
    }
}
void Boat::tick_on_wind(float _x,float _z)
{
    this->position.x += _x;
    this->position.z += _z;
}



void Boat::jump()
{
    speedy = 1.5;
    accy = -0.05;
}

void Boat::move_right()
{
    this->rotation -= (this->speed)*0.25;
}

void Boat::move_left()
{

    this->rotation += (this->speed)*0.25;
}

void Boat::move_front(float angle){
    position.x -= (speed)*sin(angle);
    position.z -= (speed)*cos(angle);
}

void Boat::move_back(float angle){
    position.x += (speed)*sin(angle);
    position.z += (speed)*cos(angle);
}
void Boat::kill()
{
    this-> alive =0;
}




