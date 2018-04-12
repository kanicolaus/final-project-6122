#include <iostream>
#include <fstream>
#include "../include/Background.h"
#include "../include/Shader.h"
// #include "../include/Shader2.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

//height and width of the window being displayed by opengl
int h,w;
double xUserPos = 0.0, yUserPos = 0.0;
bool keys[1024] = { 0 };

//this is the creation of an GLFWwindow baiscally an object that represents the window
GLFWwindow *window = nullptr;

const char* vertex_shader2 = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"layout (location = 1) in vec3 aColor;"
"layout (location = 2) in vec2 aTexCoord;"
"out vec3 ourColor;"
"out vec2 TexCoord;"
"void main()"
"{"
"    gl_Position = vec4(aPos, 1.0);"
"    ourColor = aColor;"
"    TexCoord = aTexCoord;"
"}";


//this function is used to compile the shaders and link them to the program
static void compile_shaders2(GLuint &prog2){
    GLuint vs2 = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vs2, 1, &vertex_shader2, NULL);
    glCompileShader (vs2);

    std::ifstream t("nameFragShader.fs");
    if(!t.is_open()) {
        std::cerr << "Cannot open nameFragShader.fs!" << std::endl;
        return;
    }
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    const char *src2  = str.c_str();

    GLuint fs2 = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource (fs2, 1, &src2, NULL);
    glCompileShader (fs2);

    int success;
    glGetShaderiv(fs2, GL_COMPILE_STATUS, &success);
    if(!success) {
        int s;
        glGetShaderiv(fs2, GL_INFO_LOG_LENGTH, &s);

        char *buf = new char[s];
        glGetShaderInfoLog(fs2, s, &s, buf);

        std::cerr << buf << std::endl;
        delete [] buf;
        return;
    }

    prog2 = glCreateProgram ();
    glAttachShader (prog2, fs2);
    glAttachShader (prog2, vs2);
    glLinkProgram (prog2);

    glGetProgramiv(prog2, GL_LINK_STATUS, &success);
    if(!success) {
        int s;
        glGetProgramiv(prog2, GL_INFO_LOG_LENGTH, &s);

        char *buf = new char[s];
        glGetProgramInfoLog(prog2, s, &s, buf);

        std::cerr << buf << std::endl;
        delete [] buf;
        return;
    }

    glDeleteShader(vs2);
    glDeleteShader(fs2);

}

static void gen_texture(GLuint &texID) 
{
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int texW, texH, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *texData = stbi_load("sun.png", &texW, &texH, &nrChannels, 0);
    if (texData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texW, texH, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(texData);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // const double d = 0.1 / zoom;
    const double moveSpeed = 0.1;

    if(action == GLFW_PRESS) {
        keys[key] = true;
    } else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }

    if(keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(window, 1);
    } else if(keys[GLFW_KEY_A]) {
        xUserPos -= moveSpeed;
    } else if(keys[GLFW_KEY_D]) {
        xUserPos += moveSpeed;
    } else if(keys[GLFW_KEY_W]) {
        yUserPos += moveSpeed;
    } else if(keys[GLFW_KEY_S]) {
        yUserPos -= moveSpeed;
    }
}

int main() {

    //this is initializing glfw
    if(!glfwInit()) {
        std::cerr << "Failed to init GLFW" << std::endl;
        return 1;
    }

    //this tells glfw to terminate when the window is closed
    atexit(glfwTerminate);

    //this sets up the opengl window by setting the version and all the other necessities
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // KN: Changed to 3 (from 4)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // KN: Changed to 3 (from 1)
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

    glfwSetKeyCallback(window, key_callback); // KN: Callback function for movement of avatar

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
    GLuint prog2; // KN: Create program for running other textures
    GLuint avatarTex; // KN: Create texture for the user controlled avatar

    //now use my compile_shaders function to compile the shaders we wrote
    compile_shaders(prog);
    compile_shaders2(prog2);
    gen_texture(avatarTex);

    //create a Background object to use
    Background flappys_home;


    // set up VBO VAO and EBO 
    // KN: This is for background image
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

    // KN: setup up VBO2 VAO2 and EBO2
    // KN: This is for the user-controlled avatar
    float avat_vertices[] = {
        // positions          // colors           // texture coords
         0.1f,   0.1f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.1f,  -0.1f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.1f,  -0.1f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.1f,   1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int avat_indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO2, VAO2, EBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(avat_vertices), avat_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(avat_indices), avat_indices, GL_STATIC_DRAW);

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

    // int iterator = 0;
    //finally we start our render loop
    int iterator = 0;
    while(!glfwWindowShouldClose(window)) {


        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(flappys_home.getOffset(), 0.0f, 0.0f));
        GLint transformLoc = glGetUniformLocation(prog, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //clear out the old to make way for the new!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // #################################################
        // glfwGetWindowSize(window, &w, &h);
        glUseProgram(prog);
        glBindVertexArray(VAO);
        if (iterator > 1) {
            GLint transformLoc = glGetUniformLocation(prog, "transform");
        }
        iterator += 1;

        // Drawing the mandlebrot set
        // glUseProgram (prog);
        // glBindVertexArray(vao);
        glDrawArrays (GL_TRIANGLES, 0, 6);
        // Drawing the upper left name
        glBindVertexArray(VAO2);
        glUseProgram (prog2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfwSwapBuffers(window);
        // glfwPollEvents();
        // #################################################


        //draw the texture
        // glUseProgram(prog);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    

        //swap the buffers
        glfwSwapBuffers(window);

       // flappys_home.update(prog);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);


}