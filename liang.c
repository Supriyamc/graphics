#include<stdlib.h>
#include<GL/glut.h>

double x0,y0,x1,y1;
double xmin,ymin,xmax,ymax;
double xvmin,xvmax,yvmin,yvmax;

int cliptest(double p,double q,double *t1,double *t2)
{
	double t=q/p;
	if(p<0.0)
	{
		if(t>*t1)  *t1=t;
		if(t>*t2)   return 0;
	}
	
	else if(p>0.0)
	{
		if(t<*t2)   *t2=t;
		if(t<*t1)    return 0;
	}
	
	else if(p==0.0)
	{
		if(q<0.0)
		return 0;
	}
	
	return 1;
}

void liangclipanddraw(double x0,double y0,double x1,double y1)
{
	double sx,sy,vx0,vx1,vy0,vy1;
	double dx=x1-x0,dy=y1-y0,te=0.0,t1=1.0;
	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin,yvmin);
	glVertex2f(xvmax,yvmin);
	glVertex2f(xvmax,yvmax);
	glVertex2f(xvmin,yvmax);
	glEnd();
	
	if(cliptest(-dx,x0-xmin,&te,&t1))
	if(cliptest(dx,xmax-x0,&te,&t1))
	if(cliptest(-dy,y0-ymin,&te,&t1))
	if(cliptest(dy,ymax-y0,&te,&t1))
	{
		if(t1<1.0)
		{
			x1=x0+t1*dx;
			y1=y0+t1*dy;
		}
		
		if(te>0.0)
		{
			x0=x0+te*dx;
			y0=y0+te*dy;
		}
		
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
	
	liangclipanddraw(x0,y0,x1,y1);
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
	printf("enter upperright of window");
	scanf("%lf%lf",&xmax,&ymax);
	printf("enter lowerleft of viewport");
	scanf("%lf%lf",&xvmin,&yvmin);
	printf("enter upperright of viewport");
	scanf("%lf%lf",&xvmax,&yvmax);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("liang barsky");
	glutInitWindowSize(500,500);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
