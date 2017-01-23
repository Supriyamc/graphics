#include<GL/glut.h>
#include<stdlib.h>
#include<Math.h>

void draw_pixel(GLint cx,GLint cy)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(cx,cy);
	glEnd();
}

void plot_pixel(GLint h,GLint k,GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}

void draw_circle(GLint h,GLint k,GLint r)
{
	int x=0,y=r,d=1-r;
	while(y>x)
	{
		plot_pixel(h,k,x,y);
		if(d<0)
		d+=2*x+5;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plot_pixel(h,k,x,y);
}

void draw_cylinder()
{
	int xc=100,yc=100,r=50,i,n=50;
	for(i=0;i<n;i+=4)
	draw_circle(xc,yc+i,r);
}

void parallelopipe(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glEnd();
}

void draw_parallelopipe()
{
	int x1=200,y1=100,x2=300,y2=100,x3=300,y3=200,x4=200,y4=200;
	int i,n=50;
	for(i=0;i<n;i+=4)
	parallelopipe(x1+i,y1+i,x2+i,y2+i,x3+i,y3+i,x4+i,y4+i);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	draw_cylinder();
	glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	draw_parallelopipe();
	glFlush();
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,400,0.0,300);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("cylinder & parallelopipe");
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
