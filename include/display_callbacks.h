#ifndef DISPLAY_CALLBACK_H
#define DISPLAY_CALLBACK_H

struct MouseMotion
{
	int pre_x;
	int pre_y;
}mouse;

void RenderScene()
{

	//lights.SetPositionalLightPosition(Vector3f(WorldBoundBox.XWidth/2,WorldBoundBox.YWidth/2,WorldBoundBox.ZWidth/2));
	lights.SetPositionalLightPosition(Vector3f(0,0,1));
	Matrix4f WorldProj, PersProj,CameraTrans, TrackballTrans, WorldTrans;
	TrackballTrans=track.RenderMatrix();//.InitIdentity();
	CameraTrans=cam.RenderMatrix();
	PersProj.InitPersProjTransform(PersProjInfo(cam.FieldOfView(),WINDOW_WIDTH,WINDOW_HEIGHT,0.1,10000));
	WorldTrans=TrackballTrans;
	WorldProj=PersProj*CameraTrans*WorldTrans;            

	glUniformMatrix4fv(gWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	glUniformMatrix4fv(gWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);
	glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&(cam.ViewMatrix()).m[0][0]);
	//glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&CameraTrans.m[0][0]);

	SetLightsInShader(lights,cam);

	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

	rain.RenderRain();

	GLenum errorCode = glGetError();
	if (errorCode == GL_NO_ERROR) {
		glutSwapBuffers();
	} else {
		fprintf(stderr, "OpenGL rendering error %d\n", errorCode);
	}
}

void IdleScene()
{
	glutPostRedisplay();
}


void onActiveMouseMotion(int x, int y)
{
	int dx=x - mouse.pre_x;
	int dy=y- mouse.pre_y;
	mouse.pre_x=x;
	mouse.pre_y=y;
	track.SetAngles(-dx,-dy,x,y);
	glutPostRedisplay();
}


static void onKeyPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'a':
		case 'A':	lights.ToggleDirectionalLightSwitch();break;
		case 'z':
		case 'Z':	lights.TogglePositionalLightSwitch();break;

		default:
				exit(1);
	}
}


#endif