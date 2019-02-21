#include  <GL/freeglut.h>
#include <ctime>
#include <string>

#ifndef GAME_H
#define GAME_H

unsigned long long int NextGeneration( bool ** source,bool ** result,int width, int height);

void PrintMatrix( bool ** source, int width, int height);

bool **CreateMatrix(int width, int height);

void RandomFilling( bool ** source, int width, int height);

void drawString(float x, float y, std::string str);

#endif // GAME_H


