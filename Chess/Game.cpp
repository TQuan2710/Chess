#include "Game.h"

/*-----------------------------------------------------------------------------------*/
Game::Game()
{
	IntGame();
}
/*-----------------------------------------------------------------------------------*/

void Game::IntIconInGame()
{
	t_Undo.loadFromFile("IMG/undo.png");
	t_Indo.loadFromFile("IMG/indo.png");
	t_Option.loadFromFile("IMG/option.png");

	s_Undo.setTexture(t_Undo);
	s_Indo.setTexture(t_Indo);
	s_Option.setTexture(t_Option);

	s_Option.setPosition(900, 24);
	s_Undo.setPosition(900, 550);
	s_Indo.setPosition(900, 650);
}
/*-----------------------------------------------------------------------------------*/

void Game::IntGame()
{
	movesBlack = "";
	movesWhite = "";
	drawSpriteInGame = false;
	boardChess.SetImageBoard("IMG/Board.png", "IMG/SelectionPiece.png", "IMG/SelectionPiece.png", "IMG/Selection.png");
	boardChess.CreateBoardChess();
	mouseGame.SetLocationIMG("IMG/mouse.png");

	t_MenuGame.loadFromFile("images/chess_size1/menugame.png");
	s_MenuGame.setTexture(t_MenuGame);

	t_ChangePawnBlack.loadFromFile("images/chess_size1/changepawnblack.png");
	t_ChangePawnWhite.loadFromFile("images/chess_size1/changepawnwhite.png");
	s_ChangePawnBlack.setTexture(t_ChangePawnBlack);
	s_ChangePawnWhite.setTexture(t_ChangePawnWhite);
	IntIconInGame();

	turnPlayer = TurnPlayer::P1;
	teamPlayer = ColorPiece::White;
	stateDrawIcon = TypeIcon::NoDraw;
	stateChooseIcon = TypeIcon::NoWait;
	stateGame = StateMenu::WAIT;
	changePawn = TypeIcon::NoChange;
	position = "";
	enterWall = false;
}
/*-----------------------------------------------------------------------------------*/

void Game::CreateGame()
{
	Image icon;
	icon.loadFromFile("IMG/icon.png");
	windowGame.GetWindowGame()->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Clock clock;
	double timer = 0, delay = 0.3;
	mouseGame.SetIMG();
	windowGame.GetWindowGame()->setFramerateLimit(60);
	while (windowGame.CheckEnd())
	{
		float time = clock.getElapsedTime().asSeconds();
		eventInputGame.SetWindow(&windowGame);
		eventInputGame.CheckState();
		windowGame.BeginDraw();
		boardChess.DrawBoard(&windowGame);

		for (int i = 0; i < boardChess.blackPieces->GetSizeOfPieces(); i++)
		{
			boardChess.blackPieces->pieces[i]->SetPosition();
			windowGame.Draw(boardChess.blackPieces->pieces[i]->spritePiece);

		}
		for (int i = 0; i < boardChess.whitePieces->GetSizeOfPieces(); i++)
		{
			boardChess.whitePieces->pieces[i]->SetPosition();
			windowGame.Draw(boardChess.whitePieces->pieces[i]->spritePiece);

		}
		if (stateChooseIcon == TypeIcon::NoWait)
		{
			SelectionPiece();
			if (drawSpriteInGame == true)
			{
				SelectionMovePlace();
				if (typeid(*boardChess.GetSelectionPieceMove()) == typeid(Pawn))
				{
					if (boardChess.GetSelectionPieceMove()->CheckChangePiece() == true)
					{
						changePawn = TypeIcon::Change;
					}
				}
				else if (typeid(*boardChess.GetSelectionPieceMove()) == typeid(King))
				{

					if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
					{
						if (boardChess.blackPieces->EnterWall(boardChess.GetSelectionPieceMove(), boardChess.board))
						{
							enterWall = true;
						}
					}
					else if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::White)
					{
						if (boardChess.whitePieces->EnterWall(boardChess.GetSelectionPieceMove(), boardChess.board))
						{
							enterWall = true;
						}
					}
				}
			}
		}

		if (changePawn == TypeIcon::Change)
		{
			stateChooseIcon = TypeIcon::Wait;
			UpgardePawn();
			if (mouseGame.CheckGetGBM(Vector2i(345, 365), 90, 90))
			{
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
					{
						boardChess.blackPieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Rook");
					}
					else
					{
						boardChess.whitePieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Rook");
					}
					changePawn = TypeIcon::NoChange;
				}

			}
			else if (mouseGame.CheckGetGBM(Vector2i(435, 365), 90, 90))
			{
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
					{
						boardChess.blackPieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Knight");
					}
					else
					{
						boardChess.whitePieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Knight");
					}
					changePawn = TypeIcon::NoChange;
				}

			}
			else if (mouseGame.CheckGetGBM(Vector2i(525, 365), 90, 90))
			{
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
					{
						boardChess.blackPieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Queen");
					}
					else
					{
						boardChess.whitePieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Queen");
					}
					changePawn = TypeIcon::NoChange;
				}

			}
			else if (mouseGame.CheckGetGBM(Vector2i(615, 365), 90, 90))
			{
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
					{
						boardChess.blackPieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Bishop");
					}
					else
					{
						boardChess.whitePieces->ChangePawnPiece(boardChess.GetSelectionPieceMove(), "Bishop");
					}
					changePawn = TypeIcon::NoChange;
				}

			}
			stateChooseIcon = TypeIcon::NoWait;

		}
	}
}
/*-----------------------------------------------------------------------------------*/

