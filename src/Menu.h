
/*
Created By: Nickolas Larson
Date: 10/28/2019

*/

#ifndef MENU_H
#define MENU_H

#include <stdio.h>

#include "GameScene.h"


class Menu : public GameScene{
    private: 
        Box start;
        Image * title;
        GLuint titleTexture;
    public:
        Menu(int _xres, int _yres);
        ~Menu();
        void Draw();
        GameScene * CheckMouse(int x, int y);
        GameScene * CheckKey(int key);
        GameScene * Update(){return nullptr;}
         
};


#endif
