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
	GLuint RBO,Texture;
	BoundBox box;
	public:
	Particles* RainDrops;
	int number_of_particles;
	int active_particles;
	float Wind,Velocity;
	int Optimize;

	ParticleSystem()
	{
		number_of_particles=500000;
		RainDrops = new Particles[number_of_particles];
		active_particles=1000;
		Wind=0.000;
		Velocity=1.0/100.0;
		Optimize=0;
	}

	void InitializeParticleSystem(BoundBox boundBox)
	{
		box=boundBox;
		glGenBuffers(1, &RBO);
		glBindBuffer(GL_ARRAY_BUFFER,RBO);
		float XWidth=1.5*boundBox.XWidth;
		float YWidth=1.5*boundBox.YWidth;
		float ZWidth=1.5*boundBox.ZWidth;
		float XBound=boundBox.Center.x- XWidth/2;
		float YBound=boundBox.Center.y- YWidth/2;
		float ZBound=boundBox.Center.z- ZWidth/2;

		if(Optimize==1)
		{
			XWidth=XWidth/2;
			YWidth=YWidth;
			ZWidth=ZWidth/2;
		}	
		//XWidth=XWidth;
		//YWidth=YWidth;
		//ZWidth=ZWidth;


		RainBoundBox.XWidth=XWidth;
		RainBoundBox.YWidth=YWidth;
		RainBoundBox.ZWidth=ZWidth;
		//RainBoundBox=WorldBoundBox;

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

	void setTexture(GLuint t)
	{
		Texture=t;
	}

	GLuint getTexture()
	{
		return Texture;
	}

	void RainFall()
	{
		for (int i = 0; i < active_particles; ++i)
		{		
			RainDrops[i].Position.y-=(box.YWidth*Velocity);
			RainDrops[i].Position.x+=Wind;
			if(RainDrops[i].Position.y<=box.Center.y- box.YWidth/2)
				RainDrops[i].Position=RainDrops[i].InitPosition;
		}
		glBufferData(GL_ARRAY_BUFFER,sizeof(Particles)*active_particles, RainDrops, GL_STATIC_DRAW);
	}

	float getSlope()
	{
		return Wind*Velocity;
	}

	int IsOptimized()
	{
		return Optimize;
	}

	void RenderRain()
	{
		glBindBuffer(GL_ARRAY_BUFFER, RBO);
		static int i=0;
		if(i<500){
			RainFall();
			//i++;
		}
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
    	
   	 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 48, 0);
   	 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 48, (const GLvoid*)24);
    	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    	glDrawArrays(GL_POINTS, 0, active_particles);
    	glDisableVertexAttribArray(1);
    	glDisableVertexAttribArray(0);

	}

	void IncreaseRainFall()
	{
		if(active_particles!=400000)
			active_particles=active_particles+100;		
	}

	void DecreaseRainFall()
	{
		if(active_particles!=0)
			active_particles=active_particles-100;		
	}

	int GetActiveParticles()
	{
		return active_particles;
	}

	void IncreaseWind()
	{
		if(Wind<=2)
			Wind+=0.1;
	}
	void DecreaseWind()
	{
		if(Wind>=0)
			Wind-=0.1;
	}

	void IncreaseVelocity()
	{
		if(Velocity<=1)
			Velocity+=0.0001;
	}

	void DecreaseVelocity()
	{
		if(Velocity>=0)
			Velocity-=0.0001;
	}	

	void OptimizeParticles()
	{
		Optimize=1;
		float temp=active_particles;
		InitializeParticleSystem(box);
		active_particles=temp/4;
	}

	void UnOptimizeParticles()
	{
		Optimize=0;
		float temp=active_particles;
		InitializeParticleSystem(box);
		active_particles=temp*4;
	}

	~ParticleSystem()
	{
		delete RainDrops;
	}
	
};

#endif