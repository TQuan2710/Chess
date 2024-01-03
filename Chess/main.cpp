#include <windows.h>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "BoardGame.h"
#include "Mouse.h"
#include "Game.h"
using namespace sf;
using namespace std;
void TurnOffConsole()
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
}
int main()
{
	ShowCursor(false);
	TurnOffConsole();
	Game g;
	while (g.GetStateGame() != StateMenu::EXIT_GAME)
	{
		g.IntGame();
		g.HandleInput();
	}
	return 0;
}