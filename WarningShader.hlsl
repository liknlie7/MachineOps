sampler TextureSampler : register(s0);

cbuffer cbChangesEveryFrame : register(b0)
{
	float3 pos;		// ç¿ïW
};

float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
	return float4(0,0,0,0);
}