//
// Created by Tyler Brown on 4/11/2018.
//
#define STB_IMAGE_IMPLEMENTATION
#ifndef FINAL_PROJECT_BACKGROUND_H
#define FINAL_PROJECT_BACKGROUND_H

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <future>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


void changeMatrix(float&);

class Background{

private:

    //Coordinates to be used when drawing the background texture to the screen.
    float vertices[32] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

//indices of the vertices of the triangles that will contain the background texture
    unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };


    //variables used to aid reading in the background texture from an image
    int width, height, nrChannels;

    //array that contains the data necessary to draw image
    unsigned char *data;

    //texture object compatible with openGL
    GLuint texture;

    //the translation vector for the background
   float offset = -0.01f;


public:
    //constructor that reads in the background image
    Background() {

        //flip image around
        stbi_set_flip_vertically_on_load(true);

        //setting up texture parameters for OpenGL
        glGenTextures(1, &texture);

        //binding the texture object to opengl context
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //read in background image
        data = stbi_load("background.png", &width, &height, &nrChannels, 0);

        if(data) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }

        stbi_image_free(data);

        std::cout << "Made it!" << std::endl;
    }


    //functions to access private data:

    //this function is to get the vertices of the image
    float * getVertices(){

        return this -> vertices;
    }

    unsigned int * getIndices() {

        return this -> indices;
    }

    //function that continually modifies the transformation matrix in order to
    void update(GLuint prog){

        auto update = std::async(std::launch::async, changeMatrix, std::ref(offset));


    }

    //return the offset
    float getOffset(){

        return this -> offset;
    }


};

//function to be executed on each thread that continually updates the background throughout execution
void changeMatrix(float & offset){

    for(int i =0; i < 100000; ++i) {
        offset = offset * (1 + offset);
    }

}

#endif //FINAL_PROJECT_BACKGROUND_H