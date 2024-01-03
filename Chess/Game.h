#pragma once
#include "Window.h"
#include "Mouse.h"
#include "StateInput.h"
#include "StateMenu.h"
#include "BoardGame.h"
#include "Player.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
/*-----------------------------------------------------------------------------------*/
enum class TurnPlayer
{
	P1, P2
};
/*-----------------------------------------------------------------------------------*/
enum class TypeIcon
{
	Draw, NoDraw, OptionIcon, UndoIcon, IndoIcon, Wait, NoWait, Change, NoChange, Empty
};
/*-----------------------------------------------------------------------------------*/
class Game
{
private:
	std::string position;
	TypeIcon changePawn;
	bool enterWall;
	StateMenu stateGame;
	MenuGame stateMenu;
	TypeIcon stateChooseIcon;
	TypeIcon stateDrawIcon;
	TurnPlayer turnPlayer;
	TurnPlayer beginPlayer;
	MouseGame mouseGame;
	WindowGame windowGame;
	Player player1;
	Player player2;
	BoardChess boardChess;
	StateInputGame eventInputGame;
	bool drawSpriteInGame;
	ColorPiece teamPlayer;

	Texture t_Undo;
	Sprite s_Undo;
	Texture t_Indo;
	Sprite s_Indo;
	Texture t_Option;
	Sprite s_Option;
	Texture t_MenuGame;
	Sprite s_MenuGame;
	Texture t_ChangePawnBlack;
	Sprite s_ChangePawnBlack;
	Texture t_ChangePawnWhite;
	Sprite s_ChangePawnWhite;

	std::string movesBlack;
	std::string movesWhite;

public:
	Game();
	void IntIconInGame();
	void IntGame();
	void CreateGame();
	void HandleInput();
	void SelectionPiece();
	void SelectionMovePlace();
	WindowGame* GetWindowGame();
	std::string GetStringMove(Vector2i p);
	Vector2i ToCoord(char a, char b);

	void DrawIconInGame();
	TypeIcon StateIcon();
	void DrawTurnPlayer();
	StateMenu GetStateGame();
	void UpgardePawn();
	int CheckMateGame();
	void AnimationPieceMove(Piece* p, Vector2f newPos, Vector2f oldPos);
	void DrawCheckMate();
};