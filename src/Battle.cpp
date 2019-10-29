
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:

Notes:

    
*/

#ifndef BATTLE_CPP
#define BATTLE_CPP

#include "Battle.h"

#include "Image.h"

#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>
#include "fonts.h"

#include <stdio.h>

Battle::Battle(int _xres, int _yres, Enemy * _enemy, Player * _player)
{

    xres = _xres;
    yres = _yres;
    enemy = _enemy;
    player = _player;
    playerChoice = 0;


    Image::GenerateGLTextureALPHA(hand[0], "images/sprites/pRock.png");
    Image::GenerateGLTextureALPHA(hand[1], "images/sprites/pPaper.png");
    Image::GenerateGLTextureALPHA(hand[2], "images/sprites/pScissors.png");
    Image::GenerateGLTextureALPHA(heartTexture, "images/sprites/heart.png");


    /*****all hard coded since they will never be any different********/
    headers[0].center[0] = 150;
    headers[0].center[1] = yres-80;
    headers[0].w = 130;
    headers[0].h = 30;
    headers[0].rgb[0] = 0.0f;        
    headers[0].rgb[1] = 0.0f;
    headers[0].rgb[2] = 1.0f;
    headers[1].center[0] = xres-120;
    headers[1].center[1] = yres -80;
    headers[1].w = 110;
    headers[1].h = 30;
    headers[1].rgb[0] = 1.0f;        
    headers[1].rgb[1] = 0.0f;
    headers[1].rgb[2] = 0.0f;

    choices[0].center[0] = xres/4;
    choices[0].center[1] = yres/2;
    choices[0].w = 150;
    choices[0].h = 150;
    choices[0].rgb[0] = 0.0f;        
    choices[0].rgb[1] = 0.0f;
    choices[0].rgb[2] = 1.0f;
    choices[1].center[0] = xres - xres/4;
    choices[1].center[1] = yres/2;
    choices[1].w = 150;
    choices[1].h = 150;
    choices[1].rgb[0] = 1.0f;        
    choices[1].rgb[1] = 0.0f;
    choices[1].rgb[2] = 0.0f;

    buttons[0].center[0] = 140;
    buttons[0].center[1] = yres/6;
    buttons[0].w = 90;
    buttons[0].h = 30;
    buttons[0].rgb[0] = 0.0f;        
    buttons[0].rgb[1] = 1.0f;
    buttons[0].rgb[2] = 0.0f;
    buttons[1].center[0] = 400;
    buttons[1].center[1] = yres/6;
    buttons[1].w = 90;
    buttons[1].h = 30;
    buttons[1].rgb[0] = 0.0f;        
    buttons[1].rgb[1] = 1.0f;
    buttons[1].rgb[2] = 0.0f;
    buttons[2].center[0] = 400 + 260;
    buttons[2].center[1] = yres/6;
    buttons[2].w = 90;
    buttons[2].h = 30;
    buttons[2].rgb[0] = 0.0f;        
    buttons[2].rgb[1] = 1.0f;
    buttons[2].rgb[2] = 0.0f;
    /****************************************************************/
}


