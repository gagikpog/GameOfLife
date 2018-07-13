#include "game.h"

int WndW = 1500, WndH = 900;
int w = 150, h = 90;
bool **matrix1;
bool **matrix2;
bool step = true;
bool pause = false;
int Button;

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

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
		glutTimerFunc(50, timer, 0); 
}

void Keys(unsigned char key, int ax,int ay) 
{
	if (key == 'p')
	{
		pause = !pause;		
		timer(0);
	} 
	if (key == 'r')
	{
		bool ** matrixPtr = matrix1;
		if (!step)
			matrixPtr = matrix2;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				matrixPtr[i][j] = false;
			}
		}
		glutPostRedisplay();
	}
}

void MouseMove(int ax, int ay)
{
//	if (!pause)
//		return;
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
//	if (!pause)
//		return;
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

	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(Keys);
	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}