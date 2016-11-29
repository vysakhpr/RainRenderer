#version 330

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D gRain;
uniform sampler2DArray gTexArray;
uniform mat4 gWorld;





struct DirectionalLight
{
	vec3 Color;
	float AmbientIntensity;
	vec3 Direction;
	float DiffuseIntensity;
};


struct PositionalLight
{	
	vec3 Color;
	vec3 Position;
	float AmbientIntensity;
	float DiffuseIntensity;
	struct 
	{
		float Constant;
		float Linear;
		float Exponential;
	}Attenuation;
};

uniform DirectionalLight gDirectionalLight;
uniform PositionalLight  gPositionalLight;
uniform float gSpecularIntensity, gSpecularPower;
uniform vec3 gEyeWorldPosition;
in vec3 Normal0;
in vec3 WorldPos0;



float g_rainfactors[185] = 
    {

        0.004535 , 0.014777 , 0.012512 , 0.130630 , 0.013893 , 0.125165 , 0.011809 , 0.244907 , 0.010722 , 0.218252,
        0.011450 , 0.016406 , 0.015855 , 0.055476 , 0.015024 , 0.067772 , 0.021120 , 0.118653 , 0.018705 , 0.142495, 
        0.004249 , 0.017267 , 0.042737 , 0.036384 , 0.043433 , 0.039413 , 0.058746 , 0.038396 , 0.065664 , 0.054761, 
        0.002484 , 0.003707 , 0.004456 , 0.006006 , 0.004805 , 0.006021 , 0.004263 , 0.007299 , 0.004665 , 0.007037, 
        0.002403 , 0.004809 , 0.004978 , 0.005211 , 0.004855 , 0.004936 , 0.006266 , 0.007787 , 0.006973 , 0.007911, 
        0.004843 , 0.007565 , 0.007675 , 0.011109 , 0.007726 , 0.012165 , 0.013179 , 0.021546 , 0.013247 , 0.012964, 
        0.105644 , 0.126661 , 0.128746 , 0.101296 , 0.123779 , 0.106198 , 0.123470 , 0.129170 , 0.116610 , 0.137528, 
        0.302834 , 0.379777 , 0.392745 , 0.339152 , 0.395508 , 0.334227 , 0.374641 , 0.503066 , 0.387906 , 0.519618, 
        0.414521 , 0.521799 , 0.521648 , 0.498219 , 0.511921 , 0.490866 , 0.523137 , 0.713744 , 0.516829 , 0.743649, 
        0.009892 , 0.013868 , 0.034567 , 0.025788 , 0.034729 , 0.036399 , 0.030606 , 0.017303 , 0.051809 , 0.030852, 
        0.018874 , 0.027152 , 0.031625 , 0.023033 , 0.038150 , 0.024483 , 0.029034 , 0.021801 , 0.037730 , 0.016639, 
        0.002868 , 0.004127 , 0.133022 , 0.013847 , 0.123368 , 0.012993 , 0.122183 , 0.015031 , 0.126043 , 0.015916, 
        0.002030 , 0.002807 , 0.065443 , 0.002752 , 0.069440 , 0.002810 , 0.081357 , 0.002721 , 0.076409 , 0.002990, 
        0.002425 , 0.003250 , 0.003180 , 0.011331 , 0.002957 , 0.011551 , 0.003387 , 0.006086 , 0.002928 , 0.005548, 
        0.003664 , 0.004258 , 0.004269 , 0.009404 , 0.003925 , 0.009233 , 0.004224 , 0.009405 , 0.004014 , 0.008435, 
        0.038058 , 0.040362 , 0.035946 , 0.072104 , 0.038315 , 0.078789 , 0.037069 , 0.077795 , 0.042554 , 0.073945, 
        0.124160 , 0.122589 , 0.121798 , 0.201886 , 0.122283 , 0.214549 , 0.118196 , 0.192104 , 0.122268 , 0.209397, 
        0.185212 , 0.181729 , 0.194527 , 0.420721 , 0.191558 , 0.437096 , 0.199995 , 0.373842 , 0.192217 , 0.386263, 
        0.003520 , 0.053502 , 0.060764 , 0.035197 , 0.055078 
        };
    




