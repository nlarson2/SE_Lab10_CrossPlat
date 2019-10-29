
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


*/

#ifndef GAMESCENE_H
#define GAMESCENE_H


//#include <X11/keysym.h>
#include "Image.h"
#include "fonts.h"
#include "glad/glad.h"
#include <GL/gl.h>
#include "GLFW/glfw3.h"
/*
#include "Enemy.h"
#include "Winner.h"
#include "GameOver.h"
#include "Player.h"
*/
#include <stdio.h>

struct Box {
    Image * img;
    float center[2];
    float w;
    float h;
    //[0-1]
    float rgb[3];
};

class GameScene{
    protected:
        int xres, yres;
    public:
        virtual ~GameScene(){}
        virtual void Draw() = 0;
        virtual GameScene * CheckMouse(int x, int y) = 0;
        virtual GameScene * CheckKey(int key) = 0;
        virtual GameScene * Update() = 0;
 };



#endif
