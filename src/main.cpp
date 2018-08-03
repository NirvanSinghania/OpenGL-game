#include "main.h"
#include "timer.h"
#include "boat.h"
#include "water.h"
#include "rock.h"
#include "waves.h"
#include "cannon.h"
#include "barrel.h"
#include "wind.h"
#include "enemy.h"
#include "boss.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;


const int MAXN = 200;
Boat boat;
Water ocean;
Rock rock[MAXN];
Barrel barrels[MAXN];

Waves wave[MAXN];
Enemy enemies[MAXN];
Cannon cannon;
Wind wind;
Boss boss;
Rock island;


//Constants defined 
const int num_barrels = 20;
const int num_of_enemies = 30;
const int num_rocks = 100;
const int num_waves = 25;
const float pi = 4*atan(1);

const float BOAT_HEIGHT = 64.0f;

const int BOAT_VIEW = 1;
const int TOP_VIEW = 2;
const int TOWER_VIEW = 3;
const int FOLLOW_VIEW = 4;
const int HELICOP_VIEW = 5;


//Views and camera coordinates 
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0; 
float cx=0, cy=90, cz=100;
float tx=0, ty=90, tz=0;
int view = 4;

int time_for_wind = 0;
int boss_mode = 0;


Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */

void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    glm::vec3 eye(cx, cy, cz);
    glm::vec3 target (tx, ty, tz);
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ocean.draw(VP);
    island.draw(VP);
    for (unsigned int i = 0 ;i<num_waves; i++)
        wave[i].draw(VP);

    for (unsigned int i = 0 ;i<num_rocks; i++)
        rock[i].draw(VP);

    for (unsigned int i = 0 ;i<num_barrels; i++)
    {
        barrels[i].draw(VP);
    }
    for (unsigned int i= 0;i< num_of_enemies; i++)
    {
      if (enemies[i].alive)
        enemies[i].draw(VP);
    }
    
    boat.draw(VP);
    if (boss_mode && boss.alive)
    {
        boss.draw(VP);

    }

    if(cannon.release)
        cannon.draw(VP);
}
bool collision_with_rock(const Rock &rck)
{
    double dist = (boat.position.x - rck.position.x)*(boat.position.x - rck.position.x)+
            (boat.position.z - rck.position.z)*(boat.position.z - rck.position.z);
    return dist< (rck.size + 5.0f)*(rck.size + 5.0f) ;


}

bool collision_with_barrel(const Barrel &brl)
{
    double dist = (boat.position.x - brl.position.x)*(boat.position.x - brl.position.x)+
            (boat.position.z - brl.position.z)*(boat.position.z - brl.position.z);
    return dist< (brl.size + 2.0f)*(brl.size + 2.0f)  ;


}
bool collision_with_enemy(const Enemy &en)
{
     double dist = (boat.position.x - en.position.x)*(boat.position.x - en.position.x)+
    (boat.position.z - en.position.z)*(boat.position.z - en.position.z);
    return dist< (en.size + 2.0f)*(en.size + 2.0f)  && boat.position.y < en.position.y+en.height;
 
}

