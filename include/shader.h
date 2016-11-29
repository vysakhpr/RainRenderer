#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <sstream>
#include <stdio.h>

GLuint gWorldLocation,gWVPLocation,gCameraViewLocation,gProjectionLocation;
GLuint DLightColorLocation,DLightAmbientIntensityLocation,DLightDirectionLocation,DLightDiffuseIntensityLocation;
GLuint gEyeWorldPositionLocation,SpecularIntensityLocation,SpecularPowerLocation;
GLuint PLightColorLocation, PLightAmbientIntensityLocation, PLightDiffuseIntensityLocation, PLightPositionLocation;
GLuint PLightAttenuationConstantLocation,PLightAttenuationLinearLocation,PLightAttenuationExpLocation;

GLuint RainBoundBoxLocation,SlopeLocation,OptimizeLocation;


GLuint textureLocation,textureBridgeLocation,textureNormalLocation, textureSpecLocation,texture;
GLuint ShaderProgram;
GLuint BridgeShaderProgram;


static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar * p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

static void AddBridgeShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	const GLchar * p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}


void UseRainShaderProgram()
{
	glUseProgram(ShaderProgram);
	gWVPLocation=glGetUniformLocation(ShaderProgram,"gWVP");
	gWorldLocation=glGetUniformLocation(ShaderProgram,"gWorld");
	gCameraViewLocation=glGetUniformLocation(ShaderProgram,"gCamera");
	gProjectionLocation=glGetUniformLocation(ShaderProgram,"gProjectionLocation");

	textureLocation=glGetUniformLocation(ShaderProgram,"gRain");
	texture=glGetUniformLocation(ShaderProgram,"gTexArray");
	SlopeLocation=glGetUniformLocation(ShaderProgram,"gSlope");
	OptimizeLocation=glGetUniformLocation(ShaderProgram,"gOptimize");


	DLightColorLocation=glGetUniformLocation(ShaderProgram,"gDirectionalLight.Color");
	DLightAmbientIntensityLocation=glGetUniformLocation(ShaderProgram,"gDirectionalLight.AmbientIntensity");
	DLightDirectionLocation=glGetUniformLocation(ShaderProgram,"gDirectionalLight.Direction");
	DLightDiffuseIntensityLocation=glGetUniformLocation(ShaderProgram,"gDirectionalLight.DiffuseIntensity");
	gEyeWorldPositionLocation=glGetUniformLocation(ShaderProgram,"gEyeWorldPosition");
	SpecularIntensityLocation=glGetUniformLocation(ShaderProgram,"gSpecularIntensity");
	SpecularPowerLocation=glGetUniformLocation(ShaderProgram,"gSpecularPower");
	PLightPositionLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.Position");
	PLightColorLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.Color");
	PLightAmbientIntensityLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.AmbientIntensity");
	PLightDiffuseIntensityLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.DiffuseIntensity");
	PLightAttenuationConstantLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.Attenuation.Constant");
	PLightAttenuationLinearLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.Attenuation.Linear");
	PLightAttenuationExpLocation=glGetUniformLocation(ShaderProgram,"gPositionalLight.Attenuation.Exponential");

	RainBoundBoxLocation=glGetUniformLocation(ShaderProgram,"rainBoxWidth");


	if(	gWVPLocation==0xFFFFFFFF || gWorldLocation==0xFFFFFFFF || gCameraViewLocation==0xFFFFFFFF || RainBoundBoxLocation==0xFFFFFFFF )
	{
		cout<<"Location Cannot be found"<<endl;
		exit(1);
	}
}


