
/*
Created By: Nickolas Larson
Date: 10/28/2019

*/

#ifndef BATTLE_H
#define BATTLE_H


#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>

#include "GameScene.h"
#include "Enemy.h"
#include "Player.h"


class Battle : public GameScene{
    private:
    GLuint hand[3];
    GLuint heartTexture;
    
    Enemy * enemy;
    
    Player * player;
    int playerChoice;

    Box headers[2]; //player and enemy name/health
    Box choices[2]; //player/enemy hands
    Box buttons[3]; //rock paper scissors
    

    public:  
    Battle(int _xres, int _yres, Enemy * _enemy, Player * _player);
    void Draw();
    GameScene * CheckMouse(int x, int y);
    GameScene * CheckKey(int key);
    GameScene * Update() ;

    // play() is called when a player makes a decision
    // When it is called, it makes a call to enemy
    // to find out the enemies decision
    void play();
};


#endif
