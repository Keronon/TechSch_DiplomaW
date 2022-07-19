#include"stdafx.h"
#include"Game.h"
#include<Windows.h>

int main()
{
	HWND console = GetConsoleWindow();
	//ShowWindow(console, SW_HIDE);

	Game game;

	game.run();

	//system("pause");
	return 0;
}
