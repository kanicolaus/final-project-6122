#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Avatar.h>
#include "../include/Background.h"
#include "../include/Shader.h"
#include "../include/Scroller.h"
#include "../include/Obstacle.h"
#include "../include/Lifetext.h"
#include "../include/Lifesyms.h"
#include "../include/Speedup.h"
#include <GLFW/glfw3.h>



//function prototype
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

//array of booleans, with enough space to hold all of the possible key values on a keyboard
bool keys[1024] = { 0 };

//height and width of the window being displayed by opengl
int h,w;

//this is the creation of an GLFWwindow baiscally an object that represents the window
GLFWwindow *window = nullptr;

//just for testing purposes
// AVATAR
ScreenObject* tester; 
// OBSTACLES
ScreenObject* obstacle0;
ScreenObject* obstacle1;
ScreenObject* obstacle2;
ScreenObject* obstacle3;
ScreenObject* obstacle4;
// SPEEDUPS
ScreenObject* powerup0;
ScreenObject* powerup1;
ScreenObject* powerup2;
ScreenObject* powerup3;
ScreenObject* powerup4;
// LIFE TEXT
ScreenObject* lifetext0;
// LIFE SYMBOLS
ScreenObject* lifesym0;
ScreenObject* lifesym1;
ScreenObject* lifesym2;


int main() {

    //seed random number generators
    std::srand( std::time(NULL) );

    //this is initializing glfw
    if(!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return 1;
    }

    //this tells glfw to terminate when the window is closed
    atexit(glfwTerminate);

    //this sets up the opengl window by setting the version and all the other necessities
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


    //this code is getting the dimensions that will fill up the screen
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    w = mode -> width;
    h = mode -> height;

    //this is creating the opengl window
    window = glfwCreateWindow(w, h, "ECE 4122 Project", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }

    //this basically tells opengl to make the thing its running the current context on
    glfwMakeContextCurrent(window);

    //set up callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    //make sure glad is running correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

///////////////////////////////////////////CODE FOR GAME MANAGEMENT//////////////////////////////////////////////////

    //creating an object that represents the opengl program
    GLuint prog;

    //now use my compile_shaders function to compile the shaders we wrote
    compile_shaders(prog);

    //create objects to draw on the screen
    Background flappys_home;
    Avatar test;
    Scroller scroll;
    Obstacle block0(rand()%200+100, rand()%170-70);
    Obstacle block1(rand()%200+100, rand()%170-70);
    Obstacle block2(rand()%200+100, rand()%170-70);
    Obstacle block3(rand()%200+100, rand()%170-70);
    Obstacle block4(rand()%200+100, rand()%170-70);
    Speedup spboost0(rand()%300+101, rand()%170-70);
    Lifetext lives;
    Lifesyms life0(-70.0f, -90.0f);
    Lifesyms life1(-58.0f, -90.0f);
    Lifesyms life2(-46.0f, -90.0f);

    tester = &test;
    obstacle0 = &block0;
    obstacle1 = &block1;
    obstacle2 = &block2;
    obstacle3 = &block3;
    obstacle4 = &block4;
    powerup0 = &spboost0;
    lifetext0 = &lives;
    lifesym0 = &life0;
    lifesym1 = &life1;
    lifesym2 = &life2;

    // Store all obstacles in an array for collision detection
    std::vector<ScreenObject*> OBSTACLES = { obstacle0, obstacle1, obstacle2, obstacle3, obstacle4 };
    std::vector<ScreenObject*> SPEEDUPS = { powerup0 };

    glUseProgram(prog);

    //finally we start our render loop
    while(!glfwWindowShouldClose(window)) {

        //clear the old screen whenever we re render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        flappys_home.draw(prog);
        //bindText(test.getVertices(), test.getIndices());
        test.draw(prog);

        scroll.draw(prog);

        block0.moveLeft();
        block1.moveLeft();
        block2.moveLeft();
        block3.moveLeft();
        block4.moveLeft();
        block0.draw(prog);
        block1.draw(prog);
        block2.draw(prog);
        block3.draw(prog);
        block4.draw(prog);

        spboost0.moveLeft();
        spboost0.draw(prog);

        lives.draw(prog);
        if (test.getLifeCount(0) == 3) {
            life0.draw(prog);
            life1.draw(prog);
            life2.draw(prog);
        } else if (test.getLifeCount(0) == 2) {
            life0.draw(prog);
            life1.draw(prog);
        } else if (test.getLifeCount(0) == 1) {
            life0.draw(prog);
        } else if (test.getLifeCount(0) == 0) {
            // std::cout << "LIVES EXPIRED, THANKS FOR PLAYING" << std::endl;
        } 


        // check if the avatar has collided with any obstacles on screen
        if(test.collision(OBSTACLES)) {
            if(test.TESTING_MODE) std::cout << "Collision detected with OBSTACLE" << std::endl;
            block0.resetPosition();
            block1.resetPosition();
            block2.resetPosition();
            block3.resetPosition();
            block4.resetPosition();
            test.getLifeCount(-1);
        }
        // check if the avatar has collided with any speedups on screen
        if(test.collision(SPEEDUPS)) {
            if(test.TESTING_MODE) std::cout << "Collision detected with SPEEDUP" << std::endl;
            spboost0.resetPosition();
            test.speedInc();
        }




        //swap the buffers
        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwDestroyWindow(window);


}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

   if(action == GLFW_PRESS) {

        keys[key] = true;

    } else if(action == GLFW_RELEASE) {

        keys[key] = false;

    }

    if(keys[GLFW_KEY_UP]) {

        tester -> moveUp();

    } else if(keys[GLFW_KEY_DOWN]) {

        tester -> moveDown();

    } else if(keys[GLFW_KEY_LEFT]) {

        tester -> moveLeft();

    } else if(keys[GLFW_KEY_RIGHT]) {

        tester -> moveRight();

    } else if(keys[GLFW_KEY_ESCAPE]) {

        glfwSetWindowShouldClose(window, 1);

    }


    
}


//TODO: fix this callback so that the cursor can control the sun accurately

//callback function that is used to essentially attach the avatar object to the cursor so that
//it can be used in game play.
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){

    float centerX, centerY, ratioX, ratioY;

    //this bit of code is calculating the x y coordinates of the center of the screen
    centerX = w/2;
    centerY = h/2;

    //ratioX is the ratio of width to height of the screen to a more precise decimal point
    //ratioY is the ratio of width to height of the screen which is truncated due to integer addition
    ratioX = ((float)w / (float)h) * 10;
    ratioY = (w/h) * 10;

    //this code is adjusting xpos and ypos so that the values map to a cartesian plane
    xpos = xpos - centerX;
    ypos = ypos - centerY;

    //this is setting the avatar's x and y coordinates
    tester -> setXPos(xpos/ratioX);
    tester -> setYPos(-ypos/ratioY);


}


