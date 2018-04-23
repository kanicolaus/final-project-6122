//
// Created by Tyler Brown on 4/21/2018.
//

#ifndef FINAL_PROJECT_SCOREBOARD_H
#define FINAL_PROJECT_SCOREBOARD_H

#include <fstream>
#include <string>
#include "character.h"
#include <future>

//class to represent the scoreboard/score on results screen
class ScoreBoard {


protected:

    //bool to represent the state of the game so that I can draw either a leaderboard or a score
    bool gameOver;

    //array to store all the numbers so they can be swapped out faster
    character **numbers;

    //array to hold the constant "score: " character set
    character **score;

    //character object arrays to hold the three top scores
    character **p1, **p2, **p3;

    //their numeric scores also
    int p1_score, p2_score, p3_score;

    //array of character objects that hold's the games resulting message (game over or New HighScore!)
    character **gameResult;

//    //file to keep track of the scores after the game ends
//    std::ifstream inLeaderboard;
//    std::ofstream outLeaderboard;

    //integer to keep track of how many letters/numbers are on the screen
    int strLen;

    //integer to keep track of the numerical score
    int num_score;

    //numbers to represent the x and y coordinates of the top left most point on the character being displayed
    float leftx, lefty;

    //timer for increasing score
    std::chrono::time_point<std::chrono::high_resolution_clock> start, finish;



public:

    ScoreBoard(){

        //intially the game is not over
        gameOver = false;

        //strLen is initially 8 because "score: " will always be displayed
        strLen = 7;

        //intially the score is zero
        num_score = 0;

        //initially the starting position is in the bottom right corner of the screen
        leftx = 1.0f - strLen * (0.05f);
        lefty = -1.0f + 0.2f;

        //load the word score in permanently
        score = new character*[7];

        score[0] = new character('s');
        score[1] = new character('c');
        score[2] = new character('o');
        score[3] = new character('r');
        score[4] = new character('e');
        score[5] = new character(':');
        score[6] = new character(' ');

        numbers = new character*[10];

        for(int i = 0; i < 10; ++i){

            numbers[i] = new character(*(std::to_string(i).c_str()));

        }

        //start the timer
        start = std::chrono::high_resolution_clock::now();

    }

    void update(){

        finish = std::chrono::high_resolution_clock::now();

        int new_score = (int)(std::chrono::duration_cast<std::chrono::seconds>(finish - start).count());

        if(new_score == num_score){

            return;

        } else {

            num_score = new_score;
            strLen = std::to_string(new_score).size() + 7;
            leftx = 1.0f - strLen * (0.05f);

        }
    }

    void draw(GLuint prog) {

        int count = 0;

        float offset;

        for (int i = 0; i < 7; ++i){


            //switch to this object's VAO
            glBindVertexArray(score[i]->VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset = (leftx + i * 0.03f)* 1.182f;
            transform = glm::translate(transform, glm::vec3(offset, lefty, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, score[i]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        }

        float offset2;

        for(auto & thing : std::to_string(num_score)){

            //switch to this object's VAO
            glBindVertexArray(numbers[(char)(thing - 48)]->VAO);

            glm::mat4 transform = glm::mat4(1.0f);
            offset2 = ((leftx + (count + 7) * 0.032f) ) * 1.182f;
            transform = glm::translate(transform, glm::vec3(offset2, lefty, 0.0f));
            GLint transformLoc = glGetUniformLocation(prog, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

            glBindTexture(GL_TEXTURE_2D, numbers[(char)(thing-48)]->texture);

            //draw the texture
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            count++;
        }

        update();


    }

    void setGameOver(bool game){

        this -> gameOver = game;
    }



    //TODO: read in old scores from file
    //TODO: implement if statement in draw that draws leaderboard when gameOver is true
    //TODO: allow text input via interrupts when game is over, but only change appropriate value in leader board (use below function)
    //TODO: write results to the file in destructor


    void displayResults(char letter){

        std::ifstream inLeaderboard("Results.csv");
        std::string result;

        if(!inLeaderboard){

            result = "New HighScore";
        }
    }




    ~ScoreBoard() {

        for(int i = 0; i < 7; ++i){

            delete score[i];

        }

        for(int j = 0; j < 10; ++j){

            delete numbers[j];
        }

        delete[] score;
        delete[] numbers;
    }


};

#endif //FINAL_PROJECT_SCOREBOARD_H
