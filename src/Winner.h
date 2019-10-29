
/*
Created By: Nickolas Larson
Date: 10/28/2019
*/

#ifndef WINNER_H
#define WINNER_H


#include "GameScene.h"


class Winner : public GameScene {
    private:
        Box exit;
        GLuint winnerTexture;
        Image * img;
        bool exitClicked;
    public:
    Winner(int _xres, int _yres);
    ~Winner();
    void Draw();
    GameScene * CheckMouse(int x, int y);
    GameScene * CheckKey(int key);
    GameScene * Update();
 

};


#endif
