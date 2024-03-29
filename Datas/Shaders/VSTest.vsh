
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float2 UV		: TEXCOORD0;
};

VS_OUTPUT VSTest (	float4 vPos : POSITION,
					float2 vUV : TEXCOORD0)
{
    VS_OUTPUT Output;

	Output.Position = mul(vPos, g_mWorldViewProjection);
	Output.UV = vUV;

	return Output;
}