#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
using namespace sf;
/*-----------------------------------------------------------------------------------*/
class PieceSet
{
private:
	ColorPiece pieceSetColor;
	Piece* kingChess;
public:
	bool losePiece;
	std::vector<Piece*> haveEatPieces;
	std::vector<Piece*> pieces;
	PieceSet();
	~PieceSet();
	void CreatePiece(ColorPiece p);
	int GetSizeOfPieces();
	void UnSelectionPiece();
	void ErasePiece();
	void ErasePieceAtLocation(int pos);
	void ChangePawnPiece(Piece* p, std::string typePiece);
	void UnSelectionEat();
	Piece* SelectionPiece(int c, int r);
	int SearchPieceInVector(Piece* p);
	bool EnterWall(Piece* p, PieceBoard b[][8]);
	ColorPiece GetColorSet();
	void CheckMateGame();
	Vector2i GetPossitionOfKing();
};