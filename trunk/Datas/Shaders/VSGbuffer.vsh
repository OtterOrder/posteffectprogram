
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix
float4x4 g_mWorld;					// World projection		

struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float2 UV		: TEXCOORD0;
	float3 WorldPos	: TEXCOORD1;
};

VS_OUTPUT VSTest (	float4 vPos : POSITION,
					float2 vUV : TEXCOORD0)
{
    VS_OUTPUT Output;

	Output.Position = mul(vPos, g_mWorldViewProjection);
	Output.WorldPos = mul(vPos, g_mWorld);
	Output.UV = vUV;

	return Output;
}