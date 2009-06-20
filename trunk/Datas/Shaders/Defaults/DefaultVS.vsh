
float4x4 g_mWorldViewProjection;    // World * View * Projection matrix

struct VS_OUTPUT
{
	float4 Position	: POSITION;
};

VS_OUTPUT VSMain (float4 vPos : POSITION)
{
    VS_OUTPUT Output;

	Output.Position = mul(vPos, g_mWorldViewProjection);

	return Output;
}