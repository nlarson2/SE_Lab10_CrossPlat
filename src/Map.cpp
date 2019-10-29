

/*
Created By: Nickolas Larson
Date: 10/28/2019

Modified By:
Modified Date:


Note: This class uses a 2D array to draw out the map
    each number in the map below holds values for each
    possible texture to render
    example : 15s are rocks.

*/

#ifndef MAP_CPP
#define MAP_CPP

#include "Map.h"

#include <stdio.h>
#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>


#include "Image.h"




static int map3[][102]={
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7,11,15, 4, 4, 4, 4, 4,12, 7,11, 4, 4, 4, 4, 4,15,12, 7, 7, 7, 7, 7,11,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 8,13, 6, 7, 7, 7,11, 4,15, 5,13,13,13,13,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 0, 1, 1, 1, 1, 2,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 6, 7, 8,13,13,13,13,13,13,13,13,13,13, 3, 4,15, 5,13, 0, 1, 2,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3, 4,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15,12, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15,12, 7, 7, 8,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 6, 7, 7,11,15, 5,13, 6, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 8,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 4,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 2,13, 0, 1, 2,13, 3,15,10, 1, 1, 2,13, 3,15, 5,13, 0, 1, 2,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 9,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 8,13, 3,15,12, 7, 7, 7, 8,13, 3,15, 5,13, 3,15,12, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 8,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 8,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 7, 7, 7,11,15,12, 7,11,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,12, 7,11,15,12, 7, 7, 7, 7, 7,11,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15,10, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 0, 1, 2,13, 3,15, 5,13, 3,15},
  {15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 0, 1, 1, 9,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 6, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15,12, 7, 7, 7, 7, 8,13, 6, 7, 8,13, 6, 7, 8,13, 6, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 8,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,10, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,12, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3, 4,15,12, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7,11,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13,13,13,13,13,13,13, 3,15, 5,13,13,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7,11,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 0, 1, 2,13, 0, 1, 1, 1, 9,15, 5,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13, 0, 1, 1, 1, 2,13, 3,15,10, 1, 2,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3, 4, 4, 4, 4,15, 5,13, 3,15},
  {15, 5,13, 3,15,15, 5,13, 3, 4,15,15, 5,13, 3,15,15,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15,12, 8,13, 6, 7, 7, 7, 8,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 8,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 9,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 7,11,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 4,12, 7,11, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15},
  {15, 5,13, 3, 4,15, 5,13, 3, 4,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15,12, 8,13, 6,11, 4,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 3,15, 4, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3,15},
  {15, 5,13, 3,15,15, 5,13, 3, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13, 3, 4,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 7, 8,13, 3, 4,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13,13,13, 3, 4,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13, 3, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13, 3, 4,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15,10, 1, 1, 1, 1, 1, 1, 9, 4,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13,13,13, 3, 4,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 4, 4,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13,13,13, 3, 4,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15,12, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13,13,13, 3, 4,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 4, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 6, 7, 8,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13, 3, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 9,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 6, 7, 8,13,13,13, 3, 4,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 4, 4,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15, 5,13,13,13,13,13,13,13, 3, 4,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 8,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7,11,15,10, 1, 1, 1, 1, 1, 1, 1, 9, 4,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15,15,15,15, 5,13, 6, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7,11,15, 4, 4, 4, 4, 4, 4, 4,15,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13, 3,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 6, 7, 7, 7, 7, 8,13,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15,12, 7, 7, 7, 7, 7,11,15,12, 8,13, 3,15},
  {15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 2,13, 3,15,10, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,12, 7,11,15, 5,13,13,13,13,13,13,13,13, 0, 1, 2,13, 3,15, 5,13, 0, 1, 2,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3,15, 5,13, 0, 9,15},
  {15, 5,13, 6, 7, 7, 7, 7, 7,11,15, 5,13, 6, 7, 7,11,15,12, 7,11,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15},
  {15, 5,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 6,11,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3,15,10, 1, 9,15,10, 2,13, 3,15},
  {15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 8,13, 3,15},
  {15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4,12, 7, 7, 7, 8,13, 6, 7, 7, 7, 7, 7, 7,11, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 5,13,13,13,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15,10, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15},
  {15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7,11, 4,15, 5,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8,13,13,13,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3, 4,15, 5,13, 0, 1, 2,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15, 5,13, 3, 4, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 5,13,13,13,13,13,13,13,13,13,13,13,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 8,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,12, 7,11, 4,15,12, 7, 7, 7, 8,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13,13,13,13,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13, 0, 1, 1, 1, 9,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13, 3,15,15,15,15,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13, 3, 4, 4, 4, 4,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13, 3, 4, 4, 4, 4,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3, 4,15, 5,13, 3, 4, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 8,13, 3, 4,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15},
  {15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3, 4,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 9, 4,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15},
  {15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15,12, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 4, 4, 4, 4, 4, 4,12, 7,11, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 4, 4,12, 7, 7, 7, 8,13, 6, 7, 7, 7,11, 4, 4, 4,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3,15, 5,13, 0, 1, 2,13, 0, 1, 2,13, 3,15, 5,13, 0, 1, 1, 1, 2,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15},
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 8,13, 3,15, 4, 4, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15},
  {15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7,11,15, 5,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15, 4, 4, 5,13, 3,15,12, 7,11,15,12, 7, 7, 7, 7, 7,11,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 9,15, 4, 4, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 1, 2,13, 6, 7, 8,13, 0, 1, 2,13, 6, 7, 8,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 6, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 9,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 9,15,10, 1, 9,15, 5,13, 3,15},
  {15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13, 6, 7, 8,13, 3,15, 5,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15},
  {15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15, 5,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15,10, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 1, 2,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 3, 4, 4, 4,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 3,15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 4, 4, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 4, 4,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15},
  {15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 3,15,12, 7, 7, 7, 7, 7,11,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15},
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13,13,13,13,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,11,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15},
  {15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 0, 1, 2,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 0, 1, 2,13, 0, 1, 1, 1, 1, 1, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15},
  {15, 5,13, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,15, 5,13, 3,15},
  {15, 5,13, 3,15,12, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15},
  {15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13, 3,15, 5,13, 3,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15, 5,13, 3,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15, 5,13, 3,15, 5,13, 3,15,10, 1, 9,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,10, 1, 9,15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,13, 3,15},
  {15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15, 5,13, 3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 5,13, 3,15},
  {15, 5,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 6, 7, 8,13, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8,13, 3,15},
  {15, 5,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13, 3,15},
  {15,10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9,15},
  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15}



};


