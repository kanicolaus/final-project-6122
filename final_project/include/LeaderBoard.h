//
// Created by Tyler Brown on 4/23/2018.
//

#ifndef FINAL_PROJECT_LEADERBOARD_H
#define FINAL_PROJECT_LEADERBOARD_H

class LeaderBoard{

protected:

    //bool to tell the object when the game is over
    bool gameOver;

    //character object arrays to hold the three top scores
    character **p1, **p2, **p3;

    //string equivalent of the player strings above
    std::string sp1,sp2,sp3;

    //length of each string (including the numbers)
    int p1_len, p2_len, p3_len;

    //their numeric scores also
    int p1_score, p2_score, p3_score;

    //array of character objects that hold's the games resulting message (game over or New HighScore!)
    character **gameResult;

    //array of characters to give instructions
    character **instructions;

    //integers to represent the lengths of the gameResult and instruction strings
    int gR_len, i_len;

    //offset values to draw the leader board on the screen
    float leftx, lefty;


public:

    //variable to keep track of key strokes
    static int keystrokes;
    static int which;

    LeaderBoard() : gR_len(0), i_len(0){

        //define beginning value of leftx and lefty
        leftx = 0.0f;
        lefty = 0.1f;


        //Now read in the leader board from a .csv file
        std::ifstream inLeaderboard("../Files/Results.txt");

        if(!inLeaderboard){

            //set default values when file doesnt yet exist
            p1_score = 0;
            p2_score = 0;
            p3_score = 0;

            sp1 = "ttt";
            sp2 = "ggg";
            sp3 = "bbb";

            p1_len = 7;
            p2_len = 7;
            p3_len = 7;

            p1 = new character*[7];
            p2 = new character*[7];
            p3 = new character*[7];

            for(int i = 0; i < 3; ++i){

                p1[i] = new character('t');
                p2[i] = new character('g');
                p3[i] = new character('b');

            }

            p1[3] = new character(' ');
            p2[3] = new character(' ');
            p3[3] = new character(' ');

            for(int i = 0; i < 3; ++i){

                p1[i+4] = new character('0');
                p2[i+4] = new character('0');
                p3[i+4] = new character('0');

            }

        } else {

            //otherwise read in the lines from the file
            getline(inLeaderboard, sp1);
            getline(inLeaderboard, sp2);
            getline(inLeaderboard, sp3);

            //save length of each string
            p1_len = strlen(sp1.c_str());
            p2_len = strlen(sp2.c_str());
            p3_len = strlen(sp3.c_str());


            //make the character arrays
            p1 = new character*[p1_len];
            p2 = new character*[p2_len];
            p3 = new character*[p3_len];


            //get the numeric part and store it
            p1_score = (int) atof(sp1.substr(sp1.find(' ') + 1).c_str());
            p2_score = (int) atof(sp2.substr(sp2.find(' ') + 1).c_str());
            p3_score = (int) atof(sp3.substr(sp3.find(' ') + 1).c_str());


            //now generate the character textures
            int i = 0;
            for(auto thing : sp1){

                p1[i] = new character(thing);
                ++i;
            }

            i = 0;
            for(auto thing : sp2){

                p2[i] = new character(thing);
                ++i;
            }

            i = 0;
            for (auto thing : sp3){

                p3[i] = new character(thing);
                ++i;
            }

            //now keep only the characters in the strings
            sp1 = sp1.substr(0, sp1.find(' '));
            sp2 = sp2.substr(0, sp2.find(' '));
            sp3 = sp3.substr(0, sp3.find(' '));

            inLeaderboard.close();

        }



    }

