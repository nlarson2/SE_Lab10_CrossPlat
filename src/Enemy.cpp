
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


*/

#ifndef ENEMY_CPP
#define ENEMY_CPP


#include <stdio.h>
#include "Image.h"

#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>
#include "Enemy.h"

static const int 
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3;

Enemy::Enemy(int x, int y, int _dir, int _health) {
    srand(time(nullptr));
    xpos = x;
    ypos = y;
    health = _health;
    moving = 0;
    choice = 0;
    switch(_dir) {
        case 0:
            Image::GenerateGLTextureALPHA(texture, "images/sprites/enemy/eFront.png");
            dir[0] =  0;
            dir[1] =  1;
            break;
        case 1:
            Image::GenerateGLTextureALPHA(texture, "images/sprites/enemy/eBack.png");
            dir[0] = 0;
            dir[1] = -1;
            break;
        case 2:
            Image::GenerateGLTextureALPHA(texture, "images/sprites/enemy/eLeft.png");
            dir[0] = -1;
            dir[1] =  0;
            break;
        case 3:
            Image::GenerateGLTextureALPHA(texture, "images/sprites/enemy/eRight.png");
            dir[0] =  1;
            dir[1] =  0;
            break;
        default:
            printf("ERROR ON ENEMY TEXTURE\n");
            //exit(-1);
    }


}


void Enemy::DrawEnemy(int xres, int yres, int x, int y) {
    int xdist = x - xpos;
    int ydist = y - ypos;
    if (abs(xdist) < 6 && abs(ydist) < 6) {
        int w = xres/11.0f + xres/50.0f;
        int h = yres/11.0f + yres/30.0f;
        glBindTexture(GL_TEXTURE_2D, texture);

        glPushMatrix();
            glLoadIdentity();
            glTranslatef(xres/2.0f, yres/2.0f + yres/30.0f, 0.0f);
            glTranslatef(xres/11.0f * xdist, yres/11.0f * ydist, 0.0f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBegin(GL_QUADS);
            /*!!!!!DO NOT MESS WITH THE TEXTURE COORDINATES!!!!!*/
                glTexCoord2f(0.025, 0.975);glVertex2f(-w/2.0f, -h/2.0f);
                glTexCoord2f(0.025, 0.025);glVertex2f(-w/2.0f,  h/2.0f);
                glTexCoord2f(0.975, 0.025);glVertex2f( w/2.0f,  h/2.0f);
                glTexCoord2f(0.975, 0.975);glVertex2f( w/2.0f, -h/2.0f);
            glEnd();
            glDisable(GL_BLEND);
        glPopMatrix();
    }
}

bool Enemy::CheckPos(int x, int y) {

    if (x == xpos && y == ypos) {
        return 1;
    }
    return 0;
}

bool Enemy::isMoving()
{
    return moving;
}
void Enemy::CheckForPlayer(int x, int y)
{
    int tmpx = xpos + dir[0];
    int tmpy = ypos + dir[1];

    for(int i = 0; i < 4; i++) {
        if (tmpx == x && tmpy == y) {
            moving = 1;
        }
        tmpx += dir[0];
        tmpy += dir[1];
    }
}
void Enemy::Move(int x, int y) {
    int tmpx = xpos + dir[0];
    int tmpy = ypos + dir[1];
    if(moving) {
        if(tmpx == x && tmpy == y) {
            moving = false;
        } else {
            xpos += dir[0];
            ypos += dir[1];
        }
    }
}

bool Enemy::NextToPlayer(int x, int y)
{
    int tmpx = xpos + dir[0];
    int tmpy = ypos + dir[1];
    if (tmpx == x && tmpy == y) {
        
        return true;
    }
    return false;
}

int Enemy::getChoice()
{
    choice = rand()%3;
    return choice;
}
int Enemy::getLastChoice()
{
    return choice;
}
int Enemy::isAlive()
{
    return health;
}
void Enemy::hit()
{
    health--;
}



#endif
