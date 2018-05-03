//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_MENU_H
#define FINAL_PROJECT_MENU_H

#include "ScreenObject.h"
#include "stb_image.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

enum gameStatusType : int16_t {

    MainMenu,
    Settings,
    Run,
    Pause,
    Dead
};


class MenuArrow : public ScreenObject {

public:

    int arrowPos = 0;
    int numPos = 0;
    gameStatusType gameStatus = MainMenu;

    //constructor takes in start position of the object (default to center of screen)
    MenuArrow() : ScreenObject(0, 0) {

        //intialize type
        type = MENU;

        //load the image into the texture data field

        //flip image around
        stbi_set_flip_vertically_on_load(true);

        //setting up texture parameters for OpenGL
        glGenTextures(1, &texture);

        //binding the texture object to opengl context
        glBindTexture(GL_TEXTURE_2D, this -> texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //read in background image
        // unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
        data = stbi_load("../textures/arrow.png", &width, &height, &nrChannels, STBI_rgb_alpha);

        if(data) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }

        stbi_image_free(data);

        if (gameStatus == MainMenu) {
            numPos = 2;
        }


        //now set other variables from ScreenObject class
        //these numbers represent the x,y values for the four corners of the image
        //top right (x,y)
        vertices[0] = -0.2f;
        vertices[1] = 0.4f;

        //bottom right (x,y)
        vertices[8] = -0.2f;
        vertices[9] = 0.3f;

        //top left (x,y)
        vertices[16] = -0.3f;
        vertices[17] = 0.3f;

        //bottom left (x,y)
        vertices[24] = -0.3f;
        vertices[25] = 0.4f;

        //attribute these new vertices with the VAO/VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    }


    // function called to determine what to do in menus based on arrow position
    gameStatusType enterPressed() {
        if (gameStatus == MainMenu && arrowPos == 0) {
            return Run;
        } else if (gameStatus == MainMenu && arrowPos == 1) {
            return Settings;
        } else if (gameStatus == Dead) {
            return MainMenu;
        }
    }

    virtual bool collision(std::vector<ScreenObject*> objects){

        // May not need to do much here for the menu class
        return false;

    }

    virtual void collisionHandler() {

        // Not sure if the menu class will need to call this

    }

    //these movement functions not only change the offset of the textures, they also map the movement to change in
    //cartesian coordinates as well
    virtual void moveLeft() {

    }

    virtual void moveRight() {

    }

    virtual void moveUp() {

        std::cout << "arrowPos: " << arrowPos << std::endl;
        if (arrowPos > 0) {
            y_offset += 0.25;
            arrowPos -= 1;
        }
    }

    virtual void moveDown() {

        std::cout << "arrowPos: " << arrowPos << std::endl;
        if (arrowPos < numPos-1) {
            y_offset -= 0.25;
            arrowPos += 1;
        }

    }

    virtual bool onScreenCheck() {

        return onScreen;

    }

    virtual void resetPosition() {

        arrowPos = 0;
        y_offset = 0;

    }

    //function to draw this object
    virtual void draw(GLuint prog) {

        //switch to this object's VAO
        glBindVertexArray(this -> VAO);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(x_offset, y_offset, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindTexture(GL_TEXTURE_2D, this -> texture);

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


};


class MenuText : public ScreenObject {

public:

    gameStatusType gameStatus = MainMenu;

    //constructor takes in start position of the object (default to center of screen)
    MenuText(gameStatusType gameSts) : ScreenObject(0, 0), gameStatus(gameSts) {

        //intialize type
        type = MENU;

        //load the image into the texture data field

        //flip image around
        stbi_set_flip_vertically_on_load(true);

        //setting up texture parameters for OpenGL
        glGenTextures(1, &texture);

        //binding the texture object to opengl context
        glBindTexture(GL_TEXTURE_2D, this -> texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //read in background image
        // unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
        if (gameStatus == MainMenu) {
            data = stbi_load("../textures/menuText.png", &width, &height, &nrChannels, STBI_rgb_alpha);
            x_offset = 0;
            y_offset = 0.2;
        }
        else if (gameStatus == Settings) {
            data = stbi_load("../textures/shrug.png", &width, &height, &nrChannels, STBI_rgb_alpha);
            x_offset = 0;
            y_offset = 0;
        }

        if(data) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }

        stbi_image_free(data);


        //now set other variables from ScreenObject class
        //these numbers represent the x,y values for the four corners of the image
        //top right (x,y)
        vertices[0] = 0.15f;
        vertices[1] = 0.3f;

        //bottom right (x,y)
        vertices[8] = 0.15f;
        vertices[9] = -0.3f;

        //top left (x,y)
        vertices[16] = -0.15f;
        vertices[17] = -0.3f;

        //bottom left (x,y)
        vertices[24] = -0.15f;
        vertices[25] = 0.3f;

        //attribute these new vertices with the VAO/VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    }

    //TODO: complete these functions
    //this function goes through a vector and checks to see if the calling object is within a certain range of any other
    //object on the screen.
    //the only input is the vector of objects that are drawn to the screen
    // virtual ScreenObject* collision(std::vector<ScreenObject*> objects){
    virtual bool collision(std::vector<ScreenObject*> objects){

        // May not need to do much here for the menu class
        return false;

    }

    virtual void collisionHandler() {

        // Not sure if the menu class will need to call this

    }

    //these movement functions not only change the offset of the textures, they also map the movement to change in
    //cartesian coordinates as well
    virtual void moveLeft() {

    }

    virtual void moveRight() {

    }

    virtual void moveUp() {

    }

    virtual void moveDown() {

    }

    virtual bool onScreenCheck() {

        return onScreen;

    }

    virtual void resetPosition() {}

    //function to draw this object
    virtual void draw(GLuint prog) {

        //switch to this object's VAO
        glBindVertexArray(this -> VAO);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(x_offset, y_offset, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindTexture(GL_TEXTURE_2D, this -> texture);

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


};


#endif //FINAL_PROJECT_MENU_H
