#include <GL/freeglut.h>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>

#ifndef GAME_H
#define GAME_H

unsigned long long int NextGeneration( bool ** source,bool ** result,int width, int height);

void PrintMatrix( bool ** source, int width, int height);

bool **CreateMatrix(int width, int height);

void RandomFilling( bool ** source, int width, int height);

void drawString(float x, float y, std::string str);
#ifdef __MINGW32__
    namespace std{
        template<typename T>
        std::string to_string(T t){
            std::stringstream ss;
            ss<<t;
            return ss.str();
        }
    }
#endif

#endif // GAME_H


