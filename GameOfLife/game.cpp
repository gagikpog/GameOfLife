#include "game.h"

inline int CountNeighbors(bool ** source, const int y, const int x, const int w, const int h)
{
	int res = 0;
	for (int i = - 1; i <= 1; i++)
	{
		for (int j = - 1; j <= 1; j++)
		{
			if (source[(y + i + h) % h][(x + j + w) % w])
				res++;
		}
	}
	if (source[y][x])
		res--;
	return res;
}

void NextGeneration(bool ** source, bool ** result, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int n = CountNeighbors(source, i, j, w, h);
			result[i][j] = (n == 3) || (n == 2) && source[i][j];
		}
	}
}

void PrintMatrix( bool ** source, int w, int h)
{
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			if(source[i][j])
				glVertex2f(j, i);
		}
	}
	glEnd();
}

bool ** CreateMatrix(int w, int h)
{
	bool **res = NULL;
	res = new bool*[h];
	for (int i = 0; i < h; i++) {
		res[i] = new bool[w];
		for (int j = 0; j < w; j++)
		{
			res[i][j] = false;
		}
	}
	return res;
}

void RandomFilling(bool ** source, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			source[i][j] = rand() % 2;
		}
	}
}
