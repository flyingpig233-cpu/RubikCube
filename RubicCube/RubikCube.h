#pragma once

#include <algorithm>
#include <vector>
#include <memory>
#include "CubeSurface.h"

class RubikCube
{
private:
	//定义魔方6个面
	std::shared_ptr<CubeSurface> m_topSurface;
	std::shared_ptr<CubeSurface> m_bottomSurface;
	std::shared_ptr<CubeSurface> m_frontSurface;
	std::shared_ptr<CubeSurface> m_backSurface;
	std::shared_ptr<CubeSurface> m_leftSurface;
	std::shared_ptr<CubeSurface> m_rightSurface;

	int cubeSize; //魔方阶数

	//初始化面
	void rotateSurface(std::shared_ptr<CubeSurface> surface, bool mode = 0); // mode = 0时顺时针，1为逆时针
public:
	RubikCube(int size = 3);
	void leftToRight(int y);
	void rightToleft(int y);
	void upToDown(int x);
	void downToUp(int x);
	void control_R(int mode = 0);
	void control_U(int mode = 0);
	void control_D(int mode = 0);
	void control_F(int mode = 0);
	void control_B(int mode = 0);
	void control_MU(int mode = 0);
	void control_MF(int mode = 0);
	void control_ML(int mode = 0);
	void reset();
	~RubikCube();

	friend class CubeRenderer;
};
