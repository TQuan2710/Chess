#include "StateInput.h"
/*-----------------------------------------------------------------------------------*/
void StateInputGame::SetWindow(WindowGame* wd)
{
	m_window = wd;
	typeInputMouse = TypeInput::WAIT;
}
/*-----------------------------------------------------------------------------------*/
void StateInputGame::CheckState()
{
	while (m_window->GetWindowGame()->pollEvent(m_event))
	{

		if (m_event.type == Event::Closed)
		{
			m_window->Destroy();
		}
		typeInputMouse = TypeInput::WAIT;
		if (m_event.type == Event::MouseButtonPressed)
		{
			if (m_event.key.code == Mouse::Left)
			{
				typeInputMouse = TypeInput::LEFT_MOUSE;
			}
			else if (m_event.key.code == Mouse::Right)
			{
				typeInputMouse = TypeInput::RIGHT_MOUSE;
			}
		}

	}
}
/*-----------------------------------------------------------------------------------*/
Event StateInputGame::GetEven()
{
	return m_event;
}
/*-----------------------------------------------------------------------------------*/
void StateInputGame::CheckState(Sprite& s)
{
	bool move = false;
	int x, y;
	while (m_window->GetWindowGame()->pollEvent(m_event))
	{
		typeInputMouse = TypeInput::WAIT;
		if (m_event.type == Event::MouseButtonPressed)
		{
			if (m_event.key.code == Mouse::Left)
			{
				if (s.getGlobalBounds().contains(Mouse::getPosition(*m_window->GetWindowGame()).x, Mouse::getPosition(*m_window->GetWindowGame()).y))
				{
					move = true;
					x = Mouse::getPosition(*m_window->GetWindowGame()).x - s.getPosition().x;
					y = Mouse::getPosition(*m_window->GetWindowGame()).y - s.getPosition().y;
				}
				else typeInputMouse = TypeInput::LEFT_MOUSE;
			}
		}
		if (m_event.type == Event::MouseButtonReleased)
		{
			if (m_event.key.code == Mouse::Left)
				move = false;
		}
	}
	if (move) s.setPosition(Mouse::getPosition(*m_window->GetWindowGame()).x - x, s.getPosition().y);
}
/*-----------------------------------------------------------------------------------*/