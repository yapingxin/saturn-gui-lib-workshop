// FT_gl_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <GL/glut.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>

#include <iostream>
#include <FTGL/ftgl.h>

static void keyboard(unsigned char key, int x, int y);
static void display(void);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("GLUT Test");
	glutKeyboardFunc(&keyboard);
	glutDisplayFunc(&display);
	glutMainLoop();

	return 0;
}

static void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	}
}


static void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush();
}


