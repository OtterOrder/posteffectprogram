
//******************************************************************************************************************************
float4 PSMainGreen() : COLOR0
{
    return float4( 0.0f, 1.0f, 0.0f, 1.0f );
}

//******************************************************************************************************************************
float4 PSMainRed() : COLOR0
{
    return float4( 1.0f, 0.0f, 0.0f, 1.0f );
}

//******************************************************************************************************************************
texture g_MeshTexture : TEX2;

sampler MeshSampler = 
sampler_state
{
    Texture = <g_MeshTexture>;
    AddressU  = WRAP;        
	AddressV  = WRAP;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4 PSAlbedoDisplay (float2 _uv : TEXCOORD0)	: COLOR0
{
	return tex2D(MeshSampler, _uv);
}

//******************************************************************************************************************************