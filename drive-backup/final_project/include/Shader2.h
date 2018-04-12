//
// Created by Tyler Brown on 4/11/2018.
//

#ifndef FINAL_PROJECT_SHADER_H
#define FINAL_PROJECT_SHADER_H
#include <glad/glad.h>
#include <iostream>

//vertex shader to be used in this project


//fragment shader to be used in this project
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
static void compile_shaders2(GLuint &prog){
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


#endif //FINAL_PROJECT_SHADER_H