vec4 CalculateDirectionalLight()
{
	vec4 DiffuseColor,SpecularColor;
	vec3 Normal=normalize(Normal0);
	vec4 AmbientColor=vec4(gDirectionalLight.Color*gDirectionalLight.AmbientIntensity,1.0);
	float DiffuseFactor=dot(Normal,-gDirectionalLight.Direction);
	if(DiffuseFactor>0)																//angle is between -90 to 90.
	{
		DiffuseColor=vec4(gDirectionalLight.Color,1.0f)*gDirectionalLight.DiffuseIntensity*DiffuseFactor;
		vec3 VertexToEye=normalize(gEyeWorldPosition-WorldPos0);
		vec3 ReflectedLight=normalize(reflect(gDirectionalLight.Direction,Normal));
	}
	else
	{
		DiffuseColor=vec4(0,0,0,0);
		SpecularColor=vec4(0,0,0,0);
	}
	return(AmbientColor);
}



vec4  CalculatePositionalLight()
{
	
	vec3 LightDirection=WorldPos0-(vec4(gPositionalLight.Position,1.0)).xyz;
	float distance=length(LightDirection);
	LightDirection=normalize(LightDirection);

	vec4 DiffuseColor,SpecularColor;

	vec3 Normal=normalize(Normal0);


	vec4 AmbientColor=vec4(gPositionalLight.Color*gPositionalLight.AmbientIntensity,1.0);
	float DiffuseFactor=dot(Normal,-LightDirection);
	if(DiffuseFactor!=0)																//angle is between -90 to 90.
	{
		DiffuseColor=vec4(gPositionalLight.Color,1.0f)*gPositionalLight.DiffuseIntensity*abs(DiffuseFactor);
		vec3 VertexToEye=normalize(gEyeWorldPosition-WorldPos0);
		vec3 ReflectedLight=normalize(reflect(LightDirection,Normal));
		float SpecularFactor=dot(VertexToEye,ReflectedLight);
		if(SpecularFactor>0)
		{
			SpecularFactor=pow(SpecularFactor,gSpecularPower);
			SpecularColor= vec4(gPositionalLight.Color*gSpecularIntensity*SpecularFactor,1.0f);
		}
	}
	else
	{
		DiffuseColor=vec4(0,0,0,0);
		SpecularColor=vec4(0,0,0,0);
	}

	vec4 TotalColor=(AmbientColor+DiffuseColor+SpecularColor);
	float Attenuation=gPositionalLight.Attenuation.Constant+(gPositionalLight.Attenuation.Linear*distance)+(gPositionalLight.Attenuation.Exponential*distance*distance);
	return TotalColor/Attenuation;
}
vec3 CalculateTexture()
{
	float opacity = 0.0;
	#define MAX_VIDX 2
    #define MAX_HIDX 4
    #define PI 3.1415926535897932384626433832795
	vec3 L=-normalize(WorldPos0-(vec4(gPositionalLight.Position,1.0)).xyz);
	vec3 E=normalize(gEyeWorldPosition-WorldPos0);
	vec3 N=vec3(0,-1,0);


	bool is_EpLp_angle_ccw = true;
        float hangle = 0;
        float vangle = abs( (acos(dot(L,N)) * 180/PI) - 90 ); // 0 to 90
       
        vec3 Lp = normalize( L - dot(L,N)*N );
        vec3 Ep = normalize( E - dot(E,N)*N );
        hangle = acos( dot(Ep,Lp) ) * 180/PI;  // 0 to 180
        hangle = (hangle-10)/40.0;           // -0.25 to 4.25
        is_EpLp_angle_ccw = dot( N, cross(Ep,Lp)) > 0;

    if(vangle>=88.0)
        {
            hangle = 0;
            is_EpLp_angle_ccw = true;
        }
                
    vangle = (vangle-10.0)/40.0; // -0.25 to 2.25
    int verticalLightIndex1 = int(floor(vangle)); // 0 to 2.25
    int verticalLightIndex2 = min(MAX_VIDX, (verticalLightIndex1 + 1) );
    verticalLightIndex1 = max(0, verticalLightIndex1);
    float t = fract(vangle);

    // textureCoordsH[1|2] used in case we need to flip the texture horizontally
    float textureCoordsH1 = texCoord.x;
    float textureCoordsH2 = texCoord.x;
        
    // horizontalLightIndex[1|2] - two indices in the horizontal direction
    // s - fraction at which the hangle is between these two indices (for lerp)
	int horizontalLightIndex1 = 0;
	int horizontalLightIndex2 = 0;
	float s = 0;
    
    s = fract(hangle);
    horizontalLightIndex1 = int(floor(hangle)); // 0 to 8
    horizontalLightIndex2 = horizontalLightIndex1+1;
    if( horizontalLightIndex1 < 0 )
	{
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
    }
                   
    if( is_EpLp_angle_ccw )
    {
        if( horizontalLightIndex2 > MAX_HIDX ) 
        {
            horizontalLightIndex2 = MAX_HIDX;
            textureCoordsH2 = 1.0 - textureCoordsH2;
        }
    }
    else
    {
        textureCoordsH1 = 1.0 - textureCoordsH1;
        if( horizontalLightIndex2 > MAX_HIDX ) 
        {
            horizontalLightIndex2 = MAX_HIDX;
        } else 
        {
            textureCoordsH2 = 1.0 - textureCoordsH2;
        }
    }
            
    if( verticalLightIndex1 >= MAX_VIDX )
    {
        textureCoordsH2 = texCoord.x;
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
        s = 0;
    }


	uint type = 2;
    vec2 texIndicesV1 = vec2(verticalLightIndex1*90 + horizontalLightIndex1*10 + type,
                                 verticalLightIndex1*90 + horizontalLightIndex2*10 + type);
    vec3 tex1 = vec3(textureCoordsH1, texCoord.y, texIndicesV1.x);
    vec3 tex2 = vec3(textureCoordsH2, texCoord.y, texIndicesV1.y);
    if( (verticalLightIndex1<2) && (verticalLightIndex2>=2) ) 
    {
        s = 0;
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
        textureCoordsH1 = texCoord.x;
        textureCoordsH2 = texCoord.x;
    }
        
    vec2 texIndicesV2 = vec2(verticalLightIndex2*90 + horizontalLightIndex1*10 + type,
    						 verticalLightIndex2*90 + horizontalLightIndex2*10 + type);
    vec3 tex3 = vec3(textureCoordsH1, texCoord.y, texIndicesV2.x);        
    vec3 tex4 = vec3(textureCoordsH2, texCoord.y, texIndicesV2.y);

    return 4*(texture2DArray(gTexArray,tex2).rgb); 
	
}

