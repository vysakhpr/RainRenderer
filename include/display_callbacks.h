#ifndef DISPLAY_CALLBACK_H
#define DISPLAY_CALLBACK_H
string theProgramTitle = "Rain Demo By Vysakh P R";
struct MouseMotion
{
	int pre_x;
	int pre_y;
}mouse;


void computeFPS() {
	static int frameCount = 0;
	static int lastFrameTime = 0;
	static char * title = NULL;
	int currentTime;

	if (!title)
		title = (char*) malloc((strlen(theProgramTitle.c_str()) + 40) * sizeof (char));
	frameCount++;
	currentTime = glutGet((GLenum) (GLUT_ELAPSED_TIME));
	if (currentTime - lastFrameTime > 1000) {
		sprintf(title, "%s [ FPS: %4.2f ] [ Particles: %d]",
			theProgramTitle.c_str(),
			frameCount * 1000.0 / (currentTime - lastFrameTime),
			rain.GetActiveParticles()*4);
		glutSetWindowTitle(title);
		lastFrameTime = currentTime;
		frameCount = 0;
	}
}


void RenderScene()
{

	//lights.SetPositionalLightPosition(Vector3f(WorldBoundBox.XWidth/2,WorldBoundBox.YWidth/2,WorldBoundBox.ZWidth/2));
	
	lights.SetPositionalLightPosition(Vector3f(1.5,2.35,-1.27));
	//cout<<WorldBoundBox.YWidth<<endl;
	Matrix4f WorldProj, PersProj,CameraTrans, TrackballTrans, WorldTrans;
	TrackballTrans=track.RenderMatrix();//.InitIdentity();
	CameraTrans=cam.RenderMatrix();
	PersProj.InitPersProjTransform(PersProjInfo(cam.FieldOfView(),WINDOW_WIDTH,WINDOW_HEIGHT,0.1,10000));
	WorldTrans=TrackballTrans;
	WorldProj=PersProj*CameraTrans*WorldTrans;            

	//glUniformMatrix4fv(gWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	//glUniformMatrix4fv(gWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);
	//glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&(cam.ViewMatrix()).m[0][0]);
	//glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&CameraTrans.m[0][0]);
	//SetRainBoundBoxInShader();
	//SetLightsInShader(lights,cam);


	//glUniformMatrix4fv(dWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	//glUniformMatrix4fv(dWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);

	
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_CULL_FACE);



	UseBridgeShaderProgram();
	
	glUniformMatrix4fv(gWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	glUniformMatrix4fv(gWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);
	SetLightsInShader(lights,cam);
	bridge.RenderBridge();

	
	UseRainShaderProgram();
	
	glUniformMatrix4fv(gWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	glUniformMatrix4fv(gWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);
	glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&(cam.ViewMatrix()).m[0][0]);
	glUniformMatrix4fv(gCameraViewLocation,1,GL_TRUE,&CameraTrans.m[0][0]);
	glUniformMatrix4fv(gProjectionLocation,1,GL_TRUE,&PersProj.m[0][0]);
	SetRainBoundBoxInShader();
	SetLightsInShader(lights,cam);
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
	computeFPS();
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
		case 'd':
		case 'D': 	rain.IncreaseRainFall();break;
		case 'c':
		case 'C':	rain.DecreaseRainFall();break;

		default:
				exit(1);
	}
}



#endif