    void draw(GLuint prog){

        float offset;

        for(int i = 0; i < gR_len; ++i){

            //switch to this object's VAO
            glBindVertexArray(gameResult[i] -> VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + ((float)i - ((float)gR_len/2)) * 0.032f) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty + 0.2f, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, gameResult[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        }

        for(int i = 0; i < i_len; ++i){

            //switch to this object's VAO
            glBindVertexArray(instructions[i] -> VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + ((float)i - (float)i_len/2) * 0.032f) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty + 0.1f, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, instructions[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        }



        for(int i = 0; i < p1_len; ++i){

            //switch to this object's VAO
            glBindVertexArray(p1[i] -> VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + ((float)i - (float)p1_len/2) * 0.032f) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, p1[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

        for(int i = 0; i < p2_len; ++i){

            //switch to this object's VAO
            glBindVertexArray(p2[i] -> VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + ((float)i - (float)p2_len/2) * 0.032f) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty - 0.1f, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, p2[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }

        for(int i = 0; i < p3_len; ++i){

            //switch to this object's VAO
            glBindVertexArray(p3[i] -> VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + ((float)i - (float)p3_len/2) * 0.032f) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty - 0.2f, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, p3[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }
    }

    //function to update the appropriate score on the leaderboard
    //this function should only be called once when the game is done
    void changeScore(int score){

        std::string instr, result;

        if(score > p1_score){

            which = 0;

            //set the strings to be written to the screen
            instr = "please enter your name: ";
            result = "new highscore";

            //make the character arrays for the instructions and game result
            gR_len = strlen(result.c_str());
            i_len = strlen(instr.c_str());

            gameResult = new character*[gR_len];
            instructions = new character*[i_len];

            for(int i = 0; i < gR_len; ++i){

                gameResult[i] = new character(result[i]);

            }

            for(int i = 0; i < i_len; ++i){

                instructions[i] = new character(instr[i]);
            }

            //update the correct score keep track of old one
            int temp_score = p1_score;
            p1_score = score;

            //keep the old length temporarily
            int temp_p1_len = p1_len;

            //change the length
            p1_len = 4 + strlen(std::to_string(score).c_str());

            //dynamically allocate a new array for p1
            character** temp_array = new character*[p1_len];

            //deepcopy the name from old p1 to new p1
            for(int i = 0; i < 4; ++i){

                temp_array[i] = new character(p1[i]->getSymbol());

            }

            //delete p3 since he is being pushed off the list
            for(int i = 0; i < p3_len; ++i){

                delete p3[i];
            }

            delete[] p3;

            //shift everything down the list
            //make sure to change the lengths as well
            p3 = p2;
            sp3 = sp2;
            p3_score = p2_score;
            p3_len = p2_len;

            p2 = p1;
            sp2 = sp1;
            p2_score = temp_score;
            p2_len = temp_p1_len;

            p1 = temp_array;

            //now put in the new score
            for(int i = 4; i < p1_len; ++i){

                p1[i] = new character(std::to_string(p1_score)[i-4]);

            }

        } else if(score == p1_score || score > p2_score){

            which = 1;

            //set the strings to be written to the screen
            instr = "please enter your name: ";
            result = "game over";

            //make the character arrays for the instructions and game result
            gR_len = strlen(result.c_str());
            i_len = strlen(instr.c_str());

            gameResult = new character*[gR_len];
            instructions = new character*[i_len];

            for(int i = 0; i < gR_len; ++i){

                gameResult[i] = new character(result[i]);

            }

            for(int i = 0; i < i_len; ++i){

                instructions[i] = new character(instr[i]);
            }

            //update the correct score and keep track of old one
            int temp_score = p2_score;
            p2_score = score;

            //keep the old length temporarily
            int temp_p2_len = p2_len;

            //change the length
            p2_len = 4 + strlen(std::to_string(score).c_str());

            //dynamically allocate a new array for p2
            character** temp_array = new character*[p2_len];

            //deepcopy the name from old p2 to new p2
            for(int i = 0; i < 4; ++i){

                temp_array[i] = new character(p2[i]->getSymbol());

            }

            //delete p3 since he is being pushed off the list
            for(int i = 0; i < p3_len; ++i){

                delete p3[i];
            }

            delete[] p3;

            //shift everything down the list
            //make sure to change the lengths as well
            p3 = p2;
            sp3 = sp2;
            p3_score = temp_score;
            p3_len = temp_p2_len;

            p2 = temp_array;

            //now put in the new score
            for(int i = 4; i < p2_len; ++i){

                p2[i] = new character(std::to_string(p2_score)[i-4]);

            }

        } else if(score == p2_score || score > p3_score){//if newest score is greater than p3 score and less than or equal to p2's

            //std::cout << "test" << std::endl;

            which = 2;

            //set the strings to be written to the screen
            instr = "please enter your name: ";
            result = "game over";

            //make the character arrays for the instructions and game result
            gR_len = strlen(result.c_str());
            i_len = strlen(instr.c_str());

            gameResult = new character*[gR_len];
            instructions = new character*[i_len];

            for(int i = 0; i < gR_len; ++i){

                gameResult[i] = new character(result[i]);

            }

            for(int i = 0; i < i_len; ++i){

                instructions[i] = new character(instr[i]);
            }

            //update the correct score
            p3_score = score;

            //keep the old length temporarily
            int temp_p3_len = p3_len;

            //std::cout << p3_len << std::endl;

            //change the length
            p3_len = 4 + strlen(std::to_string(score).c_str());

            //dynamically allocate a new array for p1
            character** temp_array = new character*[p3_len];

           // std::cout << "test3" << std::endl;

            //deepcopy the name from old p1 to new p1
            for(int i = 0; i < 4; ++i){

                temp_array[i] = new character(p3[i]->getSymbol());

            }

           // std::cout << "test4" << std::endl;

            //delete p3 since he is being pushed off the list
            for(int i = 0; i < p3_len; ++i){

                delete p3[i];
            }

            delete[] p3;


            //shift everything down the list
            //make sure to change the lengths as well
            p3 = temp_array;

            //now put in the new score
            for(int i = 4; i < p3_len; ++i){

                p3[i] = new character(std::to_string(p3_score)[i-4]);

            }

        } else {

            which = -1;

            //set the strings to be written to the screen
            instr = "better luck next time";
            result = "game over";

            //make the character arrays for the instructions and game result
            gR_len = strlen(result.c_str());
            i_len = strlen(instr.c_str());

            gameResult = new character*[gR_len];
            instructions = new character*[i_len];

            for(int i = 0; i < gR_len; ++i){

                gameResult[i] = new character(result[i]);

            }

            for(int i = 0; i < i_len; ++i){

                instructions[i] = new character(instr[i]);
            }

        }

    }

    //this function is only used to change letters in the leaderboard when the user hits a key
    void changeName(char letter){


        if(keystrokes > 3){

            return;
        }

        //if the first its a new highscore
        if(which == 0){

            //make sure only 3 letters entered
            switch (keystrokes) {

                case 1:

                    delete p1[0];
                    p1[0] = new character(letter);
                    sp1[0] = letter;
                    break;

                case 2:

                    delete p1[1];
                    p1[1] = new character(letter);
                    sp1[1] = letter;
                    break;

                case 3:

                    delete p1[2];
                    p1[2] = new character(letter);
                    sp1[2] = letter;
                    break;
            }

        } else if(which == 1){

            //make sure only 3 letters entered
            switch (keystrokes) {

                case 1:

                    delete p2[0];
                    p2[0] = new character(letter);
                    sp2[0] = letter;
                    break;

                case 2:

                    delete p2[1];
                    p2[1] = new character(letter);
                    sp2[1] = letter;
                    break;

                case 3:

                    delete p2[2];
                    p2[2] = new character(letter);
                    sp2[2] = letter;
                    break;
            }

        } else if(which == 2) {

            //make sure only 3 letters entered
            switch (keystrokes) {

                case 1:

                    delete p3[0];
                    p3[0] = new character(letter);
                    sp3[0] = letter;
                    break;

                case 2:

                    delete p3[1];
                    p3[1] = new character(letter);
                    sp3[1] = letter;
                    break;

                case 3:

                    delete p3[2];
                    p3[2] = new character(letter);
                    sp3[2] = letter;
                    break;
            }
        }

    }

    //function to set the game over variable
    void setGameOver(bool game){

        this -> gameOver = game;
    }

    bool getGameOver(){

        return this -> gameOver;

    }


    ~LeaderBoard(){

        std::ofstream ofile("../Files/Results.txt");

        ofile << sp1 << " " << p1_score << std::endl;
        ofile << sp2 << " " << p2_score << std::endl;
        ofile << sp3 << " " << p3_score << std::endl;

        for(int i = 0; i < p1_len; ++i){

            delete p1[i];
        }

        delete[] p1;

        for(int i = 0; i < p2_len; ++i){

            delete p2[i];
        }

        delete[] p2;

        for(int i = 0; i < p3_len; ++i){

            delete p3[i];
        }

        delete[] p3;

        if(i_len != 0) {

            for (int i = 0; i < i_len; ++i) {


                delete instructions[i];

            }

            delete[] instructions;

        }

        if(gR_len != 0) {

            for (int i = 0; i < gR_len; ++i) {

                delete gameResult[i];
            }

            delete[] gameResult;
        }


        ofile.close();

    }
};

int LeaderBoard::keystrokes = 3;
int LeaderBoard::which = -1;


#endif //FINAL_PROJECT_LEADERBOARD_H
