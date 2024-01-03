#pragma once
#include "Mouse.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
/*-----------------------------------------------------------------------------------*/
class MouseGame
{
private:
	Sprite pictureOfMouse;
	Texture textureOfMouse;
	std::string locationIMG;
	Vector2i locationMouse;
public:
	MouseGame();
	~MouseGame();
	void SetLocationIMG(std::string link);
	void SetIMG();
	void GetPositionMouse(RenderWindow& wd);
	void DrawMouse(RenderWindow& wd);
	bool CheckGetGBM(Sprite img);
	bool CheckGetGBM(Vector2i temp);
	bool CheckGetGBM(Vector2i temp, int x, int y);

	Vector2f GetPositionVector();
	void ChangeIMG(std::string link);
};