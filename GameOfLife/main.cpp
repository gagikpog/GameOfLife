#include "game.h"
#include <string>

int WndW = 1500, WndH = 900;
int w = 300, h = 180;
bool **matrix1;
bool **matrix2;
bool step = true;
bool pause = false;
int Button;
int speed = 50;

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSetWindowTitle(("timer = "+std::to_string(speed)).c_str());
	if(step)
		PrintMatrix(matrix1, w, h);
	else PrintMatrix(matrix2, w, h);

	glutSwapBuffers();
}

void timer(int)
{
	if(step)
		NextGeneration(matrix1, matrix2, w, h);
	else 	NextGeneration(matrix2, matrix1, w, h);	
	step = !step;
	glutPostRedisplay();
	if (!pause) 
		glutTimerFunc(speed, timer, 0); 
}

void Keys(unsigned char key, int ax,int ay) 
{
	bool ** matrixPtr = matrix1;
	if (!step)
		matrixPtr = matrix2;
	switch (key)
	{
	case 'p':	case 'P': {
		pause = !pause;
		timer(0);
		break;
	}
	case 'r':	case 'R': {
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				matrixPtr[i][j] = false;
			}
		}
		glutPostRedisplay();
		break;
	}
	case 'f':	case 'F': {
		RandomFilling(matrixPtr, w, h);
		glutPostRedisplay();
		break; 
	}
	default:
		break;
	}

}

void Keys(int key, int ax, int ay)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		if (speed > 1)
			speed-=2;
		break;
	case GLUT_KEY_UP:
		if (speed < 1000)
			speed+=2;
		break;
	default:
		break;
	}
}

void MouseMove(int ax, int ay)
{
	bool ** matrixPtr = matrix1;
	if(!step)
		matrixPtr = matrix2;
	bool active = Button == 0;
	int x, y;
	x = (ax*w) / WndW;
	y = (ay*h) / WndH;
	if (x > 0 && x < w&&y>0 && y < h)
		matrixPtr[y][x] = active;

	glutPostRedisplay();
}

void Mouse(int button, int state, int ax, int ay)
{
	bool ** matrixPtr = matrix1;
	if (!step)
		matrixPtr = matrix2;
	Button = button;
	bool active = button == 0;
	int x, y;
	x = (ax*w) / WndW;
	y = (ay*h) / WndH;
	if (x > 0 && x < w&&y>0 && y < h)
		matrixPtr[y][x] = active;

	glutPostRedisplay();
}

int main(int argc,char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(0, 50);
	glutInitWindowSize(WndW,WndH);
	glutCreateWindow("Game Of Life");
	
	gluOrtho2D(0, w, h, 0);

	matrix1 = CreateMatrix(w, h);
	matrix2 = CreateMatrix(w, h);
	glPointSize(WndW/w);
	matrix1[1][2] = true;
	matrix1[2][3] = true;
	matrix1[3][1] = true;
	matrix1[3][2] = true;
	matrix1[3][3] = true;

	timer(0);
	srand(time(NULL));

	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keys);
	glutSpecialFunc(Keys);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}