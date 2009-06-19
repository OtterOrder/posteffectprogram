sampler DiffuseSampler = 
sampler_state
{
    AddressU  = WRAP;        
	AddressV  = WRAP;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

sampler NormalSampler = 
sampler_state
{
    AddressU  = WRAP;        
	AddressV  = WRAP;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4 PSTextureDisplay (float2 _uv : TEXCOORD0)	: COLOR0
{
	float4 diffuseColor = tex2D(DiffuseSampler, _uv);
	float4 normalColor = tex2D(NormalSampler, _uv);

	bool DisplayDiffuse = false;

	if (DisplayDiffuse == true)
	{
		diffuseColor.a = normalColor.a;
		return diffuseColor;
	}
	else
	{
		normalColor.a = diffuseColor.a;
		return normalColor;
	}
}

//******************************************************************************************************************************