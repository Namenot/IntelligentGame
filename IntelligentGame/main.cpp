
#define GLEW_STATIC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <CL/cl.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <windows.h>

GLuint VBOID;

GLfloat vertices[] = { -0.5, -0.5,  0.0,
1, 0, 0,
-0.5,  0.5,  0.0,  //trqiangle (can be changed to multiple triangles)
0, 1, 0,
0.0,  0.5,  0.0,
0, 0, 1,

-0.5,  -0.5, 1.0,
1, 0, 0,
-0.0,  -0.5, 1.0,  //triangle (can be changed to multiple triangles)
0, 1, 0,
0.0,  0.5,  1.0,
0, 0, 1 };


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices); //6 = jumped over bites (-0.5, -0.5, 0.0, 1, 0, 0(first two lines))
	glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices + 3);
	glDrawArrays(GL_TRIANGLES, 0, 6); //3 Points = 3 corners (can be changed to multiple corners (for blocks for eg.))

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void initOpengl()
{
	glClearColor(0, 0, 0, 1);//Black

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glewInit();

	//copy data to gpu
	glGenBuffers(1, &VBOID); //amount of Buffers, were to store it
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Second Opengl test");

	initOpengl();
	glutFullScreen();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}