void Battle::Draw()
{
    float w, h;
    float * rgb;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(headers[i].center[0], headers[i].center[1], 0.0f);

        w = headers[i].w;
        h = headers[i].h;
        rgb = headers[i].rgb;
        /*************Draw Headers******************/
        /****Border****/
        glColor3f(rgb[0], rgb[1], rgb[2]);
        glBegin(GL_QUADS);            
            glVertex2f(-w, -h);
            glVertex2f(-w,  h);
            glVertex2f( w,  h);
            glVertex2f( w, -h);
        glEnd();

        /****Fill****/
        glColor3f(0,0,0);
        glBegin(GL_QUADS);            
            glVertex2f(-w + 4,-h + 4);
            glVertex2f(-w + 4, h - 4);
            glVertex2f( w - 4, h - 4);
            glVertex2f( w - 4,-h + 4);
        glEnd();

        /****hearts****/
        glTranslatef(-w, 0.0f, 0.0f);
        glPushMatrix();
        w = xres/40.0f;
        h = yres/40.0f;
        glTranslatef(w, 0, 0);
        int healthCount = (i == 0) ? player->health : enemy->isAlive();
        if(i > 6) exit(-1);
        glBindTexture(GL_TEXTURE_2D, heartTexture);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor3f(1.0f,1.0f,1.0f);
        for(int j = 0; j < healthCount; j++) {
            glBegin(GL_QUADS);
                glTexCoord2f(0.00, 0.99);glVertex2f(-w/2, -h/2);
                glTexCoord2f(0.00, 0.00);glVertex2f(-w/2,  h/2);
                glTexCoord2f(1.00, 0.00);glVertex2f( w/2,  h/2);
                glTexCoord2f(1.00, 0.99);glVertex2f( w/2, -h/2);
            glEnd();
            glTranslatef(w+w/4, 0, 0);

        }
        glBindTexture(GL_TEXTURE_2D, 0);

        /****Names****/
        glPopMatrix();
        glPopMatrix();
        glLoadIdentity();
        Rect r;
        r.bot = (int)headers[i].center[1] + 2 * h;
        r.left = (int)headers[i].center[0];;
        ggprint16(&r, 16, 0xFFFFFFFF, i == 0 ? "PLAYER":"ENEMY");


        /**********************Last Choice**********************************/
        int choice = i == 0 ? playerChoice: enemy->getLastChoice();
        glPushMatrix();
        if (choice > 0) {

            glTranslatef(choices[i].center[0], choices[i].center[1], 0.0f);
            w = choices[i].w;
            h = choices[i].h;
            rgb = choices[i].rgb;

            /*Background*/
            glColor3f(rgb[0], rgb[1], rgb[2]);
            glBegin(GL_QUADS);            
                glVertex2f(-w, -h);
                glVertex2f(-w,  h);
                glVertex2f( w,  h);
                glVertex2f( w, -h);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, hand[choice-1]);
            glBegin(GL_QUADS);
            /*!!!!!DO NOT MESS WITH THE TEXTURE COORDINATES!!!!!*/

                if(i == 0) {
                    //Player Hand
                    glTexCoord2f(0.025, 0.975);glVertex2f(-w/2.0f, -h/2.0f);
                    glTexCoord2f(0.025, 0.025);glVertex2f(-w/2.0f,  h/2.0f);
                    glTexCoord2f(0.975, 0.025);glVertex2f( w/2.0f,  h/2.0f);
                    glTexCoord2f(0.975, 0.975);glVertex2f( w/2.0f, -h/2.0f);
                } else {
                    //Enemy Hand
                    glTexCoord2f(0.975, 0.975);glVertex2f(-w/2.0f, -h/2.0f);
                    glTexCoord2f(0.975, 0.025);glVertex2f(-w/2.0f,  h/2.0f);
                    glTexCoord2f(0.025, 0.025);glVertex2f( w/2.0f,  h/2.0f);
                    glTexCoord2f(0.025, 0.975);glVertex2f( w/2.0f, -h/2.0f);
                }
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
            
        }
        glPopMatrix();
        
        glDisable(GL_BLEND);


    }

    /*******************************Buttons************************************/
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(buttons[i].center[0], buttons[i].center[1], 0.0f);

        w = buttons[i].w;
        h = buttons[i].h;
        rgb = buttons[i].rgb;

        /*Border*/
        glColor3f(rgb[0], rgb[1], rgb[2]);
        glBegin(GL_QUADS);            
            glVertex2f(-w, -h);
            glVertex2f(-w,  h);
            glVertex2f( w,  h);
            glVertex2f( w, -h);
        glEnd();

        /*Fill*/
        glColor3f(0,0,0);
        glBegin(GL_QUADS);            
            glVertex2f(-w + 4,-h + 4);
            glVertex2f(-w + 4, h - 4);
            glVertex2f( w - 4, h - 4);
            glVertex2f( w - 4,-h + 4);
        glEnd();
        glPopMatrix();

        glLoadIdentity();
        Rect r;
        r.bot = (int)buttons[i].center[1] - 5.0f;
        r.left = (int)buttons[i].center[0];;
        ggprint16(&r, 16, 0xFFFFFFFF, i == 0 ? "ROCK": i == 1 ? "PAPER" : "SCISSORS");
    }
}
GameScene * Battle::CheckMouse(int x, int y)
{
    for (int i = 0; i < 3; i++) {
        if ( x > buttons[i].center[0] - buttons[i].w && x < buttons[i].center[0] + buttons[i].w ) {
            if (yres - y > buttons[i].center[1] - buttons[i].h && yres - y < buttons[i].center[1] + buttons[i].h ) {
                switch (i)
                {
                case 0:
                    playerChoice = 1;
                    play();
                    break;
                case 1:
                    playerChoice = 2;
                    play();
                    break;
                case 2:
                    playerChoice = 3;
                    play();
                    break;
                default:
                    break;
                }
                if(!enemy->isAlive())
                    return this;
            }
        }
    }
    return nullptr;
}
GameScene * Battle::CheckKey(int key)
{
        if (key == GLFW_KEY_ESCAPE) {
        return this;
    }
    return nullptr;
}
GameScene * Battle::Update() {
    
    if(!enemy->isAlive() || player->health == 0) {
        return this;
    } 
    return nullptr;
    
}

void Battle::play() {
    int enemyChoice = enemy->getChoice();
    if((playerChoice==1 && enemyChoice==2)||(playerChoice==2 && enemyChoice==3)||(playerChoice==3 && enemyChoice==1))
        player->health -= 1;
        
    if((playerChoice==2 && enemyChoice==1)||(playerChoice==3 && enemyChoice==2)||(playerChoice==1 && enemyChoice==3))
        enemy->hit();

    return;
}

#endif
