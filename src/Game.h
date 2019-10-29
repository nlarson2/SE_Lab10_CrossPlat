
/*
Created By: Nickolas Larson
Date: 10/28/2019


*/



#ifndef GAME_H
#define GAME_H


#include <unistd.h>

#include "GameScene.h"
#include "Battle.h"
#include "Map.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"



class Game : public GameScene {


    GLuint playerTextures[4];
    int gameOver = false;
    Enemy * enemies;
    Player * player;
    Map map;
    public:
    Game(int _xres, int _yres);
    ~Game();

    void Draw();
    GameScene * CheckMouse(int x, int y);

    GameScene * CheckKey(int key);
    GameScene * Update();

    //used to see if an enemy is in the spot that
    // the users is trying to move to
    bool enemyCheck(int x, int y);
    void UpdateEnemyMoving(int y, int x);

};


#endif