void Game::HandleInput()
{
	StateMenu temp = stateMenu.InitiationMenu();
	if (temp == StateMenu::EXIT_GAME)
	{
		stateGame = StateMenu::EXIT_GAME;
	}
	else if (temp == StateMenu::PLAY_GAME)
	{
		stateGame = StateMenu::PLAY_GAME;
		CreateGame();
	}
	else if (temp == StateMenu::OPTION_GAME)
	{ }
}
/*-----------------------------------------------------------------------------------*/

void Game::SelectionPiece()
{
	if (turnPlayer == TurnPlayer::P2)
	{
		for (int i = 0; i < boardChess.blackPieces->GetSizeOfPieces(); i++)
		{
			if (mouseGame.CheckGetGBM(boardChess.blackPieces->pieces[i]->spritePiece))
			{
				boardChess.whitePieces->UnSelectionPiece();
				boardChess.blackPieces->UnSelectionPiece();
				boardChess.blackPieces->pieces[i]->SetSelection();
				boardChess.DrawSelectionPiece(&windowGame);
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					drawSpriteInGame = true;
					boardChess.SetSelectionPiece(boardChess.blackPieces->pieces[i]);
					boardChess.blackPieces->pieces[i]->ClearPossibleMoveLocation();
					boardChess.blackPieces->pieces[i]->GetPossibleMoveLocation(boardChess.board);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < boardChess.whitePieces->GetSizeOfPieces(); i++)
		{
			if (mouseGame.CheckGetGBM(boardChess.whitePieces->pieces[i]->spritePiece))
			{
				boardChess.blackPieces->UnSelectionPiece();
				boardChess.whitePieces->UnSelectionPiece();
				boardChess.whitePieces->pieces[i]->SetSelection();
				boardChess.DrawSelectionPiece(&windowGame);
				if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
				{
					drawSpriteInGame = true;
					boardChess.SetSelectionPiece(boardChess.whitePieces->pieces[i]);
					boardChess.whitePieces->pieces[i]->ClearPossibleMoveLocation();
					boardChess.whitePieces->pieces[i]->GetPossibleMoveLocation(boardChess.board);
				}
			}
		}
	}
	boardChess.ShowPossibleMove(boardChess.GetSelectionPieceMove(), &windowGame, drawSpriteInGame);
	if (drawSpriteInGame == true)
	{
		boardChess.DrawSelectionPiece(&windowGame);
	}
}
/*-----------------------------------------------------------------------------------*/

void Game::SelectionMovePlace()
{
	std::string result;
	int check = boardChess.GetSelectionPieceMove()->CheckInVectorMoveLocation(&mouseGame);
	if (check == -1)
	{
		if (enterWall == true)
		{
			if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
			{
				if (mouseGame.CheckGetGBM(Vector2i(0, 0)))
				{
					if (eventInputGame.typeInputMouse == TypeInput::RIGHT_MOUSE)
					{
						
						boardChess.GetSelectionPieceMove()->MoveNewPlace(2, 0);
						boardChess.blackPieces->pieces[boardChess.blackPieces->SearchPieceInVector(boardChess.blackPieces->SelectionPiece(0, 0))]->MoveNewPlace(3, 0);
						drawSpriteInGame = false;
						enterWall = false;
					}
				}
				else if (mouseGame.CheckGetGBM(Vector2i(7, 0)))
				{

					if (eventInputGame.typeInputMouse == TypeInput::RIGHT_MOUSE)
					{
						boardChess.GetSelectionPieceMove()->MoveNewPlace(6, 0);
						boardChess.blackPieces->pieces[boardChess.blackPieces->SearchPieceInVector(boardChess.blackPieces->SelectionPiece(7, 0))]->MoveNewPlace(5, 0);
						drawSpriteInGame = false;
						enterWall = false;
					}
				}
			}
			else if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::White)
			{
				if (mouseGame.CheckGetGBM(Vector2i(0, 7)))
				{
					if (eventInputGame.typeInputMouse == TypeInput::RIGHT_MOUSE)
					{
						boardChess.GetSelectionPieceMove()->MoveNewPlace(2, 7);
						boardChess.whitePieces->pieces[boardChess.whitePieces->SearchPieceInVector(boardChess.whitePieces->SelectionPiece(0, 7))]->MoveNewPlace(3, 7);
						drawSpriteInGame = false;
						enterWall = false;
					}
				}
				else if (mouseGame.CheckGetGBM(Vector2i(7, 7)))
				{
					if (eventInputGame.typeInputMouse == TypeInput::RIGHT_MOUSE)
					{
						boardChess.GetSelectionPieceMove()->MoveNewPlace(6, 7);
						boardChess.whitePieces->pieces[boardChess.whitePieces->SearchPieceInVector(boardChess.whitePieces->SelectionPiece(7, 7))]->MoveNewPlace(5, 7);
						drawSpriteInGame = false;
						enterWall = false;
					}
				}
			}
			if (enterWall == false)
			{
				if (turnPlayer == TurnPlayer::P1)
				{
					turnPlayer = TurnPlayer::P2;
				}
				else
				{
					turnPlayer = TurnPlayer::P1;
				}
			}

		}
		else if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE && enterWall == false)
		{

			drawSpriteInGame = false;
			if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::Black)
			{
				for (int i = 0; i < boardChess.whitePieces->GetSizeOfPieces(); i++)
				{
					if (boardChess.whitePieces->pieces[i]->GetPlaceCurrent().GetCol() == boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).x &&
						boardChess.whitePieces->pieces[i]->GetPlaceCurrent().GetRow() == boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).y)
					{
						boardChess.whitePieces->UnSelectionEat();
						boardChess.SetEatPiece(boardChess.whitePieces->pieces[i]);
						boardChess.whitePieces->ErasePiece();
					}
				}
			}
			if (boardChess.GetSelectionPieceMove()->GetColorPiece() == ColorPiece::White)
			{
				for (int i = 0; i < boardChess.blackPieces->GetSizeOfPieces(); i++)
				{
					if (boardChess.blackPieces->pieces[i]->GetPlaceCurrent().GetCol() == boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).x &&
						boardChess.blackPieces->pieces[i]->GetPlaceCurrent().GetRow() == boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).y)
					{
						boardChess.blackPieces->UnSelectionEat();
						boardChess.SetEatPiece(boardChess.blackPieces->pieces[i]);
						boardChess.blackPieces->ErasePiece();
					}
				}
			}

			AnimationPieceMove(boardChess.GetSelectionPieceMove(), Vector2f(boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).x * 90 + 24, boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).y * 90 + 24), Vector2f(boardChess.GetSelectionPieceMove()->GetPlaceCurrent().GetCol() * 90 + 24, boardChess.GetSelectionPieceMove()->GetPlaceCurrent().GetRow() * 90 + 24));
			boardChess.GetSelectionPieceMove()->MoveNewPlace(boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).x, boardChess.GetSelectionPieceMove()->GetPossibleMoveOfNumber(check).y);

			boardChess.GetSelectionPieceMove()->GetPossibleMoveLocation(boardChess.board);

			if (turnPlayer == TurnPlayer::P1)
			{
				turnPlayer = TurnPlayer::P2;
			}
			else
			{
				turnPlayer = TurnPlayer::P1;
			}
		}
	}
}
/*-----------------------------------------------------------------------------------*/

