//All windows creations and function X11 functions from waterfall or particle framework By Gordon Griesel

//Main taken from Fate The Shadow Wizard Kingdom Darkness Revived 2 The Second one
//which was created from the particles framework

//Modified by: Nickolas Larson
//Date:        10/05/2019 


#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <unistd.h>
#include <stack>

#include "src/fonts.h"


#include "src/GameScene.h"
#include "src/Menu.h"
using namespace std;

/********************************************************
- Key points to look at about GameScenes
    -Stack
        In this game I created stack to determine which
        state of the game that the the user is in.
        Stack will look something like this in a battle
        
            top->   Battle
                    Game
         bottom->   Menu
        
        If the player defeats their enemy, the battle
        scene will pop off of the top of that stack so
        that the main loop will start running the Game
        scene again
            top->   Game
         bottom->   Menu

        If the user presses escape at this point
        the Game scene will pop off the top and the 
        main loop will start running the menu scene again
        
         bottom and top->  Menu

    -Required Functions
        The GameScene class is an abstract class that 
        requires its child classes to have four 
        fucntions:
            Draw        
            CheckMouse
            CheckKey
            Update
        The purpose of this is so that you can identical
        function calls when these class are stared in a 
        GameScene pointer.
            example: GameScene * scene = new Menu(xres, yres);
        This example can then be stored on the stack to 
        easily move through scenes.
    
    -Changing scenes   
        Some GameScenes return a GameScene pointer.
        The purpose of this is to figure out if a scene 
        needs to be pop off or push onto the stack.
        If a new GameScene is returned, it pushes that
        new scene. If the current scene is sent back
        using the "this" pointer then it pops that 
        GameScene off of the stack. Lastely if nullptr
        is returned, then nothing happens.



********************************************************/


class Global {
    public:
        int xres, yres;
        int n;
        int count;
        bool ctrls = true;
        int done = 0;
        bool quit;
        //holds game scenes
        stack<GameScene*> scene;
        static Global * GetInstance()
        {
            if (!instance)
                instance = new Global();
            return instance;
        }
    private:
        static Global * instance;
        Global() {
            xres = 800;
            yres = 800;
            count = 0;
            quit = false;
        }
        Global(Global const& copy);
        Global & operator=(Global const& copy);

};
Global* Global::instance = 0;
Global * g = Global::GetInstance();

class X11_wrapper {
    private:
        Display *dpy;
        Window win;
        GLXContext glc;
    public:
        ~X11_wrapper() {
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
        }
        X11_wrapper() {
            GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            int w = g->xres, h = g->yres;
            dpy = XOpenDisplay(NULL);
            if (dpy == NULL) {
                cout << "\n\tcannot connect to X server\n" << endl;
                exit(EXIT_FAILURE);
            }
            Window root = DefaultRootWindow(dpy);
            XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
            if (vi == NULL) {
                cout << "\n\tno appropriate visual found\n" << endl;
                exit(EXIT_FAILURE);
            } 
            Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
            XSetWindowAttributes swa;
            swa.colormap = cmap;
            swa.event_mask =
                ExposureMask | KeyPressMask | KeyReleaseMask |
                ButtonPress | ButtonReleaseMask |
                PointerMotionMask |
                StructureNotifyMask | SubstructureNotifyMask;
            win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
                    InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
            set_title();
            glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
            glXMakeCurrent(dpy, win, glc);
        }
        void set_title() {
            //Set the window title bar.
            XMapWindow(dpy, win);
            XStoreName(dpy, win, "Adventure-Ish");
        }
        bool getXPending() {
            //See if there are pending events.
            return XPending(dpy);
        }
        XEvent getXNextEvent() {
            //Get a pending event.
            XEvent e;
            XNextEvent(dpy, &e);
            return e;
        }
        void swapBuffers() {
            glXSwapBuffers(dpy, win);
        }
}x11;

//Function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void render();
//=====================================
// MAIN FUNCTION IS HERE
//=====================================
int main()
{

    init_opengl();
    g->scene.push(new Menu(g->xres, g->yres));

    //Main animation loop
    while (!g->quit) {
        //Process external events.
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            check_mouse(&e);
            g->done = check_keys(&e);
        }
        render();
        x11.swapBuffers();
    }
    return 0;
}

void init_opengl(void)
{
   
    //OpenGL initialization
    glViewport(0, 0, g->xres, g->yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, g->xres, 0, g->yres, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    //Set the screen background color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //Insert Fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
}
void check_mouse(XEvent *e)
{
    static int savex;
    static int savey;
    //int flag;

    if (e->type != ButtonRelease &&
            e->type != ButtonPress) {
        //This is not a mouse event that we care about.
        return;
    }
    if (e->type == ButtonRelease) {
        return;
    }
    //----------------------------------------------------------
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button was pressed
            if(savex != e->xbutton.x || savey != e->xbutton.y) {
                savex = e->xbutton.x;
                savey = e->xbutton.y;
            }
            //verify that there is a gamescene in the stack
            if(!g->scene.empty()) {
                //pthread_mutex_lock(&g->protect);


                //get the top scene that is being displayed at this moment
                GameScene * sc = g->scene.top();
                //process the mouse position
                GameScene * newScene = sc->CheckMouse(savex, savey);
                                
                if (newScene != nullptr && &newScene != &sc) { //is a new scene
                    g->scene.push(newScene);
                    return;
                } else if (newScene == sc) { // is same scene
                    delete sc;
                    g->scene.pop();
                    return;
                } //else == nullptr
            } 
            //if gamescene was popped and is now empty
            if(g->scene.empty())
                g->quit = true;

            //---------------------------------------------------------
            if (e->xbutton.button==3) {
                //Right button was pressed
                return;
            }
        }
    }
}

int check_keys(XEvent *e)
{
    if (e->type != KeyPress && e->type != KeyRelease)
        return 0;
    int key = XLookupKeysym(&e->xkey, 0); 
    if (e->type == KeyPress) {

        //verify that there is a gamescene in the stack
        if(!g->scene.empty()) {

            //get the top scene that is being displayed at this moment
            GameScene * sc = g->scene.top();
            //process the key input
            GameScene * newScene = sc->CheckKey(key);

            if (newScene != nullptr && newScene != sc) {//is new scene
                g->scene.push(newScene);
                
            } else if (newScene == sc) { //is same scene
                //new scene equals current scene
                delete sc;
                g->scene.pop();
                
            } //else = nullptr
        }

        //if gamescenep popped and is now empty
        if(g->scene.empty())
            g->quit = true;

    }
    return 0;
}

void render()
{
    // if the stack is empty then there is nothing else to do
    // exit game
    if(g->scene.empty()) {
        g->quit = 1;
        return;
    }


    glClear(GL_COLOR_BUFFER_BIT);
    
    
    //get the top scene and call Update() and Draw for the current scene
    GameScene * sc = g->scene.top();
    if(sc != nullptr) {
        GameScene *nScene = sc->Update();

        if(nScene != nullptr && nScene != sc) {
            g->scene.push(nScene);
            ///g->scene.top()->Update();
            return;
        } else if (nScene == sc){
            g->scene.pop();
            //g->scene.top()->Update();
            return;
        }
        sc->Draw();
    }

    //printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));
}