void Tile::initTile(const char * _imgSrc, bool _walkable){
    Image img(_imgSrc);
    img.GenerateGLTexture(texture);
    walkable = _walkable;
}

Map::Map() {
    std::string imgSrc = "images/sprites/16x16_Tileset/GrassDirt/";
    for(int i=0; i<16 ;i++)
    {
        std::string tileImgSrc =  imgSrc;
        if(i<10)
            tileImgSrc += "Outdoors_0"+std::to_string(i)+".png";
        else
            tileImgSrc += "Outdoors_"+std::to_string(i)+".png";

        if(i==15)
            tiles[i].initTile(tileImgSrc.c_str(),0);
        else
            tiles[i].initTile(tileImgSrc.c_str(),1);
    }
}

void Map::drawMap(int xres, int yres, int xpos, int ypos) {
    
    glLoadIdentity();

    float w;
    float h;
    /*Title*/
    glPushMatrix();
    w = (float)xres/11.0f;
    h = (float)yres/11.0f;
    glTranslatef(w/2, -h/2, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int y = ypos-5; y <= ypos+5; y++) {
        glTranslatef(0.0f, (float)h, 0.0f);
        glPushMatrix();
        for(int x = xpos-5; x <= xpos+5; x++) {
            //if out of range of array pring 
            if(x < 0 || y < 0 || x > 101 || y > 101)
                glBindTexture(GL_TEXTURE_2D, tiles[15].texture);
            else
                glBindTexture(GL_TEXTURE_2D, tiles[map3[y][x]].texture);
            glBegin(GL_QUADS);
            /*!!!!!DO NOT MESS WITH THE TEXTURE COORDINATES!!!!!*/
                glTexCoord2f(0.025, 0.975);glVertex2f(-w/2.0f, -h/2.0f);
                glTexCoord2f(0.025, 0.025);glVertex2f(-w/2.0f,  h/2.0f);
                glTexCoord2f(0.975, 0.025);glVertex2f( w/2.0f,  h/2.0f);
                glTexCoord2f(0.975, 0.975);glVertex2f( w/2.0f, -h/2.0f);
            glEnd();
            glTranslatef((float)w, 0.0f, 0.0f);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    //exit(0);
}


bool Map::isWalkable(int x, int y) {
    if(x < 0 || y < 0 || x > 101 || y > 101)
        return false;
    int ret = map3[y][x];
    return ret;
}


#endif