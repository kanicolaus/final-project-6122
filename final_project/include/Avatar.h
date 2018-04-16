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

    Avatar() : ScreenObject() {

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
        data = stbi_load("../textures/sun.png", &width, &height, &nrChannels, 0);

        if(data) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

    }

    //TODO: complete these functions
    //these are not done, still want to normalize coordinates
    virtual bool collision(){}

    virtual void moveLeft() {

        x_offset -= 0.015;
        x_pos -= 1.5;
    }

    virtual void moveRight() {

        x_offset += 0.015;
        x_pos += 1.5;
    }

    virtual void moveUp() {

        y_offset += 0.015;
        y_pos += 1.5;
    }

    virtual void moveDown() {

        y_offset -= 0.015;
        y_pos -= 1.5;

    }

    //function to draw this object
    virtual void draw(GLuint prog) {

        //switch to this object's VAO
        glBindVertexArray(this -> VAO);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(x_offset, y_offset, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this -> texture);

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }


};

#endif //FINAL_PROJECT_AVATAR_H
