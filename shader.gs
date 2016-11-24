#version 330

layout	(points) in;
layout	(triangle_strip,max_vertices=16) out;

uniform mat4 gWorld,gWVP;
uniform mat4 gCamera;
uniform vec3 rainBoxWidth;
uniform vec3 gEyeWorldPosition;

in vec3 vNormal0[];
in vec3 vWorldPos0[];
out vec3 Normal0;
out vec3 WorldPos0;
out vec2 texCoord;

vec3 EyePosition=(gWorld*vec4(gEyeWorldPosition,1.0)).xyz;

void EmitSprites(vec3 va, vec3 vb, vec3 vc, vec3 vd)
{	
	

	gl_Position= gWVP*vec4(va,1.0);
	Normal0=-normalize(EyePosition-va);
	WorldPos0=va;
	texCoord=vec2(0,0.668);
	EmitVertex();

	gl_Position= gWVP*vec4(vb,1.0);
	Normal0=-normalize(EyePosition-vb);
	WorldPos0=vb;
	texCoord=vec2(0,1);
	EmitVertex();

	gl_Position= gWVP*vec4(vd,1.0);
	Normal0=-normalize(EyePosition-vd);
	WorldPos0=vd;
	texCoord=vec2(1*0.00834,0.668);
	EmitVertex();

	gl_Position= gWVP*vec4(vc,1.0);
	Normal0=-normalize(EyePosition-vc);
	WorldPos0=vc;
	texCoord=vec2(1*0.00834,1);
	EmitVertex();

    EndPrimitive();	
}

void main()
{
	mat4 cam=gCamera;
	float size=0.001;

	vec3 up= vec3(cam[0][1],cam[1][1],cam[2][1]);
	vec3 right= vec3(cam[0][0],cam[1][0],cam[2][0]);

	vec3 P = gl_in[0].gl_Position.xyz;
	
	vec3 va = P - (right + 128*up) * size;
	vec3 vb = P - (right - 128*up) * size;
	vec3 vd = P + (right - 128*up) * size;
	vec3 vc = P + (right + 128*up) * size;

	EmitSprites(va,vb,vc,vd);


	va.x=va.x+rainBoxWidth.x;
	vb.x=vb.x+rainBoxWidth.x;
	vc.x=vc.x+rainBoxWidth.x;
	vd.x=vd.x+rainBoxWidth.x;

	EmitSprites(va,vb,vc,vd);

	va.z=va.z+rainBoxWidth.z;
	vb.z=vb.z+rainBoxWidth.z;
	vc.z=vc.z+rainBoxWidth.z;
	vd.z=vd.z+rainBoxWidth.z;

	EmitSprites(va,vb,vc,vd);

	va.x=va.x-rainBoxWidth.x;
	vb.x=vb.x-rainBoxWidth.x;
	vc.x=vc.x-rainBoxWidth.x;
	vd.x=vd.x-rainBoxWidth.x;

	EmitSprites(va,vb,vc,vd);	


}

