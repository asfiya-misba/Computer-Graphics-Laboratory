//Bresenham's line drawing algorithm
#include <stdio.h>
#include<math.h>
#include <GL/glut.h>
using namespace std;

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-5, 20, -5, 20);
    glMatrixMode(GL_MODELVIEW);
}
void setPixel(int x, int y)
{
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
void lineBres(int x0, int y0, int xEnd, int yEnd)
{
    int dx = fabs(xEnd-x0), dy = fabs(yEnd-y0);
    int p;
    int twoDy = 2 * dy, twoDx = 2 * dx, twoDyMinusDx = 2 * (dy - dx), twoDxMinusDy = 2 * (dx - dy);
    int x, y;
    if (dx > dy)
    {
        p = 2 * dy - dx;
        if (x0 > xEnd)
        {
            x = xEnd;
            y = yEnd;
            xEnd = x0;
        }
        else
        {
            x = x0;
            y = y0;
        }
        setPixel(x, y);
        while (x < xEnd)
        {
            x++;
            if (p < 0)
                p += twoDy;
            else
            {
                y++;
                p += twoDyMinusDx;
            }
            setPixel(x, y);
        }
    }
    else
    {
        p = 2 * dx - dy;
        if (y0 > yEnd)
        {
            y = yEnd;
            x = xEnd;
            yEnd = y0;
        }
        else
        {
            y = y0;
            x = x0;
        }
        setPixel(x, y);
        while (y < yEnd)
        {
            y++;
            if (p < 0)
                p += twoDx;
            else
            {
                x++;
                p += twoDxMinusDy;
            }
            setPixel(x, y);
        }

    }
}
void display(void)
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    lineBres(5, 5, 13, 9);
    //lineBres(-3, 2, 1, 5);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}







