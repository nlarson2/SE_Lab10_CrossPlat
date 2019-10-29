
/*
Created By: Nickolas Larson
Date: 10/28/2019


*/

#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include <time.h>



class Enemy {
    private:
    int health;
    int choice;
    int xpos, ypos;
    int dir[2];
    bool moving;
    GLuint texture;
    public:
    Enemy(int x, int y, int _dir, int _health);
    void DrawEnemy(int xres, int yres, int x, int y);
    bool CheckPos(int x, int y);
    bool isMoving();
    void CheckForPlayer(int x, int y);
    void Move(int x, int y);
    bool NextToPlayer(int x, int y);
    
    //Enemy picks rock paper or scissors
    int getChoice();
    int getLastChoice();
    int isAlive();
    void hit();
};



#endif
