#ifndef DISPLAY_CALLBACK_H
#define DISPLAY_CALLBACK_H

void RenderScene()
{
	Matrix4f WorldProj, PersProj,CameraTrans, TrackballTrans, WorldTrans;
	TrackballTrans.InitIdentity();//=track.RenderMatrix();
	CameraTrans=cam.RenderMatrix();
	PersProj.InitPersProjTransform(PersProjInfo(cam.FieldOfView(),WINDOW_WIDTH,WINDOW_HEIGHT,0.1,10000));
	WorldTrans=TrackballTrans;
	WorldProj=PersProj*CameraTrans*WorldTrans;            

	glUniformMatrix4fv(gWVPLocation,1,GL_TRUE,&WorldProj.m[0][0]);
	glUniformMatrix4fv(gWorldLocation,1,GL_TRUE,&WorldTrans.m[0][0]);


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

#endif