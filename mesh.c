#include<GL/glut.h>
#include<stdlib.h>
#define maxx 10
#define maxy 15
#define dx 15
#define dy 10

GLfloat x[maxx]={0.0},y[maxy]={0.0};
GLfloat x0=50,y0=50;
GLint i,j;

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-0.0,500,-0.0,500);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	for(i=0;i<maxx;i++)
	x[i]=x0+i*dx;
	
	for(j=0;j<maxy;j++)
	y[j]=y0+j*dy;
	
	for(i=0;i<maxx-1;i++)
	for(j=0;j<maxy-1;j++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x[i],y[j]);
		glVertex2f(x[i+1],y[j]);
		glVertex2f(x[i+1],y[j+1]);
		glVertex2f(x[i],y[j+1]);
		glEnd();
		glFlush();
	}
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("mesh");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
