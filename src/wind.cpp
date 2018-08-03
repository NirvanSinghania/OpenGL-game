#include "wind.h"
#include "main.h"

Wind::Wind(float speed, float acc) {
    this-> speedx = speed ;
    this-> speedz = speed;
    this-> accx = acc;
    this-> accz = acc;
        this -> windon =0;
    this -> duration = 500;
}

void Wind::start()
{
     float ang = (rand()%360)*M_PI/180.0f;
     this -> speedx = 0.2f * cos(ang);
     this -> speedz = 0.2f * sin(ang);
     this -> accx = 0.002f * cos(ang);
     this -> accz = 0.002f * sin(ang);
     this -> windon =1;
     this -> curcount = 0;

}
void Wind::move()
{
    (this->curcount )+=1;
    if (this->curcount == this->duration)
    {
        this->windon =0 ;
        this-> curcount =0 ;
    }
}
