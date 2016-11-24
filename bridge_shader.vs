#version 330

layout (location = 0) in vec3 bPosition;
layout (location = 1) in vec3 bNormal;
layout (location = 2) in vec2 bTexCoord;
layout (location = 3) in vec3 bTangent;
layout (location = 4) in vec3 bBitangent;

out vec3 bNormal0;
out vec3 bWorldPos0;
out vec2 bTexCoord0;
out mat3 TBN;

uniform mat4 gbWorld,gbWVP;


void main()
{

	bNormal0 = (transpose(inverse(gbWorld)) * vec4(bNormal, 0.0)).xyz;
	vec3 T = normalize(vec3(transpose(inverse(gbWorld)) * vec4(bTangent,   0.0)));
   	vec3 B = normalize(vec3(transpose(inverse(gbWorld)) * vec4(bBitangent, 0.0)));
   	vec3 N = normalize(vec3(transpose(inverse(gbWorld)) * vec4(bNormal,    0.0)));
   	TBN = mat3(T, B, N);
    bWorldPos0 = (transpose(inverse(gbWorld))* vec4(bPosition, 0.0)).xyz;
    bTexCoord0=bTexCoord;
    
	gl_Position=gbWVP*vec4(bPosition,1.0);
	//gl_Position=vec4(bPosition,1.0);

}