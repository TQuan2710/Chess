#pragma once
#include <SFML/Graphics.hpp>
#include "Mouse.h"
#include "Window.h"
#include "StateInput.h"
using namespace sf;
/*-----------------------------------------------------------------------------------*/
enum class StateMenu
{
	WAIT, PLAY_GAME, OPTION_GAME, EXIT_GAME
};
/*-----------------------------------------------------------------------------------*/
class MenuGame
{
private:
	MouseGame mouseMenu;
	StateMenu stateMenu;
	WindowGame m_window;
	StateInputGame stateInputWindow;
public:
	void Run();
	StateMenu InitiationMenu();
	void PlayMenu();
	void DragAndDrop(Sprite& s, bool& move, Vector2i pos)
	{
		int x = 0, y = 0;
		Event e;
		while (m_window.GetWindowGame()->pollEvent(e))
		{
			switch (e.type) {
			case Event::MouseButtonPressed:
				if (e.mouseButton.button == 0 && s.getGlobalBounds().contains(mouseMenu.GetPositionVector().x, mouseMenu.GetPositionVector().y) == true)
				{
					move = true;
					x = pos.x - s.getPosition().x;
					y = pos.y - s.getPosition().y;
				}
				break;
			case Event::MouseButtonReleased:
				if (e.mouseButton.button == 0) move = false;
				break;
			}
		}
		if (move) s.setPosition(pos.x - x, s.getPosition().y);
	}
};	