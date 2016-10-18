#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <new>

int WINDOW_HEIGHT=1000;
int WINDOW_WIDTH=1000;




const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";
const char* pGSFileName = "shader.gs";


// Global Variables

GLuint VBO,IBO;


#include "include/file_utils.h"
#include "include/math_utils.h"
#include "include/shader.h"
#include "include/buffer.h"
#include "include/display_callbacks.h"

static void InitializeDisplayCallbacks()
{
	glutDisplayFunc(RenderScene);
}

static void onInit()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	CreateBuffers();
	CompileShaders();
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char**argv)
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Rain Viewer");
	InitializeDisplayCallbacks();
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	onInit();
	glutWarpPointer(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glutMainLoop();

	return(0);
}