//
// Created by Tyler Brown on 4/17/2018.
//
#ifndef FINAL_PROJECT_SCROLLER_H
#define FINAL_PROJECT_SCROLLER_H

//#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <chrono>


class Scroller{

private:

    //Coordinates to be used when drawing the background texture to the screen.
    float vertices[32] = {
            // positions          // colors           // texture coords
            1.0f,  -0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  -0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    //indices of the vertices of the triangles that will contain the background texture
    unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    //variables used to aid reading in the background texture from an image
    int width, height, nrChannels;

    //array that contains the data necessary to draw image
    unsigned char *data, *data2;

    //texture objects compatible with openGL
    GLuint texture, texture2;

    //the background will have its own buffers too
    unsigned int VBO, VAO, EBO;

    //value that represents the offset of both textures and the delta value to increase the scroll rate
    float offset, delta;

    //clock values for scrolling
    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;

public:

    Scroller() : offset(0.0) {

        //the background will have its own buffers just like any other texture
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

        //now set up the texture

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

        //read in scrolling image
        data = stbi_load("../textures/ground.png", &width, &height, &nrChannels, 0);

        if(data) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }

        stbi_image_free(data);

        //setting up texture parameters for OpenGL
        glGenTextures(1, &texture2);

        //binding the texture object to opengl context
        glBindTexture(GL_TEXTURE_2D, this -> texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



        //read data 2
        data2 = stbi_load("../textures/ground2.png", &width, &height, &nrChannels, 0);


        if(data2) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }


        stbi_image_free(data2);

        //keep track of time
        start = std::chrono::high_resolution_clock::now();

    }


    void draw(GLuint prog) {

        glBindVertexArray(this -> VAO);

        //bind first texture and draw it
        glBindTexture(GL_TEXTURE_2D, this -> texture);

        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::translate(transform, glm::vec3(offset, 0.0f, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        //bind second texture and draw it
        glBindVertexArray(this -> VAO);
        glBindTexture(GL_TEXTURE_2D, this -> texture2);

        transform = glm::mat4(1.0f);

        transform = glm::translate(transform, glm::vec3(1.0f + offset, 0.0f, 0.0f));
        transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        scroll();


    }

    //this function to continuously update the offset so that the images appear to scroll
    //it uses time to determine how fast it should be scrolling
    void scroll(){

        finish = std::chrono::high_resolution_clock::now();

        delta = std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();


        if(delta < 10){

            offset -= 0.002;

        } else if(delta < 20) {

            offset -= 0.003;

        } else if(delta < 30) {

            offset -= 0.004;

        } else {

            offset -= 0.005;

        }

        if(offset < -1.0f){

            offset = 0.0;
        }



    }


};

#endif //FINAL_PROJECT_SCROLLER_H
