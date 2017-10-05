#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "openglblock.h"
#include "openglentity.h"
#include "openglvfx.h"

GLuint World;
GLuint Entities;
GLuint Vfx;

GLfloat W[];
GLfloat E[];
GLfloat V[];

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
		
		//Draw World
		glBindBuffer(GL_ARRAY_BUFFER, World);

		glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), 0); //6 = jumped over bites (-0.5, -0.5, 0.0, 1, 0, 0(first two lines))
		glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), (GLvoid*)3);
		glDrawArrays(GL_TRIANGLES, 0, 6); //3 Points = 3 corners (can be changed to multiple corners (for blocks for eg.))
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0,0, w, h);
}

void initOpengl(GLfloat *world/*, GLfloat *entities, GLfloat *vfx*/)
{
	glClearColor(0, 0, 0, 1); //Black

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glewInit();

	//Buffer 1
	glGenBuffers(1, &World); 
	glBindBuffer(GL_ARRAY_BUFFER, World);
	glBufferData(GL_ARRAY_BUFFER, sizeof(W), W, GL_STATIC_DRAW);

	/*//Buffer 2
	glGenBuffers(1, &Entities);
	glBindBuffer(GL_ARRAY_BUFFER, Entities);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Buffer 3
	glGenBuffers(1, &Vfx);
	glBindBuffer(GL_ARRAY_BUFFER, Vfx);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//unbind all*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);//must get two GLfloat Arrays (first 1 contains infos about the world, whilst the second about entities)
}

void createInstance(int argc, char **argv, GLfloat vertices)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("Intelligent Game");
	glutFullScreen();


	assign(&(float)vertices, 0);

	initOpengl(&vertices); //TODO add missing two vars
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();

}

void assign(float *array, int WEV)
{
	int i = 0;
	while (array[i + 1] != i)
	{
		switch (WEV)
		{
		case 0:
				W[i] = array[i + 1];
		
		case 1:
				E[i] = array[i + 1];

		case 2:		
				V[i] = array[i + 1];

		default:
			break;
		}
	}
}//assigns World, Entities and Vfx 