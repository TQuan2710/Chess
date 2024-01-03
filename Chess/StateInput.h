#pragma once
#include "Window.h"
/*-----------------------------------------------------------------------------------*/
enum class TypeInput
{
	LEFT_MOUSE, RIGHT_MOUSE, WAIT
};
/*-----------------------------------------------------------------------------------*/
class StateInputGame
{
private:
	Event m_event;
	WindowGame* m_window;
public:
	TypeInput typeInputMouse;
	void SetWindow(WindowGame* wd);
	void CheckState();
	Event GetEven();
	void CheckState(Sprite &s);
};