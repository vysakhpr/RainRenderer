#ifndef BUFFER_H
#define BUFFER_H

void CreateBuffers()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	Vector3f Vertices[1];
    Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
	glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

#endif