WindowGame* Game::GetWindowGame()
{
	return &windowGame;
}
/*-----------------------------------------------------------------------------------*/

std::string Game::GetStringMove(Vector2i p)
{
	std::string pos;
	pos += char(p.x + 97);
	pos += char(56 - p.y);
	return pos;
}
/*-----------------------------------------------------------------------------------*/

Vector2i Game::ToCoord(char a, char b)
{
	int x = int(a) - 97, y = 56 - int(b);
	return Vector2i(x, y);
}
/*-----------------------------------------------------------------------------------*/

void Game::DrawIconInGame()
{
	windowGame.Draw(s_Option);
	windowGame.Draw(s_Undo);
	windowGame.Draw(s_Indo);
}
/*-----------------------------------------------------------------------------------*/

TypeIcon Game::StateIcon()
{
	if (mouseGame.CheckGetGBM(s_Option))
	{
		if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
		{
			stateDrawIcon = TypeIcon::Draw;
			return TypeIcon::OptionIcon;
		}
	}
	else if (mouseGame.CheckGetGBM(s_Undo))
	{
		if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
		{
			return TypeIcon::UndoIcon;
		}
	}
	else if (mouseGame.CheckGetGBM(s_Indo))
	{
		if (eventInputGame.typeInputMouse == TypeInput::LEFT_MOUSE)
		{
			return TypeIcon::IndoIcon;
		}
	}
	return TypeIcon::Empty;
}
/*-----------------------------------------------------------------------------------*/
void Game::DrawTurnPlayer()
{
	Texture t_Turn;
	Sprite s_Turn;
	Texture t_TurnBlack;
	Sprite s_TurnBlack;
	Texture t_TurnWhite;
	Sprite s_TurnWhite;
	t_Turn.loadFromFile("IMG/turn.png");
	t_TurnBlack.loadFromFile("IMG/turnblack.png");
	t_TurnWhite.loadFromFile("IMG/turnwhite.png");
	s_Turn.setTexture(t_Turn);
	s_TurnBlack.setTexture(t_TurnBlack);
	s_TurnWhite.setTexture(t_TurnWhite);
	s_Turn.setPosition(880, 120);
	s_TurnBlack.setPosition(900, 200);
	s_TurnWhite.setPosition(900, 200);
	if (turnPlayer == TurnPlayer::P1)
	{
		windowGame.Draw(s_TurnWhite);
		windowGame.Draw(s_Turn);
	}
	else
	{
		windowGame.Draw(s_TurnBlack);
		windowGame.Draw(s_Turn);
	}
}
/*-----------------------------------------------------------------------------------*/

