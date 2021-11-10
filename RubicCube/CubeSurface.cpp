#include "CubeSurface.h"


CubeSurface::CubeSurface(SurfaceColor c, int s)
	: m_color(c), m_size(s)
{
	this->surface = std::vector<std::vector<SurfaceColor>>(m_size);
	for (int i = 0; i < m_size; ++i) {
		this->surface[i] = std::vector<SurfaceColor>(m_size);
		for (int j = 0; j < m_size; ++j) {
			this->surface[i][j] = m_color;
		}
	}
}

std::vector<SurfaceColor>& CubeSurface::operator[](int index)
{
	return this->surface[index];
}

const std::vector<SurfaceColor>& CubeSurface::operator[](int index) const
{
	return this->surface[index];
}

void CubeSurface::reset()
{
	for (int i = 0; i < m_size; ++i)
		for (int j = 0; j < m_size; ++j)
			this->surface[i][j] = m_color;
}
