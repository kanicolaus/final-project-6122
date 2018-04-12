#include <iostream>
#include "../include/Background.h"
#include "../include/Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//height and width of the window being displayed by opengl
int h,w;

//this is the creation of an GLFWwindow baiscally an object that represents the window
GLFWwindow *window = nullptr;

int main() {

    //this is initializing glfw
    if(!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return 1;
    }

    //this tells glfw to terminate when the window is closed
    atexit(glfwTerminate);

    //this sets up the opengl window by setting the version and all the other necessities
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    //this code is getting the dimensions that will fill up the screen
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    w = mode -> width;
    h = mode -> height;

    //this is creating the opengl window
    window = glfwCreateWindow(w, h, "Flappy Bird", NULL, NULL);
    if(!window) {
        std::cerr << "Failed to create window" << std::endl;
        return 1;
    }

    //this basically tells opengl to make the thing its running the current context on
    glfwMakeContextCurrent(window);

    //make sure glad is running correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //creating an object that represents the opengl program
    GLuint prog;

    //now use my compile_shaders function to compile the shaders we wrote
    compile_shaders(prog);

    //create a Background object to use
    Background flappys_home;


    //set up VBO VAO and EBO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 32*sizeof(flappys_home.getVertices()), flappys_home.getVertices(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  6*sizeof(flappys_home.getIndices()), flappys_home.getIndices(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //now we tell opengl to use the program
    glUseProgram(prog);

    //then we bind the VAO to the opengl context we are using
    glBindVertexArray(VAO);


    flappys_home.update(prog);

//    glm::mat4 trans;
//    trans = glm::translate(trans, glm::vec3(0.1f, 0.0f, 0.0f));
//    GLint transformLoc = glGetUniformLocation(prog, "transform");
//    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


    //finally we start our render loop
    while(!glfwWindowShouldClose(window)) {


        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(flappys_home.getOffset(), 0.0f, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //clear out the old to make way for the new!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //draw the texture
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //swap the buffers
        glfwSwapBuffers(window);

       // flappys_home.update(prog);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);


}