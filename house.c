#include<GL/glut.h>
#include<stdlib.h>

GLfloat theta=0.0,inc;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100,200,-100,200);
	glMatrixMode(GL_MODELVIEW);
}

void house()
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(20,0);
	glVertex2i(20,50);
	glVertex2i(80,50);
	glVertex2i(80,0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(40,0);
	glVertex2i(40,25);
	glVertex2i(60,25);
	glVertex2i(60,0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glVertex2i(20,50);
	glVertex2i(80,50);
	glVertex2i(50,75);
	glEnd();
}

void rotate()
{
	theta+=inc;
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glLoadIdentity();
	glRotatef(theta,0.0,0.0,1.0);
	house();
	glFlush();
}

int main(int argc,char **argv)
{
	printf("enter angle and inc");
	scanf("%f%f",&theta,&inc);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("house");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutDisplayFunc(display);
	glutIdleFunc(rotate);
	init();
	glutMainLoop();
	return 0;
}
