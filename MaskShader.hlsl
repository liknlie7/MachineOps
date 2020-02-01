sampler TextureSampler : register(s0);

cbuffer cbChangesEveryFrame : register(b0)
{
	float Radius;		// 0�`1
	float AspectRatio;	// �A�X�y�N�g��
};

float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
	// Radias���P�̎���ʑS�̂������Ȃ�
	float r = 0.6f * Radius;
	float x = abs(texCoord.x - 0.5f);
	float y = abs(texCoord.y - 0.5f) / AspectRatio;
	// �e�N�X�`�����W���~�̒����ǂ����Ŕ��f����
	if (x * x + y * y < r * r)
	{
		// ����
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	// �A���t�@�͂P�ɂ���
	float4 col = float4(0, 0, 0, 1);

	return float4(col.r, col.g, col.b, 1.0f);
}