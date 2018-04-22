//
// Created by Tyler Brown on 4/21/2018.
//

#ifndef FINAL_PROJECT_CHARACTER_H
#define FINAL_PROJECT_CHARACTER_H

class character{

    friend class ScoreBoard;


protected:
    //Coordinates to be used when drawing the scoreboard texture to the screen.
    float vertices[32] = {
            // positions          // colors           // texture coords
            1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    //indices of the vertices of the triangles that will contain the scoreboard texture
    unsigned int indices[6] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };


    //variables used to aid reading in the scoreboard texture from an image
    int width, width2, height, height2, nrChannels, nrChannels2;

    //array that contains the data necessary to draw image
    unsigned char *data, *data2;

    //the Scoreboard will have its own buffers too
    unsigned int VBO, VAO, EBO;

    //texture object
    GLuint texture;

    //function to get the correct offsets for the given letter
    void getOffsets(char character);

    //coordinates of the vertices of the specific letter being referenced
    float x_tl, y_tl, x_br, y_br;

    //height and width of each character
    float h,w;

    //which image should be used
    bool use_png_2;



public:

    character(char character){

        //each object on the screen will need to set up its own buffers for objects
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
        data = stbi_load("../textures/letters4.png", &width, &height, &nrChannels, STBI_rgb_alpha);
        data2 = stbi_load("../textures/numbers3.png", &width2, &height2, &nrChannels2, STBI_rgb_alpha);

        w = width/9;
        h = height/3;

        //determine offsets
        getOffsets(character);

        if(data && !use_png_2) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else if(data2 && use_png_2) {

            //this code is used to generate the texture in opengl using the image
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
            glGenerateMipmap(GL_TEXTURE_2D);

        } else {

            std::cout << "Failed to load texture" << std::endl;

        }

        stbi_image_free(data);
        stbi_image_free(data2);

        //setup vertices on the window
        //top right (x,y)
        vertices[0] = 0.03f;
        vertices[1] = 0.03f;

        //bottom right (x,y)
        vertices[8] = 0.03f;
        vertices[9] = -0.03f;

        //top left (x,y)
        vertices[16] = -0.03f;
        vertices[17] = -0.03f;

        //bottom left (x,y)
        vertices[24] = -0.03f;
        vertices[25] = 0.03f;


        //setup vertices on image
        //top right(x,y)
        vertices[6] = x_br;
        vertices[7] = y_tl;

        //bottom right (x,y)
        vertices[14] = x_br;
        vertices[15] = y_br;

        //top left (x,y)
        vertices[30] = x_tl;
        vertices[31] = y_tl;

        //bottom left (x,y)
        vertices[22] = x_tl;
        vertices[23] = y_br;


        //attribute these new vertices with the VAO/VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

        //enable transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    }

};

void character::getOffsets(char character) {

    use_png_2 = false;

    switch(character){

        case 'a':
            x_tl = 0.0f;
            y_tl = 1.0f;
            x_br = 0.0f + 1.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'b':
            x_tl = 0.0f + (1.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 2.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'c':
            x_tl = 0.0f + (2.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 3.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'd':
            x_tl = 0.0f + (3.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 4.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'e':
            x_tl = 0.0f + (4.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 5.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'f':
            x_tl = 0.0f + (5.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 6.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'g':
            x_tl = 0.0f + (6.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 7.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'h':
            x_tl = 0.0f + (7.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 8.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'i':
            x_tl = 0.0f + (8.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 9.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case 'j':
            x_tl = 0.0f;
            y_tl = 1.0f - (1.0f/9.0f);
            x_br = 0.0f + 1.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'k':
            x_tl = 0.0f + (1.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 2.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'l':
            x_tl = 0.0f + (2.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 3.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'm':
            x_tl = 0.0f + (3.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 4.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'n':
            x_tl = 0.0f + (4.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 5.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'o':
            x_tl = 0.0f + (5.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 6.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'p':
            x_tl = 0.0f + (6.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 7.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'q':
            x_tl = 0.0f + (7.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 8.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 'r':
            x_tl = 0.0f + (8.0f/9.0f);
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 9.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case 's':
            x_tl = 0.0f;
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 1.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 't':
            x_tl = 0.0f + (1.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 2.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'u':
            x_tl = 0.0f + (2.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 3.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'v':
            x_tl = 0.0f + (3.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 4.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'w':
            x_tl = 0.0f + (4.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 5.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'x':
            x_tl = 0.0f + (5.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 6.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'y':
            x_tl = 0.0f + (6.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 7.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case 'z':
            x_tl = 0.0f + (7.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 8.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case ' ':
            x_tl = 0.0f + (8.0f/9.0f);
            y_tl = 1.0f - (2.0f/3.0f);
            x_br = 0.0f + 9.0f/9.0f;
            y_br = 1.0f - 3.0f/3.0f;
            break;
        case '0':
            use_png_2 = true;
            x_tl = 0.0f;
            y_tl = 1.0f;
            x_br = 0.0f + 1.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '1':
            use_png_2 = true;
            x_tl = 0.0f + (1.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 2.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '2':
            use_png_2 = true;
            x_tl = 0.0f + (2.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 3.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '3':
            use_png_2 = true;
            x_tl = 0.0f + (3.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 4.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '4':
            use_png_2 = true;
            x_tl = 0.0f + (4.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 5.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '5':
            use_png_2 = true;
            x_tl = 0.0f + (5.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 6.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '6':
            use_png_2 = true;
            x_tl = 0.0f + (6.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 7.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '7':
            use_png_2 = true;
            x_tl = 0.0f + (7.0f/9.0f);
            y_tl = 1.0f;
            x_br = 0.0f + 8.0f/9.0f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '8':
            use_png_2 = true;
            x_tl = 0.0f + (8.0f/9.0f) - 0.01f;
            y_tl = 1.0f;
            x_br = 0.0f + (9.0f/9.0f) + 0.01f;
            y_br = 1.0f - 1.0f/3.0f;
            break;
        case '9':
            use_png_2 = true;
            x_tl = 0.0f;
            y_tl = 1.0f - (1.0f/3.0f);
            x_br = 0.0f + 1.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;
        case ':':
            use_png_2 = true;
            x_tl = 0.0f + (4.0f/9.0f);
            y_tl = 1.0f - 1.0f/3.0f;
            x_br = 0.0f + 5.0f/9.0f;
            y_br = 1.0f - 2.0f/3.0f;
            break;

        default:
        std::cout << "default" << std::endl;


    }


}

#endif //FINAL_PROJECT_CHARACTER_H
