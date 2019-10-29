
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


*/

#ifndef GAME_CPP
#define GAME_CPP

#include "Game.h"

#include <stdio.h>
#include "Image.h"

#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>
#include "Winner.h"
#include "GameOver.h"

Game::Game(int _xres, int _yres)
{
    xres = _xres;
    yres = _yres;
    player = new Player(40, 53, 0, 10);
    enemies = new Enemy[4] {
        Enemy(46, 72, 0, 2),
        Enemy(86, 1, 0, 2),
        Enemy(32, 29, 0, 3),
        Enemy(6, 7, 3, 3)
    };
    Image::GenerateGLTextureALPHA(playerTextures[0], "images/sprites/player/pFront.png");
    Image::GenerateGLTextureALPHA(playerTextures[1], "images/sprites/player/pBack.png");
    Image::GenerateGLTextureALPHA(playerTextures[2], "images/sprites/player/pLeft.png");
    Image::GenerateGLTextureALPHA(playerTextures[3], "images/sprites/player/pRight.png");

}
Game::~Game()
{
    delete[] enemies;
    delete player;
}
void Game::Draw()
{

    map.drawMap(xres, yres, player->xpos, player->ypos);
    for(int i = 0; i < 4; i++) {
        if(enemies[i].isAlive())
            enemies[i].DrawEnemy(xres, yres, player->xpos, player->ypos);
    }

            
    int w = xres/11.0f + xres/50.0f;
    int h = yres/11.0f + yres/30.0f;
    glBindTexture(GL_TEXTURE_2D, playerTextures[player->dir]);
    glPushMatrix();
    glTranslatef(xres/2.0f, yres/2.0f + yres/30.0f, 0.0f);

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
//no need for mouse in Game
GameScene * Game::CheckMouse(int x, int y) { return nullptr;}

GameScene * Game::CheckKey(int key) 
{
    
    int xpos = player->xpos;
    int ypos = player->ypos;
    
    //MOVE
    switch ((key))
    {
    case GLFW_KEY_ESCAPE:
        return this;
    
    case GLFW_KEY_W://UP
        if(map.isWalkable(xpos, ypos+1))
            if(enemyCheck(xpos, ypos+1)) {
                player->ypos++;
            }
        player->dir = 0;
        break;
    case GLFW_KEY_S://DOWN
        if(map.isWalkable(xpos,ypos-1))
            if(enemyCheck(xpos,ypos-1)) {
                player->ypos--;
            }
        player->dir = 1;
        break;
    case GLFW_KEY_A://LEFT
        if(map.isWalkable(xpos-1, ypos))
            if(enemyCheck(xpos-1, ypos)) {
                player->xpos--;
            }
        player->dir = 2;
        break;
    case GLFW_KEY_D://RIGHT
        if(map.isWalkable( xpos+1, ypos))
            if(enemyCheck(xpos+1, ypos)) {
                player->xpos++;
            }
        player->dir = 3;
        break;
    default:
        break;
    }
    return nullptr;
}

GameScene * Game::Update()
{
    /*Check Lose status*/
    if(player->health == 0) {
        if(!gameOver) {
                gameOver = true;
            return new GameOver(xres, yres);
            } else {
                return this;
            }
    }
    int xpos = player->xpos;
    int ypos = player->ypos;

    /* Move enemy if they are supposed to be moving*/
    UpdateEnemyMoving(ypos, xpos);
    for(int i = 0; i < 4; i++) {
        if(!enemies[i].isAlive())
            continue;
        if(enemies[i].NextToPlayer(xpos, ypos)) {
            
            return new Battle(xres, yres, &enemies[i], player);
        }
        if ( enemies[i].isMoving()) {
            enemies[i].Move(xpos, ypos);
            sleep(2);
            return nullptr;
        }
        
    }
    /*Check Win Status*/
    if( !enemies[0].isAlive() &&  !enemies[1].isAlive() &&
            !enemies[2].isAlive() &&  !enemies[3].isAlive()) {
        
            if(!gameOver) {
                gameOver = true;
            return new Winner(xres, yres);
            } else {
                return this;
            }
    }
    

    return nullptr;
}

bool Game::enemyCheck(int x, int y)
{

    //if an enemy is moving or if in the spot the player
    //is trying to move to then the player can't move
    for (int i = 0; i < 4; i++) {
        if(enemies[i].isAlive())
            if(enemies[i].isMoving() || enemies[i].CheckPos(x,y)) {
                return 0;
            }
    }
    return 1;
}
void Game::UpdateEnemyMoving(int y, int x)
{
    
    //check each enemy to see if a player is in view
    for (int i = 0; i < 4; i++) {
        if(enemies[i].isAlive())
            enemies[i].CheckForPlayer(x,y);
    }
    return;
}

#endif
