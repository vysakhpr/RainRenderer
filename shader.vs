#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 vNormal0;
out vec3 vWorldPos0;

uniform mat4 gWorld,gWVP;

void main()
{
	gl_Position=vec4(Position,1.0);
	vNormal0 = (transpose(inverse(gWorld)) * vec4(Normal, 0.0)).xyz;
    vWorldPos0 = (transpose(inverse(gWorld))* vec4(Position, 0.0)).xyz;
}