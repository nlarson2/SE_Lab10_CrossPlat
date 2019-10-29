//All windows creations and function X11 functions from waterfall or particle framework By Gordon Griesel

//Main taken from Fate The Shadow Wizard Kingdom Darkness Revived 2 The Second one
//which was created from the particles framework

//Modified by: Nickolas Larson
//Date:        10/05/2019 


#include "glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
//#include <GL/glu.h>


#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
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

//Function prototypes
void init_opengl(void);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void render();
//=====================================
// MAIN FUNCTION IS HERE
//=====================================
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();/*
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/


    GLFWwindow* window = glfwCreateWindow(g->xres, g->yres, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
   
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    init_opengl();
    g->scene.push(new Menu(g->xres, g->yres));

    
    while (!glfwWindowShouldClose(window) && !g->quit)
    {
        render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
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


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if( button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if(!g->scene.empty()) {

            //get the top scene that is being displayed at this moment
            GameScene * sc = g->scene.top();
            //process the mouse position
            GameScene * newScene = sc->CheckMouse((int)xpos, (int)ypos);
                            
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

    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
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
