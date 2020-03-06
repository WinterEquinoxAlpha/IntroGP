#include "IntroGP_FW/Display.h"
using namespace std;
void drawGrid(int width, int height, char content[], bool drawLines, bool drawTopRow, bool drawSideRow)
{
	if (drawTopRow)
	{
		for (int i = 0; i < width; i++)
		{
			cout << " " << i;
		}
		cout << endl;
	}
	for (int y = 0; y < height; y++)
	{
		if (drawSideRow)
		{
			cout << (char)('A' + y) << " ";
		}
		for (int x = 0; x < width; x++)
		{
			cout << content[(x * width) + y] << " ";
			if (drawLines && x < width - 1) cout << "|";
		}
		cout << endl;
		if (drawLines && y < height - 1)
		{
			for (int i = 0; i < (width * 2) - 1; i++)
			{
				cout << (i % 2 == 0 ? "-" : "+");
			}
			cout << endl;
		}
	}
}