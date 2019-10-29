
/*
Created By: Nickolas Larson
Date: 10/28/2019


*/


#ifndef GAMEOVER_H
#define GAMEOVER_H




#include "GameScene.h"


class GameOver : public GameScene {
    private:
        Box exit;
        GLuint loserTexture;
        Image * img;
        bool exitClicked;
    public:
    GameOver(int _xres, int _yres);
    ~GameOver();
    void Draw();
    GameScene * CheckMouse(int x, int y) ;
    GameScene * CheckKey(int key);
    GameScene * Update();
 

};


#endif
