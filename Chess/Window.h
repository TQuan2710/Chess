#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
using namespace sf;
class WindowGame
{
private:
	RenderWindow window;
	Vector2u windowSize;
	std::string windowTitle;
	bool fullScreen;
	bool endGame;
public:
	WindowGame();
	~WindowGame();
	void Destroy();
	void Create();
	void SetUp(const std::string& title, const Vector2u& size);
	void BeginDraw();
	void EndDraw();
	void Update();
	bool CheckEnd();
	bool IsFullScreen();
	void Draw(sf::Drawable& d);
	Vector2u GetWindowSize();
	RenderWindow* GetWindowGame();
};