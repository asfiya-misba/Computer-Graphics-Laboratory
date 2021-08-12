#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
int ww = 500, wh = 500, flag = 0;
float  xp = 50, yp = 30, theta = 75, rtheta;
float p[3][2] = { { 50,30 }, { 75,70 },{ 100,30 } };
float r[3][2] = { { 50,30 }, { 75,70 },{ 100,30 } };
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-150, 150, -150, 150);
	glMatrixMode(GL_MODELVIEW);
}
void rotate()
{
	if (flag == 0)
	{
		GLint k;
		glColor3f(1, 0.5, 0);
		float x, y;
		rtheta = (theta * 3.142) / 180;
		for (k = 0; k < 3; k++)
		{
			x = r[k][0];
			y = p[k][1];
			r[k][0] = x * cos(rtheta) - y * sin(rtheta);
			r[k][1] = x * sin(rtheta) + y * cos(rtheta);
		}
		glBegin(GL_POLYGON);
		for (k = 0; k < 3; k++)
			glVertex2f(r[k][0], r[k][1]);
		glEnd();
	}

}
void triangle()
{
	glBegin(GL_POLYGON);
	glVertex2fv(p[0]);
	glVertex2fv(p[1]);
	glVertex2fv(p[2]);
	glEnd();

}

void display()
{
	if (flag == 0)
	{
		float x, y;
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 1);
		triangle();
		rotate();
		rtheta = (theta * 3.142) / 180;
		for (int i = 0; i < 3; i++)
		{
			x = p[i][0];
			y = p[i][1];
			p[i][0] = x * cos(rtheta) - y * sin(rtheta) + xp * (1 - cos(rtheta)) + yp * sin(rtheta);
			p[i][1] = x * sin(rtheta) + y * cos(rtheta) + yp * (1 - cos(rtheta)) - xp * sin(rtheta);
		}
	}
	flag = 1;
	glColor3f(0, 0.5, 0.67);
	triangle();
	glFlush();
}


int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(ww, wh);
	glutInit(&argc, argv);
	glutCreateWindow("Rotation about origin and a fixed point");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
