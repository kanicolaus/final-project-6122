//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_SCREENOBJECT_H
#define FINAL_PROJECT_SCREENOBJECT_H

#include <glad/glad.h>
#include <vector>
#include <chrono>

enum screenObjectType : int16_t {

    AVATAR,
    OBSTACLE,
    POWERUP
};

//abstract class to represent the objects on the screen during gameplay
class ScreenObject{

protected:

    //normalized x and y coordinates of the center of the texture object on the screen
    //these are basically cartesian coordinates that map to the offset
    float x_pos;
    float y_pos;

    //each screen object will have its own vertices and indices
    float vertices[32] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    //private variable to represent the actual x y offsets of the texture
    float x_offset;
    float y_offset;

    //variables used to aid reading in the background texture from an image
    int width, height, nrChannels;

    //each screen object will include a texture
    GLuint texture;

    //array that contains the data necessary to draw image
    unsigned char *data;

    //each screen object will need its own buffers too
    unsigned int VBO, VAO, EBO;


    screenObjectType type;

    //clock values for scrolling
    float delta, deltaContinuous;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

    //is the object being drawn on-screen
    bool onScreen;

    //has the object been collided with
    bool collided;

    //track the number of collisions for each object (TESTING ONLY)
    int collisionCount = 0;

    //movement multiplier
    float mm = 3.0f;

    //track the number of lives (used by the avatar)
    int lifecount = 3;


public:

    //set to true to enable console feedback
    bool TESTING_MODE = true;

    //takes in the start position of this object
    ScreenObject(float x , float y) : x_pos(x), y_pos(y), x_offset(x/100), y_offset(y/100) {

        //each object on the screen will need to set up its own buffers for objects
        //thus this can be done in the base class to avoid having to retype this code
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

    }

    //pure virtual functions that must be implemented in the base classes that inherit this one
    // virtual ScreenObject* collision(std::vector<ScreenObject*> objects) = 0;
    virtual bool collision(std::vector<ScreenObject*> objects) = 0;
    virtual void collisionHandler() = 0;

    //functions that allow the objects to move on the screen 
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveUp() = 0;
    virtual void moveDown() = 0;
    virtual bool onScreenCheck() = 0;
    virtual void resetPosition() = 0;

    //function that forces all children classes to be able to be drawn on the screen
    virtual void draw(GLuint prog) = 0;

    //functions to get x_pos and y_pos outside of this class
    float getXPos() {

        return this -> x_pos;
    }

    float getYPos() {

        return this -> y_pos;

    }

    void setXPos(float xpos) {

        this -> x_pos = xpos;
        this -> x_offset = xpos/100;
    }

    void setYPos(float ypos) {

        this->y_pos = ypos;
        this->y_offset = ypos / 100;
    }

    void speedInc() {

        mm += 2.0;

    }

    int getLifeCount(int val) {

        lifecount += val;
        return lifecount;

    }

};

#endif //FINAL_PROJECT_SCREENOBJECT_H
