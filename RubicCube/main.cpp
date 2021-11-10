#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <conio.h>
#include "RubikCube.h"
#include "CubeRenderer.h"

using std::cout;
using std::endl;

int main()
{
	RubikCube r;
	CubeRenderer renderer(&r);
	//	EASYXMSG msg;
	char c;
	int mode = 1;
	/*	while (true)
		{
			while (!_kbhit()) Sleep(150);
			c = _getch();
			if (c == 'q') break;
			if (c == 'r') r.reset();
			if (c == ' ')
			{
				mode = !mode;
				continue;
			}
			if (mode)
			{
				if (c >= '7' && c <= '9') r.downToUp(c - '7');
				else if (c <= '3' && c >= '1') r.upToDown(c - '1');
			}
			else {
				switch (c)
				{
				case '7':
					r.rightToleft(0);
					break;
				case '4':
					r.rightToleft(1);
					break;
				case '1':
					r.rightToleft(2);
					break;
				case '9':
					r.leftToRight(0);
					break;
				case '6':
					r.leftToRight(1);
					break;
				case '3':
					r.leftToRight(2);
					break;
				default:
					break;
				}
			}
			renderer.update();
		}*/
	r.control_F();
	renderer.update();
	system("pause");
}