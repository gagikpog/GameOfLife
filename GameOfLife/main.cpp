#include  <GL/freeglut.h>

int WndW = 600, WndH = 600;

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(100, 100);
	glEnd();

	glutSwapBuffers();
}


int main(int argc,char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WndW,WndH);
	glutCreateWindow("Game Of Life");
	
	gluOrtho2D(0, WndW, 0, WndH);

	glutDisplayFunc(Display);
	glutMainLoop();
	return 0;
}