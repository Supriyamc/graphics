#include<stdlib.h>
#include<GL/glut.h>

GLfloat x1,y1,x2,y2,x3,y3,x4,y4;

void edge_detect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLint *le,GLint *re)
{
	int x,mx,temp;
	int i;
	
	if((y2-y1)<0)
	{
		temp=y1; y1=y2; y2=temp;
		temp=x1; x1=x2; x2=temp;
	}
	
	if((y2-y1)!=0)
	mx=(x2-x1)/(y2-y1);
	else
	mx=(x2-x1);
	
	x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
		le[i]=(int)x;
		if(x>(float)re[i])
		re[i]=(int)x;
		x+=mx;
	}
}

void draw_pixel(int x,int y)
{
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	int le[500],re[500];
	int i,n=500,scanline;
	for(i=0;i<n;i++)
	{
		le[i]=500;
		re[i]=0;
	}
	
	edge_detect(x1,y1,x2,y2,le,re);
	edge_detect(x2,y2,x3,y3,le,re);
	edge_detect(x3,y3,x4,y4,le,re);
	edge_detect(x4,y4,x1,y1,le,re);
	
	for(scanline=0;scanline<500;scanline++)
	{
	if(le[scanline]<=re[scanline])
		for(i=le[scanline];i<re[scanline];i++)
		draw_pixel(i,scanline);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	 x1=100,y1=200,x2=200,y2=300,x3=300,y3=200,x4=200,y4=100;
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x2,y2);
	glVertex2i(x3,y3);
	glVertex2i(x4,y4);
	glEnd();
	scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
	glFlush();
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(00,500,00,500);
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutCreateWindow("polygon filling");
	glutInitWindowSize(500,500);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
