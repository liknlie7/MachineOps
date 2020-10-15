#pragma once

#include <algorithm>

// ”ÍˆÍ“à‚ÉŽû‚ß‚é
template<class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}