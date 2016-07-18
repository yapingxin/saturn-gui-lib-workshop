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
wchar_t str[128] = L"FTGL 中文输出测试";

void init(void)
{
	glShadeModel(GL_SMOOTH); // Enable Shadow Smooth Mode
	glClearDepth(1.0f); // Set Buffer Depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Initialize FTGL
	freeTypeFont = new FTGLPixmapFont(FontLibFilePath);
	if (freeTypeFont == NULL)
	{
		printf("%s", "Font lib data file cannot be loaded.");
		exit(0);
	}
	else
	{
		freeTypeFont->FaceSize(24); // <-- !!!
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 10.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRasterPos2f(0.2, 0.5);
	freeTypeFont->Render(str);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("FreeType multilingual display");
	glutKeyboardFunc(&keyboard);
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
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





