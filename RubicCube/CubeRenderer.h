#pragma once

#include "RubikCube.h"

const int DEFAULT_WIDTH = 1250;
const int DEFAULT_HEIGHT = 660;

class CubeRenderer
{
private:
	RubikCube* m_cube;
	int m_width;
	int m_height;

	void renderMap();
	void renderMapSurface(const std::shared_ptr<CubeSurface> surface, int cubeLeft, int cubeTop,
		int surfaceSize = 90, int spacing = 1);
	void renderMainView();
	void renderLeftView();
	void renderRightView();
	void renderText();

public:
	CubeRenderer(RubikCube* cube);
	CubeRenderer(RubikCube* cube, int width, int height);
	void update();
	~CubeRenderer();
};
