#include "Window.h"

/*---------------------------------------------------------------------------------*/
WindowGame::WindowGame()
{
	fullScreen = false;
	endGame = false;
}
WindowGame::~WindowGame()
{
	Destroy();
}
void WindowGame::Destroy()
{
	window.close();
}
void WindowGame::Create()
{
	auto style = (fullScreen ? Style::Fullscreen : Style::Default);
	window.create(VideoMode(windowSize.x, windowSize.y), windowTitle, style);
}
void WindowGame::SetUp(const std::string& title, const Vector2u& size)
{
	windowTitle = title;
	windowSize = size;
	Create();
}
void WindowGame::BeginDraw()
{
	window.clear(Color::Black);
}
void WindowGame::EndDraw()
{
	window.display();
}
void WindowGame::Update()
{

}
bool WindowGame::CheckEnd()
{
	return endGame;
}
bool WindowGame::IsFullScreen()
{
	return fullScreen;
}
void WindowGame::Draw(Drawable& d)
{
	window.draw(d);
}
Vector2u WindowGame::GetWindowSize()
{
	return windowSize;
}
RenderWindow* WindowGame::GetWindowGame()
{
	return &window;
}