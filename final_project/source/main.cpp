#include <iostream>
#include <cstdlib>
#include <Avatar.h>
#include "../include/Background.h"
#include "../include/Shader.h"
#include "../include/Scroller.h"
#include "../include/Obstacle.h"
#include <GLFW/glfw3.h>



//function prototype
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//array of booleans, with enough space to hold all of the possible key values on a keyboard
bool keys[1024] = { 0 };

//height and width of the window being displayed by opengl
int h,w;

//this is the creation of an GLFWwindow baiscally an object that represents the window
GLFWwindow *window = nullptr;

//just for testing purposes
ScreenObject* tester;
//IDEA FOR MOVING THE OBSTACLES: generate the max number of objects
//that we would need off screen initially (clip them).
//use a scroll like function to move them onto the screen (resetting 
//when hitting the other side).
//number of obstacles scrolled onto screen increases with time 
ScreenObject* obstacleTest;

int main() {

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
    Obstacle block;

    tester = &test;
    obstacleTest = &block;


    glUseProgram(prog);


    //finally we start our render loop
    while(!glfwWindowShouldClose(window)) {

        //clear the old screen whenever we re render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        flappys_home.draw(prog);
        //bindText(test.getVertices(), test.getIndices());
        test.draw(prog);

        scroll.draw(prog);
        block.moveLeft();
        block.draw(prog);

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