void UseBridgeShaderProgram()
{
	glUseProgram(BridgeShaderProgram);
	gWVPLocation=glGetUniformLocation(BridgeShaderProgram,"gbWVP");
	gWorldLocation=glGetUniformLocation(BridgeShaderProgram,"gbWorld");


	textureBridgeLocation=glGetUniformLocation(BridgeShaderProgram,"gBridge");
	textureNormalLocation=glGetUniformLocation(BridgeShaderProgram,"gNormalTexture");
	textureSpecLocation=glGetUniformLocation(BridgeShaderProgram,"gSpecularTexture");

	
	DLightColorLocation=glGetUniformLocation(BridgeShaderProgram,"gDirectionalLight.Color");
	DLightAmbientIntensityLocation=glGetUniformLocation(BridgeShaderProgram,"gDirectionalLight.AmbientIntensity");
	DLightDirectionLocation=glGetUniformLocation(BridgeShaderProgram,"gDirectionalLight.Direction");
	DLightDiffuseIntensityLocation=glGetUniformLocation(BridgeShaderProgram,"gDirectionalLight.DiffuseIntensity");
	gEyeWorldPositionLocation=glGetUniformLocation(BridgeShaderProgram,"gEyeWorldPosition");
	SpecularIntensityLocation=glGetUniformLocation(BridgeShaderProgram,"gSpecularIntensity");
	SpecularPowerLocation=glGetUniformLocation(BridgeShaderProgram,"gSpecularPower");
	PLightPositionLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.Position");
	PLightColorLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.Color");
	PLightAmbientIntensityLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.AmbientIntensity");
	PLightDiffuseIntensityLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.DiffuseIntensity");
	PLightAttenuationConstantLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.Attenuation.Constant");
	PLightAttenuationLinearLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.Attenuation.Linear");
	PLightAttenuationExpLocation=glGetUniformLocation(BridgeShaderProgram,"gPositionalLight.Attenuation.Exponential");
	
	//cout<<dWorldLocation<<endl;

	//if(	gWVPLocation==0xFFFFFFFF || gWorldLocation==0xFFFFFFFF )
	//{
	//	cout<<" BridgLocation Cannot be found"<<endl;
	//	exit(1);
	//}
}


using namespace std;

