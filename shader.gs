#version 330

layout	(points) in;
layout	(triangle_strip,max_vertices=16) out;

uniform mat4 gWorld,gWVP;
uniform mat4 gCamera,gProjectionLocation;
uniform vec3 rainBoxWidth;
uniform vec3 gEyeWorldPosition;
uniform float gSlope;
uniform int gOptimize;
in vec3 vNormal0[];
in vec3 vWorldPos0[];
out vec3 Normal0;
out vec3 WorldPos0;
out vec2 texCoord;

vec3 EyePosition=(vec4(gEyeWorldPosition,1.0)).xyz;


void EmitSprites(vec3 va, vec3 vb, vec3 vc, vec3 vd, vec3 Normal)
{	
	

	gl_Position= gProjectionLocation*gCamera*vec4(va,1.0);
	Normal0=normalize((vec4(Normal,1.0)).xyz);
	WorldPos0=(gWorld*vec4(va,1.0)).xyz;
	texCoord=vec2(0,0.668);
	EmitVertex();

	gl_Position= gProjectionLocation*gCamera*vec4(vb,1.0);
	Normal0=normalize((vec4(Normal,1.0)).xyz);
	WorldPos0=(gWorld*vec4(vb,1.0)).xyz;
	texCoord=vec2(0,1);
	EmitVertex();

	gl_Position= gProjectionLocation*gCamera*vec4(vd,1.0);
	Normal0=normalize((vec4(Normal,1.0)).xyz);
	WorldPos0=(gWorld*vec4(vd,1.0)).xyz;
	texCoord=vec2(1*0.00834,0.668);
	EmitVertex();

	gl_Position= gProjectionLocation*gCamera*vec4(vc,1.0);
	Normal0=normalize((vec4(Normal,1.0)).xyz);
	WorldPos0=(gWorld*vec4(vc,1.0)).xyz;
	texCoord=vec2(1*0.00834,1);
	EmitVertex();

    EndPrimitive();	
}

void EmitDrop(vec3 P, vec3 up, vec3 right)
{
	float size=0.001;
	vec3 Normal=normalize(cross(up,right));
	
	vec3 va = P - (right + 128*up) * size+vec3(gSlope,0,0);
	vec3 vb = P - (right - 128*up) * size;
	vec3 vd = P + (right - 128*up) * size+vec3(gSlope,0,0);
	vec3 vc = P + (right + 128*up) * size;

	EmitSprites(va,vb,vc,vd,Normal);

}

void main()
{

	vec3 rainBox=(vec4(rainBoxWidth,1.0)).xyz;
	mat4 w=gWVP;
	mat4 cam=transpose(gCamera*gWorld);

	vec3 right= vec3(cam[0][0],cam[1][0],cam[2][0]);
	vec3 up= vec3(cam[0][1],cam[1][1],cam[2][1]);

	vec4 Z = gl_in[0].gl_Position;

	vec3 P = (gWorld*Z).xyz;
	
	EmitDrop(P,up,right);

	if(gOptimize)
	{
		Z.x+=rainBox.x;
		P = (gWorld*Z).xyz;
		EmitDrop(P,up,right);

		Z.z+=rainBox.z;
		P = (gWorld*Z).xyz;
		EmitDrop(P,up,right);

		Z.x-=rainBox.x;
		P = (gWorld*Z).xyz;
		EmitDrop(P,up,right);
	}
}

