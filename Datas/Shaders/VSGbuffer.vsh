
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

struct VS_OUTPUT
{
	float4 Position	: POSITION;
	float2 UV		: TEXCOORD0;
	float4 WorldPos	: TEXCOORD1;
	float4 Normal	: NORMAL;
	float3 Tangent	: TEXCOORD2;
	float3 Binormal	: TEXCOORD3;
};

VS_OUTPUT VSTest (	float4 vPos : POSITION,
					float4 vNormal : NORMAL,
					float3 vTangent : TANGENT,
					float3 vBinormal  : BINORMAL,
					float2 vUV : TEXCOORD0)
{
    VS_OUTPUT Output;

	Output.Position = mul(vPos, g_mWorldViewProjection);
	Output.WorldPos = Output.Position;
	Output.UV = vUV;

	Output.Normal = vNormal;
	Output.Tangent = vTangent;
	Output.Binormal = vBinormal;

	return Output;
}