StateMenu Game::GetStateGame()
{
	return stateGame;
}
/*-----------------------------------------------------------------------------------*/

void Game::UpgardePawn()
{
	if(changePawn==TypeIcon::Change)
	{
		if(boardChess.GetSelectionPieceMove()->GetColorPiece()==ColorPiece::Black)
		{
			windowGame.Draw(s_ChangePawnBlack);
		}
		else
		{
			windowGame.Draw(s_ChangePawnWhite);
		}
	}
}
/*-----------------------------------------------------------------------------------*/

int Game::CheckMateGame()
{
	if (boardChess.PieceWin() == ColorPiece::Black)
	{
		std::cout << "Black Win\n";
		return 1;
	}
	else if (boardChess.PieceWin() == ColorPiece::White)
	{
		std::cout << "White Win\n";
		return 1;
	}
	else return 0;
}
/*-----------------------------------------------------------------------------------*/

void Game::AnimationPieceMove(Piece* p, Vector2f newPos, Vector2f oldPos)
{
	Vector2f spaceMove = newPos - oldPos;
	for (int i = 0; i < 30; i++)
	{
		p->spritePiece.move(spaceMove.x / 30, spaceMove.y / 30);
		boardChess.DrawBoard(&windowGame);
		for (int i = 0; i < boardChess.blackPieces->GetSizeOfPieces(); i++)
		{
			if (boardChess.blackPieces->SearchPieceInVector(p) == -1)
			{
				boardChess.blackPieces->pieces[i]->SetPosition();
				windowGame.Draw(boardChess.blackPieces->pieces[i]->spritePiece);
			}
			else
			{
				windowGame.Draw(boardChess.blackPieces->pieces[i]->spritePiece);
			}
		}
		for (int i = 0; i < boardChess.whitePieces->GetSizeOfPieces(); i++)
		{
			if (boardChess.whitePieces->SearchPieceInVector(p) == -1)
			{
				boardChess.whitePieces->pieces[i]->SetPosition();
				windowGame.Draw(boardChess.whitePieces->pieces[i]->spritePiece);
			}
			else
			{
				windowGame.Draw(boardChess.whitePieces->pieces[i]->spritePiece);
			}


		}
		windowGame.Draw(p->spritePiece);
		DrawIconInGame();
		DrawTurnPlayer();
		boardChess.DrawPieceEat(&windowGame);
		mouseGame.GetPositionMouse(*windowGame.GetWindowGame());
		mouseGame.DrawMouse(*windowGame.GetWindowGame());
		windowGame.EndDraw();
	}
}
/*-----------------------------------------------------------------------------------*/

void Game::DrawCheckMate()
{
}
/*-----------------------------------------------------------------------------------*/
