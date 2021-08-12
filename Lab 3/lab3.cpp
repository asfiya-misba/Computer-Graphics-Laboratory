
//Lab program-03 : Color Cube Rotation using Transformations.
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
#include<stdlib.h>
float v[8][3] = { {-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1} };
float c[8][3] = { {0,0,1},{0,1,1},{1,1,1},{1,0,1},{0,0,0},{0,1,0},{1,1,0},{1,0,0} };
float theta[3] = { 0,0,0 };
int flag = 2;
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2);
	else
		glOrtho(-2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
}

void mousefunc(int button, int status, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
		flag = 2;
	if (button == GLUT_MIDDLE_BUTTON && status == GLUT_DOWN)
		flag = 1;
	if (button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
		flag = 0;
	theta[flag]++;
	if (theta[flag] > 360) theta[flag] = 0;
	glutPostRedisplay();

}
void drawpoly(int a, int b, int c1, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(c[a]);
	glVertex3fv(v[a]);
	glColor3fv(c[b]);
	glVertex3fv(v[b]);
	glColor3fv(c[c1]);
	glVertex3fv(v[c1]);
	glColor3fv(c[d]);
	glVertex3fv(v[d]);
	glEnd();
}

void colorcube()
{
	drawpoly(0, 1, 2, 3);
	drawpoly(0, 1, 5, 4);
	drawpoly(1, 5, 6, 2);
	drawpoly(4, 5, 6, 7);
	drawpoly(3, 2, 6, 7);
	drawpoly(0, 4, 7, 3);
}

void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0, 1, 0);
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();
	glRotatef(theta[0], 1, 0, 0);
	glRotatef(theta[1], 0, 1, 0);
	glRotatef(theta[2], 0, 0, 1);
	colorcube();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE| GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100,100);
	glutInit(&argc, argv);
	glutCreateWindow("Color Cube rotation");
	myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mousefunc);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
