#ifndef PARTICLE_H
#define PARTICLE_H

#include "math_utils.h"

struct Particles
{
	Vector3f Position;
	Vector3f Color;
	Vector3f Normal;
	Vector3f InitPosition;

	Particles()
	{
		Position=Vector3f(0.0,0.0,0.0);
		Color=Vector3f(1.0,1.0,1.0);
		Normal=Position;
		Position=InitPosition;
	}
};
 
class ParticleSystem
{
	GLuint RBO;
	BoundBox box;
	public:
	Particles* RainDrops;
	int number_of_particles;
	float Wind;

	ParticleSystem()
	{
		number_of_particles=1000;
		RainDrops = new Particles[number_of_particles];
		Wind=0.0001;
	}

	void InitializeParticleSystem(BoundBox boundBox)
	{
		box=boundBox;
		glGenBuffers(1, &RBO);
		glBindBuffer(GL_ARRAY_BUFFER,RBO);
		float XWidth=1.5*boundBox.XWidth;
		float YWidth=boundBox.YWidth;
		float ZWidth=boundBox.ZWidth;
		float XBound=boundBox.Center.x- XWidth/2;
		float YBound=boundBox.Center.y- YWidth/2;
		float ZBound=boundBox.Center.z- ZWidth/2;
		for (int i = 0; i < number_of_particles; ++i)
		{
			float X=((float)rand()/RAND_MAX)*XWidth+XBound;
			float Y=((float)rand()/RAND_MAX)*YWidth-YBound;
			float Z=((float)rand()/RAND_MAX)*ZWidth+ZBound;
			RainDrops[i].Position=Vector3f(X,Y,Z);
			RainDrops[i].Normal=Vector3f(X,Y,Z);
			RainDrops[i].Normal.Normalize();
			RainDrops[i].InitPosition=Vector3f(X,Y,Z);
		}
		glBufferData(GL_ARRAY_BUFFER,sizeof(Particles)*number_of_particles, RainDrops, GL_STATIC_DRAW);
	}

	void RainFall()
	{
		for (int i = 0; i < number_of_particles; ++i)
		{		
			RainDrops[i].Position.y-=(box.YWidth/500);
			RainDrops[i].Position.x+=Wind;
			if(RainDrops[i].Position.y<=box.Center.y- box.YWidth/2)
				RainDrops[i].Position=RainDrops[i].InitPosition;
		}
		glBufferData(GL_ARRAY_BUFFER,sizeof(Particles)*number_of_particles, RainDrops, GL_STATIC_DRAW);
	}

	void RenderRain()
	{
		RainFall();
		glEnableVertexAttribArray(0);
    	glBindBuffer(GL_ARRAY_BUFFER, RBO);
   	 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48, 0);
   	 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48, (const GLvoid*)24);
    	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    	glDrawArrays(GL_POINTS, 0, number_of_particles);
    	glDisableVertexAttribArray(1);
    	glDisableVertexAttribArray(0);

	}

	~ParticleSystem()
	{
		delete RainDrops;
	}
	
};

#endif