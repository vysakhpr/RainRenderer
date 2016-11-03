#version 330

layout	(points) in;
layout	(triangle_strip,max_vertices=4) out;

uniform mat4 gWorld,gWVP;
uniform mat4 gCamera;

void main()
{
	mat4 cam=gCamera;
	float size=0.001;

	vec3 up= vec3(cam[0][1],cam[1][1],cam[2][1]);
	vec3 right= vec3(cam[0][0],cam[1][0],cam[2][0]);

	vec3 P = gl_in[0].gl_Position.xyz;
	
	vec3 va = P - (right + 20*up) * size;
	gl_Position= gWVP*vec4(va,1.0);
	EmitVertex();

	vec3 vb = P - (right - 20*up) * size;
	gl_Position= gWVP*vec4(vb,1.0);
	EmitVertex();

	vec3 vd = P + (right - 20*up) * size;
	gl_Position= gWVP*vec4(vd,1.0);
	EmitVertex();

	vec3 vc = P + (right + 20*up) * size;
	gl_Position= gWVP*vec4(vc,1.0);
	EmitVertex();

	

    EndPrimitive();
}