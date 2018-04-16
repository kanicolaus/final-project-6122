//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_AVATAR_H
#define FINAL_PROJECT_AVATAR_H

#include "ScreenObject.h"
#include "stb_image.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Avatar : public ScreenObject {

public:

    //constructor takes in start position of the object (default to center of screen)
    Avatar(float x = 0.0, float y = 0.0) : ScreenObject(x, y) {

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
        data = stbi_load("../textures/sun.png", &width, &height, &nrChannels, STBI_rgb_alpha);

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
        vertices[0] = 0.1f;
        vertices[1] = 0.1f;

        //bottom right (x,y)
        vertices[8] = 0.1f;
        vertices[9] = -0.1f;

        //top left (x,y)
        vertices[16] = -0.1f;
        vertices[17] = -0.1f;

        //bottom left (x,y)
        vertices[24] = -0.1f;
        vertices[25] = 0.1f;

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
    virtual ScreenObject* collision(std::vector<ScreenObject*> objects){

        double dist;
        int range = 20;

        for(auto thing : objects){

            //if the object being compared happens to be the calling object then ignore it
          if(thing == this){

              continue;

          }

            //compute the distance between this obejct and thing using cartesian coordinates
            dist = sqrt(pow(this -> x_pos - thing->getXPos(), 2.0) + pow(this -> y_pos - thing->getYPos(), 2.0));

            //if distance is less than range, return the pointer to the object that was run into
            if(dist < range) {

                return thing;

            }
        }

        //if all is good return NULL
        return NULL;

    }

    //these movement functions not only change the offset of the textures, they also map the movement to change in
    //cartesian coordinates as well
    virtual void moveLeft() {

        x_offset -= 0.015f;
        x_pos -= 1.5f;

        if(x_offset < -1.0) {

            x_offset = -1.0f;
            x_pos = -100.0f;
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

        if(y_offset < -1.0) {

            y_offset = -1.0f;
            y_pos = -100.0f;
        }

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

#endif //FINAL_PROJECT_AVATAR_H