static void CompileShaders() {

	ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	string vs, fs, gs;

	if (!ReadFile(pVSFileName, vs)) {
		exit(1);
	}

	if (!ReadFile(pFSFileName, fs)) {
		exit(1);
	}

	if (!ReadFile(pGSFileName, gs)) {
		exit(1);
	}

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);
	AddShader(ShaderProgram, gs.c_str(), GL_GEOMETRY_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = {0};

	glLinkProgram(ShaderProgram);
	
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof (ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof (ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	
}


static void CompileBridgeShaders() {

	BridgeShaderProgram = glCreateProgram();

	if (BridgeShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	string vs, fs, gs;

	if (!ReadFile(bVSFileName, vs)) {
		exit(1);
	}

	if (!ReadFile(bFSFileName, fs)) {
		exit(1);
	}

	AddBridgeShader(BridgeShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddBridgeShader(BridgeShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = {0};

	glLinkProgram(BridgeShaderProgram);
	
	glGetProgramiv(BridgeShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(BridgeShaderProgram, sizeof (ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking BridgeShaderProgram: '%s'\n", ErrorLog);
		exit(1);
	}

	glValidateProgram(BridgeShaderProgram);
	glGetProgramiv(BridgeShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(BridgeShaderProgram, sizeof (ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid BridgeShaderProgram program: '%s'\n", ErrorLog);
		exit(1);
	}

	
}





void SetRainBoundBoxInShader()
{
	glUniform3f(RainBoundBoxLocation,RainBoundBox.XWidth,RainBoundBox.YWidth,RainBoundBox.ZWidth);
}

void SetTextureInRainShader(string s)
{
	//glUniform1i(textureLocation, 0);
	//glActiveTexture(GL_TEXTURE0+0);
	//lBindTexture(GL_TEXTURE_2D, texture);

	//GLuint textureLocation;
    glGenTextures(1, &textureLocation);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureLocation);
    image = SOIL_load_image(s.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textureLocation);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void SetTextureInBridgeShader(string s, string v, string t)
{
	//glUniform1i(textureLocation, 0);
	//glActiveTexture(GL_TEXTURE0+0);
	//lBindTexture(GL_TEXTURE_2D, texture);

	//GLuint textureLocation;
    glGenTextures(1, &textureBridgeLocation);
    glGenTextures(1, &textureNormalLocation);
    glGenTextures(1, &textureSpecLocation);

    

    glActiveTexture(GL_TEXTURE0);
    /*glBindTexture(GL_TEXTURE_2D, textureBridgeLocation);
    image = SOIL_load_image(s.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    */

    textureBridgeLocation = SOIL_load_OGL_texture
	(
		s.c_str(),
		SOIL_LOAD_AUTO,
		textureBridgeLocation,
		SOIL_FLAG_DDS_LOAD_DIRECT
	);
	
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBridgeLocation);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE1);
    /*glBindTexture(GL_TEXTURE_2D, textureBridgeLocation);
    image = SOIL_load_image(s.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    */

    textureNormalLocation = SOIL_load_OGL_texture
	(
		v.c_str(),
		SOIL_LOAD_AUTO,
		textureNormalLocation,
		SOIL_FLAG_DDS_LOAD_DIRECT
	);
	
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureNormalLocation);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glActiveTexture(GL_TEXTURE2);
    /*glBindTexture(GL_TEXTURE_2D, textureBridgeLocation);
    image = SOIL_load_image(s.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        SOIL_free_image_data(image);
    */

    textureSpecLocation = SOIL_load_OGL_texture
	(
		t.c_str(),
		SOIL_LOAD_AUTO,
		textureSpecLocation,
		SOIL_FLAG_DDS_LOAD_DIRECT
	);
	
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, textureSpecLocation);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



}


void LoadArrayTexture()
{
	int count=180;
    unsigned char * images[count];
    int width, height;

    glEnable(GL_TEXTURE_3D);
    glGenTextures(1,&texture);
    
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

    for (int i = 0; i < count; ++i)
    {
    	stringstream out;
        out<<i+1;
        string k=("Drops/"+out.str()+".png");
    	images[i]=SOIL_load_image(k.c_str(), &width, &height, 0, SOIL_LOAD_RGB);  	
    }
    //images[0]=SOIL_load_image("Drops/1.png", &width, &height, 0, SOIL_LOAD_RGB);  
    //images[1]=SOIL_load_image("Drops/2.png", &width, &height, 0, SOIL_LOAD_RGB);  


    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGB, width, height, 2*count);


    for (int i = 0; i < count; ++i)
    {
    	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, count, GL_RGB, GL_UNSIGNED_BYTE, images[i]);
    }
    
	//glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, count, GL_RGB, GL_UNSIGNED_BYTE, images[0]);
	//glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 1, width, height, count, GL_RGB, GL_UNSIGNED_BYTE, images[1]);
	

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    for (int i = 0; i < count; ++i)
    {
    	SOIL_free_image_data(images[i]);
    }


}

void SetLightsInShader(Lighting lights, Camera cam)
{
	DirectionalLight DLight=lights.GetDirectionalLight();
	glUniform3f(DLightColorLocation, DLight.Color.x, DLight.Color.y, DLight.Color.z);
    glUniform1f(DLightAmbientIntensityLocation, DLight.AmbientIntensity);
    Vector3f Direction=DLight.Direction;
    Direction.Normalize();
    glUniform3f(DLightDirectionLocation,Direction.x,Direction.y,Direction.z);
    glUniform1f(DLightDiffuseIntensityLocation,DLight.DiffuseIntensity);
	glUniform3f(gEyeWorldPositionLocation,cam.GetPosition().x,cam.GetPosition().y,cam.GetPosition().z);
    glUniform1f(SpecularIntensityLocation,1.0f);
    glUniform1f(SpecularPowerLocation,2);
    PositionalLight PLight=lights.GetPositionalLight();
    glUniform3f(PLightColorLocation,PLight.Color.x,PLight.Color.y,PLight.Color.z);
    glUniform3f(PLightPositionLocation,PLight.Position.x,PLight.Position.y,PLight.Position.z);
    glUniform1f(PLightDiffuseIntensityLocation,PLight.DiffuseIntensity);
    glUniform1f(PLightAmbientIntensityLocation, PLight.AmbientIntensity);
    glUniform1f(PLightAttenuationConstantLocation,PLight.Attenuation.Constant);
    glUniform1f(PLightAttenuationLinearLocation,PLight.Attenuation.Linear);
    glUniform1f(PLightAttenuationExpLocation,PLight.Attenuation.Exponential);

}

#endif