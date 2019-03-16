#pragma once


template<typename T>
T Lerp(T p1, T p2, float d)
{
	return p1 + (p2 - p1) * d;
}

template <typename T>
int GetRandomNumber(int min, int max)
{
	static const double fraction = 1.0f / (RAND_MAX + 1.0f);

	return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}


namespace d3d
{
	D3DLIGHT9 InitDirectionalLight(Vector3 *dir, D3DXCOLOR *color);
}