#ifndef BRIDGE_H
#define BRIDGE_H

#include <vector>
#include <string.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
	Vector3f Position;
	Vector3f Normal;
	Vector2f Texture;
	Vector3f Tangent;
	Vector3f Bitangent;


	Vertex()
	{
		Position=Vector3f(0.0,0.0,0.0);
		Normal=Position;
		Texture=Vector2f(0.0,0.0);
	}
};


class Bridge
{
	GLuint VBO,IBO;
	std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
public:
	Bridge()
	{

	}	
	~Bridge()
	{

	}


	void LoadFile(string file)
	{
		Assimp::Importer importer;
    	const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenNormals  | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_FixInfacingNormals | aiProcess_CalcTangentSpace );
    	if ((!scene) || (scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE) || (!scene->mRootNode))
    	{
        	std::cerr << "Error loading bridge Model: " << std::string(importer.GetErrorString()) << std::endl;
        	return;
    	}
	
		aiMesh* mesh = scene->mMeshes[0];
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

		float maxBoundX=0,maxBoundY=0,maxBoundZ=0,minBoundX=0,minBoundY=0,minBoundZ=0;
		float x,y,z;
		float dX,dY,dZ,BoundBoxWidth;

		for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
        {
        	Vertex vertex;
        	vertex.Position.x=mesh->mVertices[j].x;
        	vertex.Position.y=mesh->mVertices[j].y;
        	vertex.Position.z=mesh->mVertices[j].z;

        	vertex.Normal.x=mesh->mNormals[j].x;
        	vertex.Normal.y=mesh->mNormals[j].y;
        	vertex.Normal.z=mesh->mNormals[j].z;

        	//cout<<vertex.Normal.x<<","<<vertex.Normal.y<<","<<vertex.Normal.z<<endl;

        	vertex.Texture.x=mesh->mTextureCoords[0][j].x;
        	vertex.Texture.y=mesh->mTextureCoords[0][j].y;

        	vertex.Tangent.x=mesh->mTangents[j].x;
        	vertex.Tangent.y=mesh->mTangents[j].y;
        	vertex.Tangent.z=mesh->mTangents[j].z;

        	//cout<<vertex.Tangent.x<<","<<vertex.Tangent.y<<","<<vertex.Tangent.z<<endl;

        	vertex.Bitangent.x=mesh->mBitangents[j].x;
        	vertex.Bitangent.y=mesh->mBitangents[j].y;
        	vertex.Bitangent.z=mesh->mBitangents[j].z;



        	vertices.push_back(vertex);
        	x = vertex.Position.x;
        	y = vertex.Position.y;
        	z = vertex.Position.z;

        	if(j==0)
	 		{
		 		maxBoundX=x;maxBoundY=y;maxBoundZ=z;
		 		minBoundX=x;minBoundY=y;minBoundZ=z;
		 	}
	 		else
	 		{
		 		if(x>maxBoundX)
		 			maxBoundX=x;
	 			else if(x<minBoundX)
	 				minBoundX=x;

	 			if(y>maxBoundY)
	 				maxBoundY=y;
	 			else if(y<minBoundY)
		 			minBoundY=y;

	 			if(z>maxBoundZ)
		 			maxBoundZ=z;
		 		else if(z<minBoundZ)
	 				minBoundZ=z; 
	 		}
        }

        dX=maxBoundX- minBoundX;
		dY=maxBoundY- minBoundY;
		dZ=maxBoundZ- minBoundZ;
		
		if(dX>dY)
		{
			if(dX>dZ)
				BoundBoxWidth=dX;
			else
				BoundBoxWidth=dZ;
		}
		else
		{
			if(dY>dZ)
				BoundBoxWidth=dY;
			else
				BoundBoxWidth=dZ;
		}
		if(BoundBoxWidth==0)
			BoundBoxWidth=1;
		WorldBoundBox.Center.x=(maxBoundX-(dX/2));
		WorldBoundBox.Center.y=(maxBoundY-(dY/2));
		WorldBoundBox.Center.z=(maxBoundZ-(dZ/2));
		WorldBoundBox.XWidth=dX;
		WorldBoundBox.YWidth=dY;
		WorldBoundBox.ZWidth=dZ;
		
		for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
        {
            //Get the face
            aiFace face = mesh->mFaces[j];
            //Add the indices of the face to the vector
            for (unsigned int k = 0; k < face.mNumIndices; k+=3) 
            {
            	indices.push_back(face.mIndices[k]);
            	indices.push_back(face.mIndices[k+1]);
            	indices.push_back(face.mIndices[k+2]);
            }
        }

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);	

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.at(0), GL_STATIC_DRAW);



        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices.at(0), GL_STATIC_DRAW);
	}	


	void RenderBridge()
	{
		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 56, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 56, (void*)12);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 56, (void*)24);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 56, (void*)32);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 56, (void*)44);

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(4);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(1);
    	glDisableVertexAttribArray(0);
	}
};

#endif