#ifndef BUFFER_H
#define BUFFER_H

#include  "camera.h"
void CreateBuffers()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	Vector3f Vertices[4];
    Vertices[0] = Vector3f(-0.5f, -0.5f, 0.0f);
    Vertices[1] = Vector3f(0.0f, -0.5f, 0.5f);
    Vertices[2] = Vector3f(0.5f, -0.5f, 0.0f);
    Vertices[3] = Vector3f(0.0f, 0.5f, 0.0f);

    unsigned int Indices[] = { 0, 3, 1,
                               1, 3, 2,
                               2, 3, 0,
                               0, 1, 2 };

    WorldBoundBox=BoundBox(Vector3f(0,0,0),2,2,2,1);
    cam.SetPosition(Vector3f(0,0,-WorldBoundBox.ZWidth));

	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

#endif