#include<stdlib.h>
#include<GL/glut.h>
#define outcode int

double x0,y0,x1,y1;
double xmin,ymin,xmax,ymax;
double xvmin,yvmin,xvmax,yvmax;

const int TOP=1;
const int BOTTOM=2;
const int RIGHT=4;
const int LEFT=8;

outcode computecode(double x,double y)
{
	outcode code=0;
	if(y>ymax)
	code=TOP;
	if(y<ymin)
	code=BOTTOM;
	if(x>xmax)
	code=RIGHT;
	if(x<xmin)
	code=LEFT;
	
	return code;
}

void clipanddraw(double x0,double y0,double x1,double y1)
{
	outcode outcode0,outcode1,outcodeout;
	double sx,sy,vx0,vx1,vy0,vy1;
	int accept=0,done=0;
	
	outcode0=computecode(x0,y0);
	outcode1=computecode(x1,y1);

do
  {	
	if(!(outcode0|outcode1))
	{
		accept=1;
		done=1;
	}
	
	else if(outcode0&outcode1)
	done=1;
	
	else
	{
		double x,y;
		outcodeout=outcode0?outcode0:outcode1;
	
		if(outcodeout & TOP)
		{
			y=ymax;
			x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
		}
		
		else if(outcodeout & BOTTOM)
		{
			y=ymin;
			x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
		}
		
		else if(outcodeout & LEFT)
		{
			x=xmin;
			y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
		}
		
		else
		{
			x=xmax;
			y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
		}
		
		if(outcodeout==outcode0)
		{
			x0=x;
			y0=y;
		outcode0=computecode(x0,y0);
		}
		else
		{
			x1=x;
			y1=y;
		outcode1=computecode(x1,y1);
		}
	}
}

while(!done);

glColor3f(0.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(xvmin,yvmin);
glVertex2f(xvmax,yvmin);
glVertex2f(xvmax,yvmax);
glVertex2f(xvmin,yvmax);
glEnd();

if(accept)
{
	sx=(xvmax-xvmin)/(xmax-xmin);
	sy=(yvmax-yvmin)/(ymax-ymin);
	
	vx0=xvmin+(x0-xmin)*sx;
	vx1=xvmin+(x1-xmin)*sx;
	vy0=yvmin+(y0-ymin)*sy;
	vy1=yvmin+(y1-ymin)*sy;
	
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex2f(vx0,vy0);
	glVertex2f(vx1,vy1);
	glEnd();
}
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0,0.0,500.0);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
	
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
	
	clipanddraw(x0,y0,x1,y1);
	glFlush();
}

int main(int argc,char **argv)
{
	
	printf("enter starting point");
	scanf("%lf%lf",&x0,&y0);
	
	printf("enter ending point");
	scanf("%lf%lf",&x1,&y1);

	printf("enter lowerleft of window");
	scanf("%lf%lf",&xmin,&ymin);
	
	printf("enter upperright of vindow");
	scanf("%lf%lf",&xmax,&ymax);
	
	printf("enter lowerleft of viewport");
	scanf("%lf%lf",&xvmin,&yvmin);
	
	
	printf("enter upperright of viewport");
	scanf("%lf%lf",&xvmax,&yvmax);
		
		glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow(" cohen clipping");
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
