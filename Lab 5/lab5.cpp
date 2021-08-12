#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
int flag = 0;
#define outcode int
float  xmin = 200, xmax = 300, ymin = 200, ymax = 300, umin = 500, umax = 800, vmin = 500, vmax = 800;
enum { top = 0x8, bottom = 0x4, right = 0x2, left = 0x1 };
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200, 1200, -200, 1200);
	glMatrixMode(GL_MODELVIEW);
}

outcode Computeoutcode(float x, float y)
{
	outcode code = 0;
	if (y > ymax)
		code = code | top;
	else if (y < ymin)
		code = code | bottom;
	if (x > xmax)
		code = code | right;
	else if (x < xmin)
		code = code | left;
	return code;
}
void drawline(float xrmin, float yrmin, float xrmax, float yrmax, float x1, float y1, float x2, float y2)
{
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xrmin, yrmin);
	glVertex2f(xrmin, yrmax);
	glVertex2f(xrmax, yrmax);
	glVertex2f(xrmax, yrmin);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void cohensoutherland_algo(float x1, float y1, float x2, float y2)
{
	bool accept = false, done = false;
	float x = 0, y = 0;
	outcode p1, p2, p = 0;
	p1 = Computeoutcode(x1, y1);
	p2 = Computeoutcode(x2, y2);
	float m = (y2 - y1) / (x2 - x1);
	do {
		if (!(p1 | p2))
		{
			accept = true;
			done = true;
		}
		else if (p1 & p2)
			done = true;
		else
		{
			p = p1 ? p1 : p2;
			if (p & bottom)
			{
				y = ymin;
				x = x1 + (ymin - y1) / m;
			}
			else if (p & top)
			{
				y = ymax;
				x = x1 + (ymax - y1) / m;
			}
			else if (p & right)
			{
				x = xmax;
				y = y1 + (xmax - x1) * m;
			}
			else
			{
				x = xmin;
				y = y1 + (xmin - x1) * m;
			}
			if (p == p2)
			{
				x2 = x;
				y2 = y;
				p2 = Computeoutcode(x2, y2);
			}
			if (p == p1)
			{
				x1 = x;
				y1 = y;
				p1 = Computeoutcode(x1, y1);
			}
		}
	} while (!done);
	if (accept)
	{
		float sx = (umax - umin) / (xmax - xmin);
		float sy = (vmax - vmin) / (ymax - ymin);
		x1 = sx * x1 + umin - sx * xmin;
		y1 = sy * y1 + vmin - sy * ymin;
		x2 = sx * x2 + umin - sx * xmin;
		y2 = sy * y2 + vmin - sy * ymin;
		drawline(umin, vmin, umax, vmax, x1, y1, x2, y2);
	}
}
void display()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawline(xmin, ymin, xmax, ymax, 180, 180, 320, 320);
	cohensoutherland_algo(180, 180, 320, 320);
}
int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInit(&argc, argv);
	glutCreateWindow("Cohensoutherland Line Clipping");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
