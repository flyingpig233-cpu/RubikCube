#include "CubeRenderer.h"
#include <easyx.h>

CubeRenderer::CubeRenderer(RubikCube* cube)
	: m_cube(cube), m_width(DEFAULT_WIDTH), m_height(DEFAULT_HEIGHT)
{
	initgraph(m_width, m_height);
	renderText();
	update();
}

CubeRenderer::CubeRenderer(RubikCube* cube, int width, int height)
	: m_cube(cube), m_width(width), m_height(height)
{
	initgraph(m_width, m_height);
	renderText();
	update();
}

void CubeRenderer::renderMap()
{
	RECT r{ 0, 90, 90, 110 };
	renderMapSurface(m_cube->m_topSurface, 0, 0);
	drawtext(L"TOP", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, 200, 90, 220 };
	renderMapSurface(m_cube->m_bottomSurface, 0, 110);
	drawtext(L"BOTTOM", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r = { 110, 90, 200, 110 };
	renderMapSurface(m_cube->m_leftSurface, 110, 0);
	drawtext(L"LEFT", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r = { 110, 200, 200, 220 };
	renderMapSurface(m_cube->m_rightSurface, 110, 110);
	drawtext(L"RIGHT", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r = { 220, 90, 310, 110 };
	renderMapSurface(m_cube->m_frontSurface, 220, 0);
	drawtext(L"FRONT", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r = { 220, 200, 310, 220 };
	renderMapSurface(m_cube->m_backSurface, 220, 110);
	drawtext(L"BACK", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void CubeRenderer::renderMapSurface(const std::shared_ptr<CubeSurface> surface, int cubeLeft, int cubeTop, int surfaceSize, int spacing)
{
	const int blockSize = (surfaceSize / m_cube->cubeSize) - spacing;
	for (int i = 0; i < m_cube->cubeSize; ++i) {
		for (int j = 0; j < m_cube->cubeSize; ++j) {
			int left = spacing * (j + 1) + j * blockSize + cubeLeft;
			int top = spacing * (i + 1) + i * blockSize + cubeTop;
			setfillcolor((COLORREF)(*surface)[i][j]);
			fillrectangle(left, top, left + blockSize, top + blockSize);
		}
	}
}

void CubeRenderer::renderMainView()
{
	renderLeftView();
	renderRightView();
}

void CubeRenderer::renderLeftView()
{
	//fillrectangle(360, 150, 760, 550); //大盒子
	//fillrectangle(360, 300, 600, 550); //小盒子
	line(520, 150, 760, 150);   //直线，小盒子的边
	line(360, 300, 520, 150);   //斜线
	line(600, 300, 760, 150);
	line(600, 550, 760, 400); //底下的斜线
	line(760, 400, 760, 150);
}

void CubeRenderer::renderRightView()
{
}

void CubeRenderer::renderText()
{
	drawtext(L"输入q为退出，r为重置，数字键盘键为操控，默认操控上下转动，按空格键切换成左右", new RECT{ 0, 240, 320, 340 },
		DT_CENTER | DT_VCENTER | DT_WORDBREAK);
}

void CubeRenderer::update()
{
	renderMap();
	// renderMainView();
}

CubeRenderer::~CubeRenderer()
{
	closegraph();
}