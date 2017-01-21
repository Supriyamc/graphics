#include<stdlib.h>
#include<GL/glut.h>

GLfloat v[4][3]={{0.0,0.0,1.0},{0.0,0.9,-0.3},{-0.8,-0.4,-0.3},{0.8,-0.4,-0.3}};
GLfloat colors[4][3]={{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{0.0,0.0,1.0}};
int n;

void triangle(GLfloat *va,GLfloat *vb,GLfloat *vc)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	
}

void tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
	glColor3fv(colors[0]);
	triangle(a,b,c);
	glColor3fv(colors[1]);
	triangle(a,b,d);
	glColor3fv(colors[2]);
	triangle(b,c,d);
	glColor3fv(colors[3]);
	triangle(a,d,c);
	
}

void divide_tetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
	GLfloat mid[6][3];
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)  mid[0][j]=(a[j]+b[j])/2;
		for(j=0;j<3;j++)  mid[1][j]=(a[j]+c[j])/2;
		for(j=0;j<3;j++)  mid[2][j]=(a[j]+d[j])/2;
		for(j=0;j<3;j++)  mid[3][j]=(b[j]+c[j])/2;
		for(j=0;j<3;j++)  mid[4][j]=(b[j]+d[j])/2;
		for(j=0;j<3;j++)  mid[5][j]=(c[j]+d[j])/2;
		
		divide_tetra(a,mid[0],mid[1],mid[2],m-1);
		divide_tetra(mid[0],b,mid[3],mid[4],m-1);
		divide_tetra(mid[1],mid[3],c,mid[5],m-1);
		divide_tetra(mid[2],mid[4],mid[5],d,m-1);
	}
	else
	tetra(a,b,c,d);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0],v[1],v[2],v[3],n);
	glEnd();
	glFlush();
}

void init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-2,2);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char **argv)
{
	n=atoi(argv[1]);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutCreateWindow("gasket");
	glutInitWindowSize(500,500);
	glutDisplayFunc(display);
	init();
	glEnable(GL_DEPTH_TEST);
//	init();
	glutMainLoop();
	return 0;
}
