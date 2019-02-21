#include "game.h"

int WndW = 1500, WndH = 900;
int w = 300, h = 180;
bool **matrix1;
bool **matrix2;
bool step = true;
bool pause = false;
int Button;
int speed = 50;
unsigned int generation = 0;
void WriteInfo();

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	if(step)
		PrintMatrix(matrix1, w, h);
	else PrintMatrix(matrix2, w, h);
	WriteInfo();
	glutSwapBuffers();
}

void timer(int)
{
	static bool b1 = false, b2 = false;
	if (step) {
		static unsigned long long int r1 = 0;
		unsigned long long int f1 = 0;
		f1 = NextGeneration(matrix1, matrix2, w, h);
		b1 = f1 == r1;
		r1 = f1;
	} else {
		static unsigned long long int r2 = 0;
		unsigned long long int f2 = 0;
		f2 = NextGeneration(matrix2, matrix1, w, h);
		b2 = f2 == r2;
		r2 = f2;
	}
	pause |= b1 && b2;
	step = !step;
	glutPostRedisplay();
	generation++;
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
		generation = 0;
		glutPostRedisplay();
		break;
	}
	case 'f':	case 'F': {
		RandomFilling(matrixPtr, w, h);
		generation = 0;
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

void WriteInfo()
{
	glColor3ub(250, 250, 0);
	drawString(1, 3, "Generation: " + std::to_string(generation));
	drawString(1, 6, "Speed: " + std::to_string(speed));
	if (pause)
		drawString(1, 9, "Pause");
	else drawString(1, 9, "Run");
	glColor3ub(255, 255, 255);
}