#include "pch.h"
#include "Pvector.h"

using namespace std;

using namespace DirectX;
using namespace DirectX::SimpleMath;

Pvector::Pvector(const Vector3& _comp)
{
	m_vector = _comp;
}