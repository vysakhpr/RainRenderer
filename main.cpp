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

const char* bVSFileName = "bridge_shader.vs";
const char* bFSFileName = "bridge_shader.fs";




// Global Variables
#include "include/file_utils.h"
#include "include/math_utils.h"
#include "include/camera.h"
#include "include/trackball.h"
#include <SOIL/SOIL.h>

GLuint VBO,IBO;
struct BoundBox
{
	Vector3f Center;
	float XWidth;
	float YWidth;
	float ZWidth;

	BoundBox()
	{
		
	}
	BoundBox(Vector3f v,float x, float y, float z,int i)
	{
		Center=v;
		XWidth=i*x;
		YWidth=i*y;
		ZWidth=i*z;
	}
}WorldBoundBox,RainBoundBox;


#include "include/particles.h"
#include "include/lighting.h"
#include "include/bridge.h"
Camera cam;
ParticleSystem rain;
Lighting lights;
TrackBall track;
Bridge bridge;


#include "include/shader.h"
#include "include/buffer.h"
#include "include/display_callbacks.h"




static void InitializeDisplayCallbacks()
{
	glutDisplayFunc(RenderScene);
	glutIdleFunc(IdleScene);
	glutMotionFunc(onActiveMouseMotion);
	glutKeyboardFunc(onKeyPress);
}

static void onInit()
{
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	CreateBuffers();
	CompileShaders();
	CompileBridgeShaders();
	//UseRainShaderProgram();
	//UseBridgeShaderProgram();
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char**argv)
{	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(500,500);
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