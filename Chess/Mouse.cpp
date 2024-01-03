#include "Mouse.h"

/*-----------------------------------------------------------------------------------*/
MouseGame::MouseGame()
{

}
/*-----------------------------------------------------------------------------------*/
MouseGame::~MouseGame()
{

}
/*-----------------------------------------------------------------------------------*/
void MouseGame::SetLocationIMG(std::string link)
{
	locationIMG = link;
}
/*-----------------------------------------------------------------------------------*/
void MouseGame::SetIMG()
{
	if (textureOfMouse.loadFromFile(locationIMG) == false) std::cout << "Loi mo file chuot\n";
	else pictureOfMouse.setTexture(textureOfMouse);
}
/*-----------------------------------------------------------------------------------*/
void MouseGame::GetPositionMouse(RenderWindow& wd)
{
	locationMouse = Mouse::getPosition(wd);
	pictureOfMouse.setPosition(locationMouse.x, locationMouse.y);
}
/*-----------------------------------------------------------------------------------*/
void MouseGame::DrawMouse(RenderWindow& wd)
{
	wd.draw(pictureOfMouse);
}
/*-----------------------------------------------------------------------------------*/
bool MouseGame::CheckGetGBM(Sprite img)
{
	return (img.getGlobalBounds().contains(locationMouse.x, locationMouse.y));
}
/*-----------------------------------------------------------------------------------*/
bool MouseGame::CheckGetGBM(Vector2i temp)
{
	return (locationMouse.x >= temp.x * 90 + 24 && locationMouse.x <= (temp.x + 1) * 90 + 24 && locationMouse.y >= temp.y * 90 + 24 && locationMouse.y <= (temp.y + 1) * 90 + 24);
}
/*-----------------------------------------------------------------------------------*/
bool MouseGame::CheckGetGBM(Vector2i temp, int x, int y)
{
	return (locationMouse.x >= temp.x && locationMouse.x <= temp.x + x && locationMouse.y >= temp.y && locationMouse.y <= temp.y + y);
}
/*-----------------------------------------------------------------------------------*/
Vector2f MouseGame::GetPositionVector()
{
	Vector2f temp;
	temp.x = locationMouse.x;
	temp.y = locationMouse.y;
	return temp;
}
/*-----------------------------------------------------------------------------------*/
void MouseGame::ChangeIMG(std::string link)
{
	SetLocationIMG(link);
	SetIMG();
}
/*-----------------------------------------------------------------------------------*/
