#include "Piece.h"
/*-----------------------------------------------------------------------------------*/
void Piece::AddPossibleMoveLocation(Vector2i temp)
{
	possibleMove.push_back(temp);
}
/*-----------------------------------------------------------------------------------*/
PieceBoard Piece::CheckPossibleMoveLocation(int c, int r, PieceBoard b[][8], ColorPiece color)
{
	if (color == ColorPiece::Black)
	{
		if (b[c][r] == PieceBoard::EmptySquare) return PieceBoard::EmptySquare;
		else if (b[c][r] == PieceBoard::WhiteSquare) return PieceBoard::EnemySquare;
		else return PieceBoard::SameSquare;
	}
	else
	{
		if (b[c][r] == PieceBoard::EmptySquare) return PieceBoard::EmptySquare;
		else if (b[c][r] == PieceBoard::BlackSquare) return PieceBoard::EnemySquare;
		else return PieceBoard::SameSquare;
	}
}
/*-----------------------------------------------------------------------------------*/
void Piece::ClearPossibleMoveLocation()
{
	possibleMove.clear();
}
/*-----------------------------------------------------------------------------------*/
void Piece::CheckAndAddPossibleMoveLocation(int c, int r, PieceBoard b[][8], ColorPiece color)
{
	if (b[c][r] == PieceBoard::EmptySquare || b[c][r] == PieceBoard::EnemySquare)
		AddPossibleMoveLocation(Vector2i(c, r));
}
/*-----------------------------------------------------------------------------------*/
int Piece::GetSizePossibleMoveLocation()
{
	return possibleMove.size();
}
/*-----------------------------------------------------------------------------------*/
Vector2i Piece::GetPossibleMoveOfNumber(int i)
{
	return possibleMove[i];
}
/*-----------------------------------------------------------------------------------*/
int Piece::CheckInVectorMoveLocation(MouseGame* m)
{
	if (GetSizePossibleMoveLocation() == 0) return -1;
	for (int i = 0; i < GetSizePossibleMoveLocation(); i++)
	{
		if (m->CheckGetGBM(possibleMove[i])) return i;
	}
	return -1;
}
/*-----------------------------------------------------------------------------------*/
void Piece::SetEat()
{
	selectionErasePiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Piece::UnSetEat()
{
	selectionErasePiece = false;
}
/*-----------------------------------------------------------------------------------*/
bool Piece::CheckChangePiece()
{
	if (GetColorPiece() == ColorPiece::Black)
	{
		if (GetPlaceCurrent().GetRow() == sizeBoard)
			return true;
		else return false;
	}
	else
	{
		if (GetPlaceCurrent().GetRow() == 0)
			return true;
		else return false;
	}
}
/*-----------------------------------------------------------------------------------*/
void Piece::ChangeLocationFileTexture(std::string link)
{
	texturePiece.loadFromFile(link);
	spritePiece.setTexture(texturePiece);
}
/*-----------------------------------------------------------------------------------*/
/*Chess of the Board*/
/*-----------------------------------------------------------------------------------*/
void King::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/KingBlack.png");
	else texturePiece.loadFromFile("IMG/KingWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void King::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square King::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece King::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void King::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void King::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void King::GetPossibleMoveLocation(PieceBoard b[][8])
{
	for (int i = (placeCurrent.GetCol() - 1 >= 0 ? placeCurrent.GetCol() - 1 : 0); i <= (placeCurrent.GetCol() + 1 <= sizeBoard ? placeCurrent.GetCol() + 1 : sizeBoard); i++)
	{
		for (int j = (placeCurrent.GetRow() - 1 >= 0 ? placeCurrent.GetRow() - 1 : 0); j <= (placeCurrent.GetRow() + 1 <= sizeBoard ? placeCurrent.GetRow() + 1 : sizeBoard); j++)
		{
			if (i == placeCurrent.GetCol() && j == placeCurrent.GetRow()) continue;
			CheckAndAddPossibleMoveLocation(i, j, b, pieceColor);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void King::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/
bool King::GetFirstMove()
{
	return firstMove;
}
/*-----------------------------------------------------------------------------------*/
void King::SetFirstMove()
{
	firstMove = true;
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
void Queen::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/QueenBlack.png");
	else texturePiece.loadFromFile("IMG/QueenWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void Queen::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square Queen::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece Queen::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void Queen::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Queen::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void Queen::GetPossibleMoveLocation(PieceBoard b[][8])
{
	// x - 1
	for (int i = placeCurrent.GetCol() - 1; i >= 0; i--)
	{
		if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
			break;
		}
		else if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
		else break;
	}
	// x + 1
	for (int i = placeCurrent.GetCol() + 1; i <= sizeBoard; i++)
	{
		if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
			break;
		}
		else if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
		else break;
	}
	// y - 1
	for (int j = placeCurrent.GetRow() - 1; j >= 0; j--)
	{
		if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
			break;
		}
		else if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
		else break;
	}
	// y + 1
	for (int j = placeCurrent.GetRow() + 1; j <= sizeBoard; j++)
	{
		if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
			break;
		}
		else if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
		else break;
	}
	// x - 1, y - 1
	for (int i = placeCurrent.GetCol() - 1, j = placeCurrent.GetRow() - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x + 1, y + 1
	for (int i = placeCurrent.GetCol() + 1, j = placeCurrent.GetRow() + 1; i <= sizeBoard && j <= sizeBoard; i++, j++)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x - 1, y + 1
	for (int i = placeCurrent.GetCol() - 1, j = placeCurrent.GetRow() + 1; i >= 0 && j <= sizeBoard; i--, j++)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x + 1, y - 1
	for (int i = placeCurrent.GetCol() + 1, j = placeCurrent.GetRow() - 1; i <= sizeBoard && j >= 0; i++, j--)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
}
/*-----------------------------------------------------------------------------------*/
void Queen::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
void Rook::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/RookBlack.png");
	else texturePiece.loadFromFile("IMG/RookWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void Rook::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square Rook::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece Rook::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void Rook::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Rook::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void Rook::GetPossibleMoveLocation(PieceBoard b[][8])
{
	// x - 1
	for (int i = placeCurrent.GetCol() - 1; i >= 0; i--)
	{
		if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
			break;
		}
		else if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
		else break;
	}
	// x + 1
	for (int i = placeCurrent.GetCol() + 1; i <= sizeBoard; i++)
	{
		if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
			break;
		}
		else if (CheckPossibleMoveLocation(i, placeCurrent.GetRow(), b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, placeCurrent.GetRow()));
		else break;
	}
	// y - 1
	for (int j = placeCurrent.GetRow() - 1; j >= 0; j--)
	{
		if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
			break;
		}
		else if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
		else break;
	}
	// y + 1
	for (int j = placeCurrent.GetRow() + 1; j <= sizeBoard; j++)
	{
		if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
			break;
		}
		else if (CheckPossibleMoveLocation(placeCurrent.GetCol(), j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(placeCurrent.GetCol(), j));
		else break;
	}
}
/*-----------------------------------------------------------------------------------*/
void Rook::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/
bool Rook::GetFirstMove()
{
	return firstMove;
}
/*-----------------------------------------------------------------------------------*/
void Rook::SetFirstMove()
{
	firstMove = true;
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
void Knight::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/KnightBlack.png");
	else texturePiece.loadFromFile("IMG/KnightWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void Knight::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square Knight::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece Knight::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void Knight::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Knight::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void Knight::GetPossibleMoveLocation(PieceBoard b[][8])
{
	Vector2i temp(placeCurrent.GetCol(), placeCurrent.GetRow());
	// x - 2, y - 1
	if (temp.x - 2 >= 0 && temp.y - 1 >= 0) CheckAndAddPossibleMoveLocation(temp.x - 2, temp.y - 1, b, pieceColor);
	// x - 1, y - 2
	if (temp.x - 1 >= 0 && temp.y - 2 >= 0) CheckAndAddPossibleMoveLocation(temp.x - 1, temp.y - 2, b, pieceColor);
	// x + 1, y - 2
	if (temp.x + 1 <= sizeBoard && temp.y - 2 >= 0) CheckAndAddPossibleMoveLocation(temp.x + 1, temp.y + 2, b, pieceColor);
	// x + 2, y - 1
	if (temp.x + 2 <= sizeBoard && temp.y - 1 >= 0) CheckAndAddPossibleMoveLocation(temp.x + 2, temp.y - 1, b, pieceColor);
	// x + 2, y + 1
	if (temp.x + 2 <= sizeBoard && temp.y + 1 <= sizeBoard) CheckAndAddPossibleMoveLocation(temp.x + 2, temp.y + 1, b, pieceColor);
	// x + 1, y + 2
	if (temp.x + 1 <= sizeBoard && temp.y + 2 <= sizeBoard) CheckAndAddPossibleMoveLocation(temp.x + 1, temp.y + 2, b, pieceColor);
	// x - 1, y + 2
	if (temp.x - 1 >= 0 && temp.y + 2 <= sizeBoard) CheckAndAddPossibleMoveLocation(temp.x - 1, temp.y + 2, b, pieceColor);
	// x - 2, y + 1
	if (temp.x - 2 >= 0 && temp.y + 1 <= sizeBoard) CheckAndAddPossibleMoveLocation(temp.x - 2, temp.y + 1, b, pieceColor);
}
/*-----------------------------------------------------------------------------------*/
void Knight::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
void Pawn::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/KingBlack.png");
	else texturePiece.loadFromFile("IMG/KingWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void Pawn::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square Pawn::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece Pawn::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void Pawn::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Pawn::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void Pawn::GetPossibleMoveLocation(PieceBoard b[][8])
{
	for (int i = (placeCurrent.GetCol() - 1 >= 0 ? placeCurrent.GetCol() - 1 : 0); i <= (placeCurrent.GetCol() + 1 <= sizeBoard ? placeCurrent.GetCol() + 1 : sizeBoard); i++)
	{
		for (int j = (placeCurrent.GetRow() - 1 >= 0 ? placeCurrent.GetRow() - 1 : 0); j <= (placeCurrent.GetRow() + 1 <= sizeBoard ? placeCurrent.GetRow() + 1 : sizeBoard); j++)
		{
			if (i == placeCurrent.GetCol() && j == placeCurrent.GetRow()) continue;
			CheckAndAddPossibleMoveLocation(i, j, b, pieceColor);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void Pawn::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/
int Pawn::GetMove()
{
	return step;
}
/*-----------------------------------------------------------------------------------*/
void Pawn::AddMove()
{
	step++;
}
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
void Bishop::SetIMG()
{
	if (GetColorPiece() == ColorPiece::Black) texturePiece.loadFromFile("IMG/QueenBlack.png");
	else texturePiece.loadFromFile("IMG/QueenWhite.png");
}
/*-----------------------------------------------------------------------------------*/
void Bishop::SetPosition()
{
	spritePiece.setPosition(landMark + placeCurrent.GetCol() * distancePiece, landMark + placeCurrent.GetCol() * distancePiece);
}
/*-----------------------------------------------------------------------------------*/
Square Bishop::GetPlaceCurrent()
{
	return placeCurrent;
}
/*-----------------------------------------------------------------------------------*/
ColorPiece Bishop::GetColorPiece()
{
	return pieceColor;
}
/*-----------------------------------------------------------------------------------*/
void Bishop::SetSelection()
{
	selectionPiece = true;
}
/*-----------------------------------------------------------------------------------*/
void Bishop::CancelSelection()
{
	selectionPiece = false;
}
/*-----------------------------------------------------------------------------------*/
void Bishop::GetPossibleMoveLocation(PieceBoard b[][8])
{
	// x - 1, y - 1
	for (int i = placeCurrent.GetCol() - 1, j = placeCurrent.GetRow() - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x + 1, y + 1
	for (int i = placeCurrent.GetCol() + 1, j = placeCurrent.GetRow() + 1; i <= sizeBoard && j <= sizeBoard; i++, j++)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x - 1, y + 1
	for (int i = placeCurrent.GetCol() - 1, j = placeCurrent.GetRow() + 1; i >= 0 && j <= sizeBoard; i--, j++)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
	// x + 1, y - 1
	for (int i = placeCurrent.GetCol() + 1, j = placeCurrent.GetRow() - 1; i <= sizeBoard && j >= 0; i++, j--)
	{
		if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EnemySquare)
		{
			AddPossibleMoveLocation(Vector2i(i, j));
			break;
		}
		else if (CheckPossibleMoveLocation(i, j, b, pieceColor) == PieceBoard::EmptySquare) AddPossibleMoveLocation(Vector2i(i, j));
		else break;
	}
}
/*-----------------------------------------------------------------------------------*/
void Bishop::MoveNewPlace(int c, int r)
{
	placeCurrent.ChangeSquare(c, r);
}
/*-----------------------------------------------------------------------------------*/