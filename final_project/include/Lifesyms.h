//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_LIFESYMS_H
#define FINAL_PROJECT_LIFESYMS_H

#include "ScreenObject.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Lifesyms : public ScreenObject {

public:

    //constructor takes in start position of the object (default to center of screen)
    Lifesyms(float x = 0.0, float y = 0.0) : ScreenObject(x, y) {
        // TOP RIGHT: <100.0, 100.0>
        // BOTTOM RIGHT: <100.0, -100.0>
        // BOTTOM LEFT: <-100.0, -100.0>
        // TOP LEFT: <-100.0, 100.0>
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
        data = stbi_load("../textures/lifeCircle.png", &width, &height, &nrChannels, STBI_rgb_alpha);

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
        vertices[0] = 0.05f;
        vertices[1] = 0.05f;

        //bottom right (x,y)
        vertices[8] = 0.05f;
        vertices[9] = -0.05f;

        //bottom left (x,y)
        vertices[16] = -0.05f;
        vertices[17] = -0.05f;

        //top left (x,y)
        vertices[24] = -0.05f;
        vertices[25] = 0.05f;

        //attribute these new vertices with the VAO/VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    }

    //TODO: complete these functions
    //this function goes through a vector and checks to see if 
    // the calling object is within a certain range of any other
    //object on the screen.
    //the only input is the vector of objects that are drawn to the screen
    virtual bool collision(std::vector<ScreenObject*> objects){

        // May not need to do much here for the Lifesyms class
        return false;

    }

    // Called when this collides with the Avatar
    virtual void collisionHandler(void) {

        // This function varies depending on the type of ScreenObject
        collided = true;


    }

    // For now: Lifesyms object only move left across the screen
    virtual void moveLeft() {

        // x_offset -= 0.015f;
        // x_pos -= 1.5f;

        // if(x_offset < -1.0) {

        //     x_offset = 1.0f;
        //     x_pos = 100.0f;

        // }

        finish = std::chrono::high_resolution_clock::now();

        delta = std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();


        if(delta < 10){

            x_offset -= 0.002;
            x_pos -= 0.2f;

        } else if(delta < 20) {

            x_offset -= 0.003;
            x_pos -= 0.3f;

        } else if(delta < 30) {

            x_offset -= 0.004;
            x_pos -= 0.4f;

        } else {

            x_offset -= 0.005;
            x_pos -= 0.5f;

        }

        if(x_offset < -1.0f){

            x_offset = 1.0f;
            x_pos = 100.0f;
        }

    }

    virtual void moveRight() {

        x_offset += 0.015f;
        x_pos += 1.5f;

        if(x_offset > 1.0) {

            x_offset = 1.0f;
            x_pos = 100.0f;

        }
    }

    virtual void moveUp() {

        y_offset += 0.015f;
        y_pos += 1.5f;

        if(y_offset > 1.0) {

            y_offset = 1.0f;
            y_pos = 100.0f;
        }
    }

    virtual void moveDown() {

        y_offset -= 0.015f;
        y_pos -= 1.5f;

        if(y_offset < -0.7) {

            y_offset = -0.7f;
            y_pos = -70.0f;
        }

    }

    virtual bool onScreenCheck() {

        return onScreen;

    }

    virtual void resetPosition() {
        collided = true;
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

#endif //FINAL_PROJECT_Lifesyms_H
