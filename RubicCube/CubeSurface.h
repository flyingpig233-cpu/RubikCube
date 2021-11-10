#pragma once

#include <vector>

enum class SurfaceColor
{
	Red = 0x0000AA, Blue = 0xAA0000, Yello = 0x55FFFF,
	Green = 0x00AA00, Orange = 0x00A5FF, White = 0xFFFFFF
};

class CubeSurface
{
private:
	std::vector<std::vector<SurfaceColor>> surface;

public:
	CubeSurface(SurfaceColor c, int s = 3);

	std::vector<SurfaceColor>& operator[](int index);
	const std::vector<SurfaceColor>& operator[](int index) const;
	void reset();
private:
	SurfaceColor m_color;
	int m_size;
};

