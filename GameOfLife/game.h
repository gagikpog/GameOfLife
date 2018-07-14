#include  <GL/freeglut.h>
#include <ctime>

#ifndef GAME_H
#define GAME_H

void NextGeneration( bool ** source,bool ** result,int width, int height);

void PrintMatrix( bool ** source, int width, int height);

bool **CreateMatrix(int width, int height);

void RandomFilling( bool ** source, int width, int height);

#endif // GAME_H


