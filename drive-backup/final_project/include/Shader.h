//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_SHADER_H
#define FINAL_PROJECT_SHADER_H
#include <glad/glad.h>
#include <iostream>

//vertex shader to be used in this project
const char* vertex_shader =
        "#version 410\n"
                "layout (location = 0) in vec3 aPos;"
                "layout (location = 1) in vec3 aColor;"
                "layout (location = 2) in vec2 aTexCoord;"
                "out vec3 ourColor;"
                "out vec2 TexCoord;"
                "uniform mat4 transform;"
                "void main () {"
                " gl_Position = transform * vec4(aPos, 1.0);"
                " ourColor = aColor;"
                " TexCoord = aTexCoord;"
                "}";


//fragment shader to be used in this project
const char* frag_shader =
        "#version 330 core\n"
                "out vec4 FragColor;"
                "in vec3 ourColor;"
                "in vec2 TexCoord;"
                "uniform sampler2D ourTexture;"
                "void main()"
                "{"
                "    FragColor = texture(ourTexture, TexCoord);"
                "}";


//this function is used to compile the shaders and link them to the program
static void compile_shaders(GLuint &prog){

    //variables used in the function
    int success;
    GLuint vs, fs;

    //first create the vertex shader object
    vs = glCreateShader(GL_VERTEX_SHADER);
    //linking the vertex shader code to the object we just created
    glShaderSource(vs, 1, &vertex_shader, NULL);
    //now we compile the shader code we just linked the object to
    glCompileShader(vs);


    //now lets do the fragement shader !
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    //linking the fragment shader to the code above
    glShaderSource(fs, 1, &frag_shader, NULL);
    //now we compile the shader code we just linked (hold on to your butts)
    glCompileShader(fs);

    //make sure we were successful in our efforts to compile
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

    if(!success) {

        std::cout << "Fragment Shader failed to compile." << std::endl;
        return;

    } else {

        //now we create the openGL "program" to draw on
        prog = glCreateProgram();

        //now we add the fragment shader to the program
        glAttachShader(prog, fs);

        //and finish with the vertex shader
        glAttachShader(prog, vs);

        //now lets link the program with openGL
        glLinkProgram(prog);


    }

    //now we can get rid of these shaders because they are not needed anymore
    glDeleteShader(fs);
    glDeleteShader(vs);

}


#endif //FINAL_PROJECT_SHADER_H