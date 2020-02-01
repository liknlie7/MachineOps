sampler TextureSampler : register(s0);

cbuffer cbChangesEveryFrame : register(b0)
{
	float Radius;		// 0～1
	float AspectRatio;	// アスペクト比
};

float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
	// Radiasが１の時画面全体が黒くなる
	float r = 0.6f * Radius;
	float x = abs(texCoord.x - 0.5f);
	float y = abs(texCoord.y - 0.5f) / AspectRatio;
	// テクスチャ座標が円の中かどうかで判断する
	if (x * x + y * y < r * r)
	{
		// 透明
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	// アルファは１にする
	float4 col = float4(0, 0, 0, 1);

	return float4(col.r, col.g, col.b, 1.0f);
}