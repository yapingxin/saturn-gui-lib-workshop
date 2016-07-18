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

using namespace std;

const char* FontLibFilePath = "C:\\Pub\\FontLib\\SourceHanSansCN\\SourceHanSansCN-Light.otf";

static void keyboard(unsigned char key, int x, int y);
static void display(void);

FTGLPixmapFont *freeTypeFont = NULL;

void init(void)
{
	glShadeModel(GL_SMOOTH); // Enable Shadow Smooth Mode
	glClearDepth(1.0f); // Set Buffer Depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Initialize FTGL
	freeTypeFont = new FTGLPixmapFont(FontLibFilePath);

}


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