bool collision_with_boss()
{
     double dist = (boat.position.x - boss.position.x)*(boat.position.x - boss.position.x)+
    (boat.position.z - boss.position.z)*(boat.position.z - boss.position.z);
    return dist< (boss.size + 2.0f)*(boss.size + 2.0f)  && boat.position.y < boss.position.y+boss.height;
 
}
bool detect_collision(const  bounding_box_t &a,const bounding_box_t &b) {
    return (abs(a.x - b.x) * 2 < (a.length + b.length)) &&
            (abs(a.z - b.z) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}



void collision_helper(float temp_x, float temp_z)
{
    int flag =0;
    if (boat.collide){
    for (unsigned int i =0;i< num_rocks ; i++)
        if (collision_with_rock(rock[i])){            
            flag =1 ;
            break;
        }
    boat.collide = flag ;
    if (flag)
        boat.set_position(temp_x,boat.position.y,temp_z);
    }
    
    else
    {
        for (unsigned int i =0;i< num_rocks ; i++)
        if (collision_with_rock(rock[i])){
            
            flag =1 ;
            boat.upd_health(-0.1f);
            break;
        }
        boat.collide = flag;
    }
}



void tick_input(GLFWwindow *window) {

     int j = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
   
    int a =   glfwGetKey(window, GLFW_KEY_A);
    int  s=   glfwGetKey(window, GLFW_KEY_A);

    if (a)
    {

        boat.speed= max(boat.speed + 0.1f, 8.0f);

    }   
    if (s)
    {
        boat.speed = min(boat.speed - 0.1f, 2.0f);
    }
    int l  = glfwGetKey(window, GLFW_KEY_LEFT);
    int r = glfwGetKey(window, GLFW_KEY_RIGHT);
    int d = glfwGetKey(window, GLFW_KEY_DOWN);
    int u = glfwGetKey(window, GLFW_KEY_UP);
    float temp_x = boat.position.x;
    float temp_z = boat.position.z;
    if(f)
    {
        if (cannon.release!=1)
        {
        cannon.release = 1;
        cannon.shoot((boat.rotation-90)*(pi/180));
        }
    }
    if (l) 
    {
        boat.move_left();
        collision_helper(temp_x,temp_z);

    }
    if(r)
    {
        boat.move_right();
        collision_helper(temp_x,temp_z);
        

    }
    if(d)
    {
        boat.move_back((boat.rotation-90)*(pi/180));
        collision_helper(temp_x,temp_z);

    }
    if(u)
    {
        boat.move_front((boat.rotation-90)*(pi/180));
        collision_helper(temp_x,temp_z);
    }
    
    if(j)
    {
        if(boat.position.y<=64)
            boat.jump();
    }
    
}

void tick_elements() {
    time_for_wind ++;  
    if ( time_for_wind ==  2000 )
    {
        wind.start();
        time_for_wind = 0;
    }
    boss.tick();
    float temp_x = boat.position.x;
    float temp_z= boat.position.z;

    if (wind.windon){
        wind.move();
        boat.tick_on_wind(wind.speedx, wind.speedz);

    }
    else
        boat.tick();
        

    boat.set_position(temp_x, boat.position.y, temp_z);
    for( unsigned int i=0;i< num_barrels;i++)
    {

        if (collision_with_barrel(barrels[i]) && barrels[i].hasgift)
        {
            barrels[i].hasgift = 0;
            boat.points += 10;
        }
        barrels[i].tick();  
    }
    for (unsigned int i = 0;i< num_of_enemies ;i++)
    {

        enemies[i].tick();
        if (collision_with_enemy(enemies[i]))
            boat.upd_health(-3.0f);
        if (detect_collision(cannon.bounding_box(), enemies[i].bounding_box()))
           { enemies[i].alive = 0;
             boat.points += 10;
             boat.mon_killed += 1;

         }

    }

    if (boss_mode)
    {
        if (cannon.release &&(detect_collision(cannon.bounding_box(), boss.bounding_box())))
         {   boss.kill();
             boat.points += 50;
         }
         if (collision_with_boss())
         {
            boat.kill();
         }
        
    }
    
    collision_helper(temp_x,temp_z);


   if (cannon.release == 1)
    cannon.tick();
    else
       cannon.set_position(boat.position.x, boat.position.y, boat.position.z);

   if (boat.mon_killed >= 5)
        boss_mode = 1;

}
    

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    boat = Boat(0, 63   ,40, COLOR_RED);
    wind = Wind(0.1f,0.001f);
    cannon = Cannon(0, 62, 40, COLOR_TURQUOISE);
    ocean  =  Water(0, 40.0f, 0, COLOR_SEA);
   
    int randx, randz ;


    boat.rotation = 90;
    island = Rock( 500, 62 , 500, 100, COLOR_GRAY);
        
   
    for (unsigned int i = 0 ;i<num_waves; i++){

        randx = rand() % 2000;
        if (rand()%2)
            randx *= -1;
        randz = rand() % 2000;
          if (rand()%2)
            randz *= -1;
        wave[i] = Waves(randx, 60 , randz, COLOR_WAVE);
    }
     for (unsigned int i=0;i<num_of_enemies ;i++)
    {
        randx = rand() % 2000;
        if (rand()%2)
            randx *= -1;
        randz = rand() % 2000;
          if (rand()%2)
            randz *= -1;
        enemies[i]= Enemy(randx, 65.0f , randz, COLOR_PURPLE);
    }
    for (unsigned int i = 0 ;i<num_rocks; i++){
          randx = rand() % 2000;
        if (rand()%2)
            randx *= -1;
        randz = rand() % 2000;
          if (rand()%2)
            randz *= -1;
        rock[i] = Rock(randx, 62 , randz, 10, COLOR_GRAY);
    }
     for(unsigned int i ;i< num_barrels;i++){
         randx = rand() % 2000;
        if (rand()%2)
            randx *= -1;
        randz = rand() % 2000;
          if (rand()%2)
            randz *= -1;
        barrels[i] = Barrel(randx, 60.0f , randz, COLOR_BROWN);
    }
    randx = rand() % 50;
    if (rand()%2)
        randx *= -1;
    randz = rand() % 50;
      if (rand()%2)
        randz *= -1;
    boss = Boss(randx, 64 , randz, COLOR_RED);
   

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}
void display_score()
{
    char str[100];
    sprintf(str,"Score: %d\t    Health:%d\t  Boss lives:%d\n" , boat.points, (int)boat.health, boss.life_left);
    glfwSetWindowTitle(window, str);

}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

   
    while (!glfwWindowShouldClose(window)) {
       

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            display_score();
            if (view == HELICOP_VIEW )
            {
                cy = 100;
            }
            else
            {
                cx = boat.position.x;
                cy = boat.position.y;
                cz = boat.position.z;

                tx = boat.position.x;
                ty = boat.position.y;
                tz = boat.position.z;
                float ang = (boat.rotation-90.0f)*(pi/180);

                if (view == FOLLOW_VIEW)
                {
                   cx += 80*sin(ang);
                   cy =  100;
                   ty = cy;

                   cz += 80*cos(ang);
                   tx += sin(ang+pi);
                   tz += cos(ang+pi);

                }
                else if (view == BOAT_VIEW )
                {

                    cx += 30*sin(ang);
                    cy += 10;
                    ty = cy;

                    
                    cz += 30*cos(ang);
                    tx +=40*sin(ang+pi);
                    tz += 40*cos(ang+pi);
                }
         
                    
                    else if(view == TOP_VIEW){
                        cy = 200;
                        tx ++;
                       
                  
                    }
                    else if(view== TOWER_VIEW){
                        cx += 100;
                        cy = 200;
                        cz = boat.position.z;
                    }
            }
            if (boss.alive == 0 || boat.health <= 0.0f)
            {
                break;
            }

                
                       
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}



void reset_screen() 
{
  
    Matrices.projection = glm::perspective(45.0f, 1.0f, 60.0f, 1000.0f);
}

void updateview()
{
    view = view+1;
    if (view > 5)
        view = 1;
}



void helicopter(float _x, float _y){
    if(view != HELICOP_VIEW)
        return;

    tx = boat.position.x+(_x-250);
    if(_y<= 250){
        ty = boat.position.y+(250-_y)/2;
    }
}

void zooming_functionality(int type){
   
    const float diff_value = 11;

    if (view != HELICOP_VIEW)
        return;


    if (cz > tz+ diff_value)
        cz = cz- diff_value;
    
    else if (type == -1)
        cz += diff_value;

    cx = (tx-cx)*(cz-tz)/(tz-cz)+tx;
    cy = (ty-cy)*(cz-tz)/(tz-cz)+ty;
    
}
