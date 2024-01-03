#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Mouse.h"
#include "Square.h"
using namespace sf;
const int distancePiece = 90;
const int sizeBoard = 7;
const int landMark = 24;
const int sizeimage = 90;
/*-----------------------------------------------------------------------------------*/
enum class	ColorPiece
{
	Black, White
};
/*-----------------------------------------------------------------------------------*/
enum class PieceBoard
{
	WhiteSquare, BlackSquare, EmptySquare, EnemySquare, SameSquare
};
/*-----------------------------------------------------------------------------------*/
class Piece
{
protected:
	Square placeCurrent;
	ColorPiece pieceColor;
	std::vector<Vector2i> possibleMove;
public:
	bool selectionPiece;
	bool selectionErasePiece;
	Sprite spritePiece;
	Texture texturePiece;
	Piece();
	Piece(int r, int c, ColorPiece color)
	{
		selectionPiece = false;
		selectionErasePiece = false;
		placeCurrent.ChangeSquare(c, r);
		pieceColor = color;
	}
	~Piece();
	virtual void SetIMG() = 0;
	virtual void SetPosition() = 0;
	virtual Square GetPlaceCurrent() = 0;
	virtual ColorPiece GetColorPiece() = 0;
	virtual void SetSelection() = 0;
	virtual void CancelSelection() = 0;
	virtual void GetPossibleMoveLocation(PieceBoard b[][8]) = 0;
	virtual void MoveNewPlace(int c, int r) = 0;
	void AddPossibleMoveLocation(Vector2i temp);
	PieceBoard CheckPossibleMoveLocation(int c, int r, PieceBoard b[][8], ColorPiece color);
	void ClearPossibleMoveLocation();
	void CheckAndAddPossibleMoveLocation(int c, int r, PieceBoard b[][8], ColorPiece color);
	int GetSizePossibleMoveLocation();
	Vector2i GetPossibleMoveOfNumber(int i);
	int CheckInVectorMoveLocation(MouseGame* m);
	void SetEat();
	void UnSetEat();
	bool CheckChangePiece();
	void ChangeLocationFileTexture(std::string link);
};
/*-----------------------------------------------------------------------------------*/
class King:public Piece
{
private:
	bool firstMove;
public:
	King(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
		firstMove = false;
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
	bool GetFirstMove();
	void SetFirstMove();
};
/*-----------------------------------------------------------------------------------*/
class Queen:public Piece
{
private:
public:
	Queen(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
};
/*-----------------------------------------------------------------------------------*/
class Rook:public Piece
{
private:
	bool firstMove;
public:
	Rook(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
		firstMove = false;
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
	bool GetFirstMove();
	void SetFirstMove();
};
/*-----------------------------------------------------------------------------------*/
class Knight:public Piece
{
private:
public:
	Knight(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
};
/*-----------------------------------------------------------------------------------*/
class Pawn:public Piece
{
private:
	int step;
public:
	Pawn(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
		step = 0;
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
	void AddMove();
	int GetMove();
};
/*-----------------------------------------------------------------------------------*/
class Bishop:public Piece
{
private:
public:
	Bishop(int c, int r, ColorPiece color) :Piece(c, r, color)
	{
		SetIMG();
	}
	void SetIMG();
	void SetPosition();
	Square GetPlaceCurrent();
	ColorPiece GetColorPiece();
	void SetSelection();
	void CancelSelection();
	void GetPossibleMoveLocation(PieceBoard b[][8]);
	void MoveNewPlace(int c, int r);
};
/*-----------------------------------------------------------------------------------*/