#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Avatar.h>
#include <Menu.h>
#include "../include/Background.h"
#include "../include/Shader.h"
#include "../include/Scroller.h"
#include "../include/Obstacle.h"
#include "../include/Lifetext.h"
#include "../include/Lifesyms.h"
#include "../include/Speedup.h"
#include "../include/ScoreBoard.h"
#include "../include/LeaderBoard.h"
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
// Game Status
gameStatusType gameStatus = MainMenu;   // enumeration indicating current game in mode
// MENU ITEMS
MenuArrow* arrower;         // used for selection menu items and actions
MenuText* mainMenur;        // used for main menu texture
MenuText* settingsMenur;     // used for settings menu tecture
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
//LeaderBoard
LeaderBoard* leaders;


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
    MenuArrow testArrow;
    MenuText testMainMenu(MainMenu); // set texture for Main Menu
    MenuText testSettingsMenu(Settings); // set texture for settings menu
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
    arrower = &testArrow;
    mainMenur = &testMainMenu;
    settingsMenur = &testSettingsMenu;
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

    ScoreBoard sc;
    LeaderBoard lb;

    leaders = &lb;


    // Store all obstacles in an array for collision detection
    std::vector<ScreenObject*> OBSTACLES = { obstacle0, obstacle1, obstacle2, obstacle3, obstacle4 };
    std::vector<ScreenObject*> SPEEDUPS = { powerup0 };

    glUseProgram(prog);

    //just a test variable
    bool update = true;

    //finally we start our render loop
    while(!glfwWindowShouldClose(window)) {
        // Main Menu render
        while (!glfwWindowShouldClose(window) && gameStatus == MainMenu) {

            //clear the old screen whenever we re render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // update menu status
            arrower->gameStatus = gameStatus;
            flappys_home.draw(prog);
            testArrow.draw(prog);
            testMainMenu.draw(prog);

            //swap the buffers
            glfwSwapBuffers(window);

            glfwPollEvents();

        }
        // Settings Menu render
        while (!glfwWindowShouldClose(window) && gameStatus == Settings) {

            //clear the old screen whenever we re render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // update menu status
            arrower->gameStatus = gameStatus;
            flappys_home.draw(prog);
            testSettingsMenu.draw(prog);

            //swap the buffers
            glfwSwapBuffers(window);

            glfwPollEvents();

        }
        // Run Game render
        while (!glfwWindowShouldClose(window) && (gameStatus == Run || gameStatus == Dead)) {

            //clear the old screen whenever we re render
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // update menu status
            arrower->gameStatus = gameStatus;
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
            } else if (test.getLifeCount(0) <= 0) {
                // std::cout << "LIVES EXPIRED, THANKS FOR PLAYING" << std::endl;
                if (gameStatus == Run) {
                    gameStatus = Dead;
                }

                if (update) {
                    lb.changeScore(sc.getScore());
                    lb.setGameOver(true);
                    update = false;
                }
                lb.draw(prog);
            }


            // check if the avatar has collided with any obstacles on screen
            if (test.collision(OBSTACLES)) {
                if (test.TESTING_MODE) std::cout << "Collision detected with OBSTACLE" << std::endl;
                block0.resetPosition();
                block1.resetPosition();
                block2.resetPosition();
                block3.resetPosition();
                block4.resetPosition();
                test.getLifeCount(-1);
            }
            // check if the avatar has collided with any speedups on screen
            if (test.collision(SPEEDUPS)) {
                if (test.TESTING_MODE) std::cout << "Collision detected with SPEEDUP" << std::endl;
                spboost0.resetPosition();
                test.speedInc();
            }

            sc.draw(prog);

            //swap the buffers
            glfwSwapBuffers(window);

            glfwPollEvents();

        }
    }


    glfwDestroyWindow(window);


}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

   if(action == GLFW_PRESS) {

        keys[key] = true;

    } else if(action == GLFW_RELEASE) {

        keys[key] = false;

    }

    if(keys[GLFW_KEY_ENTER]) {

        gameStatus = arrower->enterPressed();
        arrower->resetPosition();

    } else if(keys[GLFW_KEY_UP]) {

        if(gameStatus == MainMenu) {
            arrower->moveUp();
        } else {
            tester->moveUp();
        }

    } else if(keys[GLFW_KEY_DOWN]) {

        if(gameStatus == MainMenu) {
            arrower->moveDown();
        } else {
            tester -> moveDown();
        }

    } else if(keys[GLFW_KEY_LEFT]) {

        tester -> moveLeft();

    } else if(keys[GLFW_KEY_RIGHT]) {

        tester -> moveRight();

    } else if(keys[GLFW_KEY_ESCAPE]) {

        glfwSetWindowShouldClose(window, 1);

    } else if(keys[GLFW_KEY_A] && leaders -> getGameOver()){

        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }

        leaders -> changeName('a');
        LeaderBoard::keystrokes++;

    } else if(keys[GLFW_KEY_B] && leaders -> getGameOver()){


        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('b');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_C] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('c');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_D] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('d');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_E] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('e');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_F] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('f');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_G] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('g');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_H] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('h');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_I] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('i');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_J] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('j');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_K] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('k');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_L] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('l');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_M] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('m');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_N] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('n');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_O] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('o');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_P] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('p');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_Q] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('q');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_R] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('r');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_S] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('s');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_T] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('t');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_U] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('u');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_V] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('v');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_W] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('w');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_X] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('x');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_Y] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;
        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }
        leaders -> changeName('y');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_Z] && leaders -> getGameOver()){

//        LeaderBoard::keystrokes++;

        if(LeaderBoard::keystrokes > 3){

            LeaderBoard::keystrokes = 3;

        }

        leaders -> changeName('z');
        LeaderBoard::keystrokes++;

    }else if(keys[GLFW_KEY_BACKSPACE] && leaders -> getGameOver()){


        leaders -> changeName('#');

        LeaderBoard::keystrokes--;

        if(LeaderBoard::keystrokes < 1){

            LeaderBoard::keystrokes = 1;

        }

    }

}


//callback function that is used to essentially attach the avatar object to the cursor so that
//it can be used in game play.
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){

    float centerX, centerY, ratioX, ratioY;

    int height, width;
    glfwGetWindowSize(window, &width, &height);

    //this bit of code is calculating the x y coordinates of the center of the screen
    centerX = width/2;
    centerY = height/2;

    //ratioX is the ratio of width to height of the screen to a more precise decimal point
    //ratioY is the ratio of width to height of the screen which is truncated due to integer addition
    ratioX = ((float)width / (float)height) * 10;
    ratioY = (width/height) * 10;

    //this code is adjusting xpos and ypos so that the values map to a cartesian plane
    xpos = xpos - centerX;
    ypos = ypos - centerY;

    //this is setting the avatar's x and y coordinates
    tester -> setXPos(xpos/ratioX);
    tester -> setYPos(-ypos/ratioY);

}


