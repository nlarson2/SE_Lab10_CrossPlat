
/*
Created By: Nickolas Larson
Date: 10/28/2019

Note: Only holds basic information about the player
since the main actions are are done in the Game scene
*/

#ifndef PLAYER_H
#define PLAYER_H


class Player {
    
    public:
    int health;
    int xpos, ypos;
    int dir;
    Player(int _xpos, int _ypos, int _dir, int _health);


};

#endif
