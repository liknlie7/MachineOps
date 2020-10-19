#pragma once

#include "SimpleMath.h"

class Collision
{
public: // �\����

	// ��
	struct Sphere
	{
		DirectX::SimpleMath::Vector3		center;
		float								radius;
	};

	// ����
	struct Segment
	{
		DirectX::SimpleMath::Vector3 start;
		DirectX::SimpleMath::Vector3 end;
	};

	// �J�v�Z��
	struct Capsule
	{
		Segment segment;
		float radius;
	};

	// �{�b�N�X(�����`)
	struct Box
	{
		DirectX::SimpleMath::Vector3 center;		// ���S���W
		DirectX::SimpleMath::Vector3 radius;		// ���̔���(xyz�e�v�f)
	};

	// �O�p�`�̍\���́i�����ƎO�p�`�̌�������p�j
	struct Triangle
	{
		// �O�p�`�̕��ʕ�����
		DirectX::SimpleMath::Plane p;
		// ��BC�̕��ʕ������i�d�S���W�̒��_a�ɑ΂���d��u��^����j
		DirectX::SimpleMath::Plane edgePlaneBC;
		// ��CA�̕��ʕ������i�d�S���W�̒��_b�ɑ΂���d��v��^����j
		DirectX::SimpleMath::Plane edgePlaneCA;

		// �R���X�g���N�^���ŏՓ˔�����y�����邽�߂ɑO�����Ōv�Z���Ă���
		Triangle(DirectX::SimpleMath::Vector3 a, DirectX::SimpleMath::Vector3 b, DirectX::SimpleMath::Vector3 c)
		{
			DirectX::SimpleMath::Vector3 n = (c - a).Cross(b - a);
			p = DirectX::SimpleMath::Plane(a, n);
			DirectX::SimpleMath::Plane pp = DirectX::SimpleMath::Plane(b, n);
			edgePlaneBC = DirectX::SimpleMath::Plane(b, n.Cross(b - c));
			edgePlaneCA = DirectX::SimpleMath::Plane(c, n.Cross(c - a));
			p.Normalize(); edgePlaneBC.Normalize(); edgePlaneCA.Normalize();
			float bc_scale = 1.0f / (a.Dot(edgePlaneBC.Normal()) + edgePlaneBC.D());
			float ca_scale = 1.0f / (b.Dot(edgePlaneCA.Normal()) + edgePlaneCA.D());
			edgePlaneBC.x *= bc_scale; edgePlaneBC.y *= bc_scale; edgePlaneBC.z *= bc_scale; edgePlaneBC.w *= bc_scale;
			edgePlaneCA.x *= ca_scale; edgePlaneCA.y *= ca_scale; edgePlaneCA.z *= ca_scale; edgePlaneCA.w *= ca_scale;
		}
	};
	// ���������_�̌덷�œ�����ʂ�����̂ŏ����]�T������
#define EPSILON 1.0e-06F


public: // ��{

	Collision() {}
	~Collision() {}

public: // �֐�

	// ���Ƌ��̏Փ˔���
	static bool HitCheckSphereToSphere(const Sphere& _sphereA, const Sphere& _sphereB);

	// ���ƃJ�v�Z���̏Փ˔���
	static bool HitCheckSphereToCapsule(const Sphere& _sphere, const Capsule& _capsule);

	// �J�v�Z���ƃJ�v�Z���̏Փ˔���
	static bool HitCheckCapsuleToCapsule(const Capsule& _capsuleA, const Capsule& _capsuleB);

	// �{�b�N�X�ƃ{�b�N�X�̏Փ˔���
	static bool HitCheckAABB(const Box& _boxA, const Box& _boxB);

	// ���ƃ{�b�N�X�̏Փ˔���
	static bool HitCheckSphereToBox(const Sphere& _sphere, const Box& _box);

	// �����ƎO�p�`�̌�������
	static bool IntersectSegmentTriangle(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end, const Triangle& _tri, DirectX::SimpleMath::Vector3* _crossPoint);

private: // �T�u�֐�

	// �_�Ɛ����̊Ԃ̋����̕�����Ԃ��֐�
	static float SqDistPointSegment(const DirectX::SimpleMath::Vector3& _start, const DirectX::SimpleMath::Vector3& _end, const DirectX::SimpleMath::Vector3& _point);

	// �N�����v�֐�
	static float Clamp(float _n, float _min, float _max);

	// �Q�̐����̍ŒZ�����̕�����Ԃ��֐�
	static float ClosestPtSegmentSegment(DirectX::SimpleMath::Vector3 _start1, DirectX::SimpleMath::Vector3 _end1
		, DirectX::SimpleMath::Vector3 _start2, DirectX::SimpleMath::Vector3 _end2
		, float &s, float &t
		, DirectX::SimpleMath::Vector3& c1, DirectX::SimpleMath::Vector3& c2);

	// �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�����̕������v�Z����֐�
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const Box& _box);
};