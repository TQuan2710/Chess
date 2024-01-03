#include "StateMenu.h"
/*-----------------------------------------------------------------------------------*/
void MenuGame::Run()
{
	mouseMenu.SetLocationIMG("IMG/mouse.png");
	mouseMenu.SetIMG();
}
StateMenu MenuGame::InitiationMenu()
{
	stateMenu = StateMenu::WAIT;
	stateInputWindow.SetWindow(&m_window);
	Run();
	Texture play, option, exit;
	play.loadFromFile("IMG/Home/play.png");
	option.loadFromFile("IMG/Home/option.png");
	exit.loadFromFile("IMG/Home/exit.png");
	
	Sprite spritePlay, spriteOption, spriteExit;
	while (m_window.CheckEnd())
	{
		mouseMenu.GetPositionMouse(*m_window.GetWindowGame());
		stateInputWindow.CheckState();
		m_window.BeginDraw();
		if (mouseMenu.CheckGetGBM(spritePlay))
		{
			if (stateInputWindow.typeInputMouse == TypeInput::LEFT_MOUSE)
			{
				stateInputWindow.typeInputMouse = TypeInput::WAIT;
				m_window.Destroy();
				return StateMenu::PLAY_GAME;
			}
		}
	}
	m_window.Destroy();
	return StateMenu::EXIT_GAME;
}