float CalculateTextureIntensity()
{

	float opacity = 0.0;
	#define MAX_VIDX 2
    #define MAX_HIDX 4
    #define PI 3.1415926535897932384626433832795
	vec3 L=-normalize(WorldPos0-(vec4(gPositionalLight.Position,1.0)).xyz);
	vec3 E=normalize(gEyeWorldPosition-WorldPos0);
	vec3 N=vec3(0,-1,0);


	bool is_EpLp_angle_ccw = true;
        float hangle = 0;
        float vangle = abs( (acos(dot(L,N)) * 180/PI) - 90 ); // 0 to 90
       
        vec3 Lp = normalize( L - dot(L,N)*N );
        vec3 Ep = normalize( E - dot(E,N)*N );
        hangle = acos( dot(Ep,Lp) ) * 180/PI;  // 0 to 180
        hangle = (hangle-10)/40.0;           // -0.25 to 4.25
        is_EpLp_angle_ccw = dot( N, cross(Ep,Lp)) > 0;

    if(vangle>=88.0)
        {
            hangle = 0;
            is_EpLp_angle_ccw = true;
        }
                
    vangle = (vangle-10.0)/40.0; // -0.25 to 2.25
    int verticalLightIndex1 = int(floor(vangle)); // 0 to 2.25
    int verticalLightIndex2 = min(MAX_VIDX, (verticalLightIndex1 + 1) );
    verticalLightIndex1 = max(0, verticalLightIndex1);
    float t = fract(vangle);

    // textureCoordsH[1|2] used in case we need to flip the texture horizontally
    float textureCoordsH1 = texCoord.x;
    float textureCoordsH2 = texCoord.x;
        
    // horizontalLightIndex[1|2] - two indices in the horizontal direction
    // s - fraction at which the hangle is between these two indices (for lerp)
	int horizontalLightIndex1 = 0;
	int horizontalLightIndex2 = 0;
	float s = 0;
    
    s = fract(hangle);
    horizontalLightIndex1 = int(floor(hangle)); // 0 to 8
    horizontalLightIndex2 = horizontalLightIndex1+1;
    if( horizontalLightIndex1 < 0 )
	{
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
    }
                   
    if( is_EpLp_angle_ccw )
    {
        if( horizontalLightIndex2 > MAX_HIDX ) 
        {
            horizontalLightIndex2 = MAX_HIDX;
            textureCoordsH2 = 1.0 - textureCoordsH2;
        }
    }
    else
    {
        textureCoordsH1 = 1.0 - textureCoordsH1;
        if( horizontalLightIndex2 > MAX_HIDX ) 
        {
            horizontalLightIndex2 = MAX_HIDX;
        } else 
        {
            textureCoordsH2 = 1.0 - textureCoordsH2;
        }
    }
            
    if( verticalLightIndex1 >= MAX_VIDX )
    {
        textureCoordsH2 = texCoord.x;
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
        s = 0;
    }


	uint type = 2;
    ivec2 texIndicesV1 = ivec2(verticalLightIndex1*90 + horizontalLightIndex1*10 + type,
                                 verticalLightIndex1*90 + horizontalLightIndex2*10 + type);
    vec3 tex1 = vec3(textureCoordsH1, texCoord.y, texIndicesV1.x);
    vec3 tex2 = vec3(textureCoordsH2, texCoord.y, texIndicesV1.y);
    if( (verticalLightIndex1<2) && (verticalLightIndex2>=2) ) 
    {
        s = 0;
        horizontalLightIndex1 = 0;
        horizontalLightIndex2 = 0;
        textureCoordsH1 = texCoord.x;
        textureCoordsH2 = texCoord.x;
    }
        
    ivec2 texIndicesV2 = ivec2(verticalLightIndex2*90 + horizontalLightIndex1*10 + type,
    						 verticalLightIndex2*90 + horizontalLightIndex2*10 + type);
    vec3 tex3 = vec3(textureCoordsH1, texCoord.y, texIndicesV2.x);        
    vec3 tex4 = vec3(textureCoordsH2, texCoord.y, texIndicesV2.y);

    //return texture2DArray(gTexArray,tex2).rgb; 

    
    float col1 = texture2DArray(gTexArray,tex1).a * g_rainfactors[texIndicesV1.x];
    float col2 = texture2DArray(gTexArray,tex2).a * g_rainfactors[texIndicesV1.y];
    float col3 = texture2DArray(gTexArray,tex3).a * g_rainfactors[texIndicesV2.x];
    float col4 = texture2DArray(gTexArray,tex4).a * g_rainfactors[texIndicesV2.y];
    float hOpacity1 = mix(col1,col2,s);
    float hOpacity2 = mix(col3,col4,s);
    opacity = mix(hOpacity1,hOpacity2,t);
    opacity = pow(opacity,0.7); // inverse gamma correction (expand dynamic range)
    opacity = 4* opacity;
   	return opacity;
   	
}


void main()
{
	vec4 TotalLight=CalculateDirectionalLight()+CalculatePositionalLight();
	//FragColor= vec4(texture2D(gTexArray,texCoord).rgb,1.0);
	//FragColor= vec4(texture2DArray(gTexArray,vec3(texCoord,1)).rgb,1.0)*TotalLight;
	FragColor= vec4(CalculateTexture(),1.0)*4*TotalLight;	
	//FragColor= vec4(1.0,1.0,1.0,1.0)*TotalLight*CalculateTextureIntensity();
	//FragColor= vec4(1.0,1.0,1.0,1.0)*TotalLight;
	//FragColor= vec4(1.0,1.0,1.0,1.0);

}
