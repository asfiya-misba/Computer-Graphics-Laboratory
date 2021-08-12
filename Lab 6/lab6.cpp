//Teapot
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<GL/glut.h>
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 200, -100, 200, -200, 200);
	glMatrixMode(GL_MODELVIEW);
}
void drawtable()
{
	//table top 
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(50, 40, -50);
	glScalef(50, 5, 50);
	glutSolidCube(1);
	glPopMatrix();
	//1 st leg 
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(30, 20, -30);
	glScalef(5, 35, 5);
	glutSolidCube(1);
	glPopMatrix();
	//2nd leg 
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(70, 20, -30);
	glScalef(5, 35, 5);
	glutSolidCube(1);
	glPopMatrix();
	// 3rd leg 
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(30, 20, -70);
	glScalef(5, 35, 5);
	glutSolidCube(1);
	glPopMatrix();
	//4 th leg
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(70, 20, -70);
	glScalef(5, 35, 5);
	glutSolidCube(1);
	glPopMatrix();
	//floor 
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslatef(50, 0, -50);
	glScalef(100, 5, 100);
	glutSolidCube(1);
	glPopMatrix();
	//left wall 
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(50, 0, -50);
	glScalef(100, 5, 100);
	glutSolidCube(1);
	glPopMatrix();
	//backside wall 
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(50, 50, -100);
	glScalef(100, 100, 5);
	glutSolidCube(1);
	glPopMatrix();
	//tea pot 
	glPushMatrix();
	glTranslatef(50, 50, -50);
	glRotatef(30, 0, 1, 0);
	glutSolidTeapot(10);
	glPopMatrix();
}
void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat mat_ambient[] = { .7,.7,.7,1 };
	GLfloat mat_diffuse[] = { .5,.5,.5,1 };
	GLfloat mat_spec[] = { 1,1,1,1 };
	GLfloat mat_shininess[] = { 50 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	GLfloat light_int[] = { .7,.7,.7,1 };
	GLfloat lightpos[] = { 100,100,100 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_int);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(25, 25, 50, 0, 0, -25, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	drawtable();
	glFlush();
}
void main()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Scene");
	myinit();
	glutDisplayFunc(display);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
