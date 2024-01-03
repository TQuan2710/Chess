#pragma once
#include "PieceSet.h"
#include "Window.h"
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
/*-----------------------------------------------------------------------------------*/
class BoardChess
{
private:
	Texture textureBoard;
	Sprite spriteBoard;
	Texture t_setBlack;
	Sprite s_setBlack;
	Texture t_setWhite;
	Sprite s_setWhite;
	PieceBoard colorOfBoard(int c, int r);
	Piece* selectionPieceMove;
	Piece* selectionPieceEat;
	Sprite s_possibleMove;
	Texture t_possibleMove;
	Vector2i posOfBoard;
public:
	PieceBoard board[8][8];
	BoardChess();
	~BoardChess();
	PieceSet* whitePieces;
	PieceSet* blackPieces;
	void CreateBoardChess();
	void UpdataBoardChess();
	PieceBoard GetPieceBoard(int c, int r);
	void SetImageBoard(std::string l, std::string b, std::string w, std::string s);
	void DrawBoard(WindowGame* wd);
	Vector2u GetSizeImageBoard();
	void DrawSelectionPiece(WindowGame* wd);
	void SetSelectionPiece(Piece* p);
	void SetEatPiece(Piece* p);
	void ShowPossibleMove(Piece* p, WindowGame* wd, bool check);
	Piece* GetSelectionPieceMove();
	Piece* GetSelectionPieceEat();
	void MovePieceToNewPlace(Piece* p, int c, int r);
	void DrawPieceEat(WindowGame* wd);
	ColorPiece PieceWin();
};