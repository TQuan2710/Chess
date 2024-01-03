#include "PieceSet.h"
/*-----------------------------------------------------------------------------------*/
PieceSet::PieceSet()
{
	losePiece = false;
}
/*-----------------------------------------------------------------------------------*/
PieceSet::~PieceSet()
{
	pieces.clear();
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::CreatePiece(ColorPiece p)
{
	pieces.clear();
	if (p == ColorPiece::Black)
	{
		// Pawn
		for (int i = 0; i < 8; i++) pieces.push_back(new Pawn(i, 1, ColorPiece::Black));
		// Rook
		pieces.push_back(new Rook(0, 0, ColorPiece::Black));
		pieces.push_back(new Rook(7, 0, ColorPiece::Black));
		// Knight
		pieces.push_back(new Knight(1, 0, ColorPiece::Black));
		pieces.push_back(new Knight(6, 0, ColorPiece::Black));
		// Bishop
		pieces.push_back(new Bishop(2, 0, ColorPiece::Black));
		pieces.push_back(new Bishop(5, 0, ColorPiece::Black));
		// Queen, King
		pieces.push_back(new Queen(3, 0, ColorPiece::Black));
		pieces.push_back(new King(4, 0, ColorPiece::Black));
		//
		Piece* temp;
		temp = new King(4, 0, ColorPiece::Black);
		kingChess = temp;
	}
	else
	{
		// Pawn
		for (int i = 0; i < 8; i++) pieces.push_back(new Pawn(i, 6, ColorPiece::White));
		// Rook
		pieces.push_back(new Rook(0, 7, ColorPiece::White));
		pieces.push_back(new Rook(7, 7, ColorPiece::White));
		// Knight
		pieces.push_back(new Knight(1, 7, ColorPiece::White));
		pieces.push_back(new Knight(6, 7, ColorPiece::White));
		// Bishop
		pieces.push_back(new Bishop(2, 7, ColorPiece::White));
		pieces.push_back(new Bishop(5, 7, ColorPiece::White));
		// Queen, King
		pieces.push_back(new Queen(3, 7, ColorPiece::White));
		pieces.push_back(new King(4, 7, ColorPiece::White));
		//
		Piece* temp;
		temp = new King(4, 7, ColorPiece::White);
		kingChess = temp;
	}
}
/*-----------------------------------------------------------------------------------*/
int PieceSet::GetSizeOfPieces()
{
	return pieces.size();
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::UnSelectionPiece()
{
	for (int i = 0; i < GetSizeOfPieces(); i++)
	{
		pieces[i]->CancelSelection();
	}
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::ErasePiece()
{
	for (int i = 0; i < GetSizeOfPieces(); i++)
	{
		if (pieces[i]->selectionErasePiece == true)
		{
			if (typeid(*pieces[i]) == typeid(King))
			{
				CheckMateGame();
			}
			haveEatPieces.push_back(pieces[i]);
			pieces.erase(pieces.begin() + i);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::ErasePieceAtLocation(int pos)
{
	pieces.erase(pieces.begin() + pos);
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::ChangePawnPiece(Piece* p, std::string typePiece)
{
	Piece *temp;
	Vector2i pos;
	int check = SearchPieceInVector(p);
	if (p->CheckChangePiece() == true)
	{
		if (check != -1)
		{
			pos = Vector2i(pieces[check]->GetPlaceCurrent().GetCol(), pieces[check]->GetPlaceCurrent().GetRow());
			if (typePiece == "Knight")
			{
				if (pieces[check]->GetColorPiece() == ColorPiece::Black) temp = new Knight(pos.x, pos.y, ColorPiece::Black);
				else temp = new Knight(pos.x, pos.y, ColorPiece::White);
			}
			else if (typePiece == "Bishop")
			{
				if (pieces[check]->GetColorPiece() == ColorPiece::Black) temp = new Bishop(pos.x, pos.y, ColorPiece::Black);
				else temp = new Bishop(pos.x, pos.y, ColorPiece::White);
			}
			else if (typePiece == "Rook")
			{
				if (pieces[check]->GetColorPiece() == ColorPiece::Black) temp = new Rook(pos.x, pos.y, ColorPiece::Black);
				else temp = new Rook(pos.x, pos.y, ColorPiece::White);
			}
			else if (typePiece == "Queen")
			{
				if (pieces[check]->GetColorPiece() == ColorPiece::Black) temp = new Queen(pos.x, pos.y, ColorPiece::Black);
				else temp = new Queen(pos.x, pos.y, ColorPiece::White);
			}
			ErasePieceAtLocation(check);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::UnSelectionEat()
{
	for (int i = 0; i < GetSizeOfPieces(); i++)
	{
		pieces[i]->UnSetEat();
	}
}
/*-----------------------------------------------------------------------------------*/
Piece* PieceSet::SelectionPiece(int c, int r)
{
	for (int i = 0; i < GetSizeOfPieces(); i++)
	{
		if (c == pieces[i]->GetPlaceCurrent().GetCol() && r == pieces[i]->GetPlaceCurrent().GetRow())
		{
			return pieces[i];
		}
	}
}
/*-----------------------------------------------------------------------------------*/
int PieceSet::SearchPieceInVector(Piece* p)
{
	for (int i = 0; i < GetSizeOfPieces(); i++)
	{
		if (p->GetPlaceCurrent().GetCol() == pieces[i]->GetPlaceCurrent().GetCol())
			if (p->GetPlaceCurrent().GetRow() == pieces[i]->GetPlaceCurrent().GetRow())
				return i;
	}
	return -1;
}
/*-----------------------------------------------------------------------------------*/
bool PieceSet::EnterWall(Piece* p, PieceBoard b[][8])
{
	int available = 0;
	int check = 0;
	if (p->GetColorPiece() == ColorPiece::Black)
	{
		if (typeid(*SelectionPiece(0, 0)) == typeid(Rook))
		{
			for (int i = 1; i <= 3; i++) if (b[i][0] == PieceBoard::EmptySquare) available++;
		}
		if (available == 3)
		{
			p->AddPossibleMoveLocation(Vector2i(0, 0));
			check++;
		}
		available = 0;
		if (typeid(*SelectionPiece(7, 0)) == typeid(Rook))
		{
			for (int i = 5; i <= 6; i++) if (b[i][0] == PieceBoard::EmptySquare) available++;
		}
		if (available == 2)
		{
			p->AddPossibleMoveLocation(Vector2i(7, 0));
			check++;
		}
	}
	else
	{
		if (p->GetPlaceCurrent().GetCol() == 4 && p->GetPlaceCurrent().GetRow() == 7)
		{
			if (typeid(*SelectionPiece(0, 7)) == typeid(Rook))
			{
				for (int i = 1; i <= 3; i++)
				{
					if (b[i][7] == PieceBoard::EmptySquare) available++;
				}
			}
			if (available == 3)
			{
				p->AddPossibleMoveLocation(Vector2i(0, 7));
				check++;
			}
			available = 0;
			if (typeid(*SelectionPiece(7, 7)) == typeid(Rook))
			{
				for (int i = 5; i <= 6; i++)
				{
					if (b[i][7] == PieceBoard::EmptySquare) available++;
				}
			}
			if (available == 2)
			{
				p->AddPossibleMoveLocation(Vector2i(7, 7));
				check++;
			}
		}
	}
	if (check > 0) return true;
	else return false;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece PieceSet::GetColorSet()
{
	return pieceSetColor;
}
/*-----------------------------------------------------------------------------------*/
void PieceSet::CheckMateGame()
{
	losePiece = true;
}
/*-----------------------------------------------------------------------------------*/
Vector2i PieceSet::GetPossitionOfKing()
{
	return Vector2i(kingChess->GetPlaceCurrent().GetCol(), kingChess->GetPlaceCurrent().GetRow());
}
/*-----------------------------------------------------------------------------------*/