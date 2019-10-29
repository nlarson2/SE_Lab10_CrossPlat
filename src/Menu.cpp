
/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


*/



#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include "Game.h"


Menu::Menu(int _xres, int _yres)
{
    xres = _xres;
    yres = _yres;
    title = new Image("images/title.png");
    //position start button on the bottom middle of the screen
    start.center[0] = xres/2.0f;
    start.center[1] = yres/4.0f;
    //wider than it is tall
    start.w = xres/8.0f;
    start.h = yres/15.0f;

    start.rgb[0] = 1.0f;
    start.rgb[1] = 0;
    start.rgb[2] = 0;

    title->GenerateGLTexture(titleTexture);
}
Menu::~Menu()
{
    delete title;
}
void Menu::Draw()
{
    // printf("Center(x/y) : %f %f\n", start.center[0], start.center[1]);
    

    glLoadIdentity();

    float w;
    float h;
    float * rgb;
    /*Title*/
    glPushMatrix();
    w = 250;
    h = 150;
    glTranslatef(xres/2, yres/2 + 200, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, titleTexture);
    glBegin(GL_QUADS);
        glTexCoord2f(0.00, 0.99);glVertex2f(-w, -h);
        glTexCoord2f(0.00, 0.00);glVertex2f(-w,  h);
        glTexCoord2f(1.00, 0.00);glVertex2f( w,  h);
        glTexCoord2f(1.00, 0.99);glVertex2f( w, -h);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    /*Start Button*/
    glPushMatrix();
    w = start.w;
    h = start.h;
    rgb = start.rgb;
    glTranslatef(start.center[0], start.center[1], 0.0f);
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
    Rect r;
    r.bot = (int)start.center[1] - 5;
    r.left = (int)start.center[0];;
    ggprint16(&r, 16, 0xFFFFFFFF, "START");
}


GameScene * Menu::CheckMouse(int x, int y) {
        
        if (x > start.center[0] - start.w && x < start.center[0] + start.w ) {
            if (y > start.center[1] - start.h && y < start.center[1] + start.h ) {
                printf("Return game\n");
                return new Game(xres,yres);
            }
        }
        return nullptr;

}
GameScene * Menu::CheckKey(int key) {
    if (key == GLFW_KEY_ESCAPE) {
        return this;
    }
    return nullptr;
}
      




#endif
