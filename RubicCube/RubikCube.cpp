#include <easyx.h>
#include <algorithm>
#include <iostream>
#include "RubikCube.h"

using std::cout;
using std::endl;

RubikCube::RubikCube(int size)
	: cubeSize(size), m_topSurface(new CubeSurface(SurfaceColor::Yello, size)),
	m_bottomSurface(new CubeSurface(SurfaceColor::White, size)),
	m_leftSurface(new CubeSurface(SurfaceColor::Blue, size)), m_rightSurface(new CubeSurface(SurfaceColor::Green, size)),
	m_frontSurface(new CubeSurface(SurfaceColor::Red, size)), m_backSurface(new CubeSurface(SurfaceColor::Orange, size)) {}

void RubikCube::leftToRight(int y)
{
	auto tmp1 = (*m_backSurface)[y];
	auto tmp2 = (*m_frontSurface)[y];
	auto tmp3 = (*m_leftSurface)[y];
	auto tmp4 = (*m_rightSurface)[y];
	(*m_rightSurface)[y] = tmp1;
	(*m_backSurface)[y] = tmp4;
	(*m_leftSurface)[y] = tmp2;
	(*m_frontSurface)[y] = tmp3;

	if (y == 0) rotateSurface(m_topSurface, true);
	if (y == cubeSize - 1) rotateSurface(m_bottomSurface);
}

void RubikCube::rightToleft(int y)
{
	auto tmp1 = (*m_frontSurface)[y];
	auto tmp2 = (*m_leftSurface)[y];
	auto tmp3 = (*m_backSurface)[y];
	auto tmp4 = (*m_rightSurface)[y];
	(*m_leftSurface)[y] = tmp1;
	(*m_backSurface)[y] = tmp2;
	(*m_rightSurface)[y] = tmp3;
	(*m_frontSurface)[y] = tmp4;

	if (y == 0) rotateSurface(m_topSurface);
	if (y == cubeSize - 1) rotateSurface(m_bottomSurface, true);
}

void RubikCube::upToDown(int x)
{
	std::vector<std::vector<SurfaceColor>> temp(4);

	for (int i = 0; i < 4; ++i)
		temp[i] = std::vector<SurfaceColor>(cubeSize);
	for (int i = 0; i < cubeSize; ++i)
		temp[0][i] = (*m_frontSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[1][i] = (*m_bottomSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[2][i] = (*m_backSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[3][i] = (*m_topSurface)[i][x];

	for (int i = 0; i < cubeSize; ++i)
		(*m_bottomSurface)[i][x] = temp[0][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_backSurface)[i][x] = temp[1][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_topSurface)[i][x] = temp[2][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_frontSurface)[i][x] = temp[3][i];
	//若为侧面，则翻转
	if (x == 0)
		rotateSurface(m_leftSurface);
	if (x == cubeSize - 1)
		rotateSurface(m_rightSurface, true);
}

void RubikCube::downToUp(int x)
{
	std::vector<std::vector<SurfaceColor>> temp(4);
	for (int i = 0; i < 4; ++i)
		temp[i] = std::vector<SurfaceColor>(cubeSize);
	for (int i = 0; i < cubeSize; ++i)
		temp[0][i] = (*m_frontSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[1][i] = (*m_topSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[2][i] = (*m_backSurface)[i][x];
	for (int i = 0; i < cubeSize; ++i)
		temp[3][i] = (*m_bottomSurface)[i][x];

	for (int i = 0; i < cubeSize; ++i)
		(*m_topSurface)[i][x] = temp[0][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_backSurface)[i][x] = temp[1][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_bottomSurface)[i][x] = temp[2][i];
	for (int i = 0; i < cubeSize; ++i)
		(*m_frontSurface)[i][x] = temp[3][i];
	if (x == 0)
		rotateSurface(m_leftSurface, true);
	if (x == cubeSize - 1)
		rotateSurface(m_rightSurface);
}

void RubikCube::control_R(int mode)
{
	if (mode) upToDown(cubeSize - 1);
	else downToUp(cubeSize - 1);
}

void RubikCube::control_U(int mode)
{
	if (mode) leftToRight(0);
	else rightToleft(0);
}

void RubikCube::control_D(int mode)
{
	if (mode) leftToRight(cubeSize - 1);
	else rightToleft(cubeSize - 1);
}

void RubikCube::control_F(int mode)
{
	auto temp = m_frontSurface;
	auto temp1 = m_leftSurface;
	auto temp2 = m_backSurface;
	auto temp3 = m_rightSurface;
	m_frontSurface = temp3;
	m_leftSurface = temp;
	m_backSurface = temp1;
	m_rightSurface = temp2;
	upToDown(0);
	m_frontSurface = temp;
	m_leftSurface = temp1;
	m_backSurface = temp2;
	m_rightSurface = temp3;
}

void RubikCube::reset()
{
	m_topSurface->reset();
	m_bottomSurface->reset();
	m_leftSurface->reset();
	m_rightSurface->reset();
	m_frontSurface->reset();
	m_backSurface->reset();
}

RubikCube::~RubikCube()
{
	closegraph();
}

void RubikCube::rotateSurface(std::shared_ptr<CubeSurface> surface, bool mode)
{
	if (!mode)
	{
		for (int i = 0; i < cubeSize; ++i)
		{   //倒转每行
			std::reverse((*surface)[i].begin(), (*surface)[i].end());
		}
		for (int i = 0; i < cubeSize; ++i)
		{   //沿右对角线对折
			for (int j = 0; i + j < cubeSize - 1; ++j)
			{
				auto tmp = (*surface)[i][j];
				(*surface)[i][j] = (*surface)[cubeSize - 1 - j][cubeSize - 1 - i];
				(*surface)[cubeSize - 1 - j][cubeSize - 1 - i] = tmp;
			}
		}
	}
	else
	{
		for (int i = 0; i < cubeSize; i++)
		{  // 次对角线翻转
			for (int j = 0; j < cubeSize - i; j++)
			{
				auto tmp = (*surface)[i][j];
				(*surface)[i][j] = (*surface)[cubeSize - j - 1][cubeSize - i - 1];
			}
		}

		for (int i = 0; i < cubeSize; i++) {  // 每行按照中点翻转
			for (int j = 0; j < cubeSize / 2; j++) {
				auto tmp = (*surface)[i][j];
				(*surface)[i][j] = (*surface)[i][cubeSize - j - 1];
				(*surface)[i][cubeSize - j - 1] = tmp;
			}
		}
	}
}