#include "BoardGame.h"
/*-----------------------------------------------------------------------------------*/
BoardChess::BoardChess()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 1) board[j][i] = PieceBoard::BlackSquare;
			else if (i == 6 || i == 7) board[j][i] = PieceBoard::WhiteSquare;
			else board[j][i] = PieceBoard::EmptySquare;
		}
	}
}
/*-----------------------------------------------------------------------------------*/
BoardChess::~BoardChess()
{
	whitePieces->~PieceSet();
	blackPieces->~PieceSet();
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::CreateBoardChess()
{
	BoardChess();
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::UpdataBoardChess()
{
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++)	board[j][i] = PieceBoard::EmptySquare;

	for (int i = 0; i < blackPieces->GetSizeOfPieces(); i++)
	{
		board[blackPieces->pieces[i]->GetPlaceCurrent().GetCol()][blackPieces->pieces[i]->GetPlaceCurrent().GetRow()] = PieceBoard::BlackSquare;
	}
	for (int i = 0; i < whitePieces->GetSizeOfPieces(); i++)
	{
		board[whitePieces->pieces[i]->GetPlaceCurrent().GetCol()][whitePieces->pieces[i]->GetPlaceCurrent().GetRow()] = PieceBoard::WhiteSquare;
	}
}
/*-----------------------------------------------------------------------------------*/
PieceBoard BoardChess::GetPieceBoard(int c, int r)
{
	return board[c][r];
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::SetImageBoard(std::string l, std::string b, std::string w, std::string s)
{
	textureBoard.loadFromFile(l);
	spriteBoard.setTexture(textureBoard);
	t_setBlack.loadFromFile(b);
	s_setBlack.setTexture(t_setBlack);
	t_setWhite.loadFromFile(w);
	s_setWhite.setTexture(t_setWhite);
	t_possibleMove.loadFromFile(s);
	s_possibleMove.setTexture(t_possibleMove);
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::DrawBoard(WindowGame* wd)
{
	spriteBoard.setPosition(landMark, landMark);
	wd->Draw(spriteBoard);
}
/*-----------------------------------------------------------------------------------*/
Vector2u BoardChess::GetSizeImageBoard()
{
	return textureBoard.getSize();
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::DrawSelectionPiece(WindowGame* wd)
{
	for (int i = 0; i < blackPieces->GetSizeOfPieces(); i++)
	{
		if (blackPieces->pieces[i]->selectionPiece == true)
		{
			if (colorOfBoard(blackPieces->pieces[i]->GetPlaceCurrent().GetCol(), blackPieces->pieces[i]->GetPlaceCurrent().GetRow()) == PieceBoard::WhiteSquare)
			{
				s_setWhite.setPosition(landMark + sizeimage * blackPieces->pieces[i]->GetPlaceCurrent().GetCol(), landMark + sizeimage * blackPieces->pieces[i]->GetPlaceCurrent().GetRow());
				wd->Draw(s_setWhite);
			}
			else
			{
				s_setBlack.setPosition(landMark + sizeimage * blackPieces->pieces[i]->GetPlaceCurrent().GetCol(), landMark + sizeimage * blackPieces->pieces[i]->GetPlaceCurrent().GetRow());
				wd->Draw(s_setBlack);
			}
		}
	}
	for (int i = 0; i < whitePieces->GetSizeOfPieces(); i++)
	{
		if (whitePieces->pieces[i]->selectionPiece == true)
		{
			if (colorOfBoard(whitePieces->pieces[i]->GetPlaceCurrent().GetCol(), whitePieces->pieces[i]->GetPlaceCurrent().GetRow()) == PieceBoard::WhiteSquare)
			{
				s_setWhite.setPosition(landMark + sizeimage * whitePieces->pieces[i]->GetPlaceCurrent().GetCol(), landMark + sizeimage * whitePieces->pieces[i]->GetPlaceCurrent().GetRow());
				wd->Draw(s_setWhite);
			}
			else
			{
				s_setBlack.setPosition(landMark + sizeimage * whitePieces->pieces[i]->GetPlaceCurrent().GetCol(), landMark + sizeimage * whitePieces->pieces[i]->GetPlaceCurrent().GetRow());
				wd->Draw(s_setBlack);
			}
		}
	}
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::SetSelectionPiece(Piece* p)
{
	selectionPieceMove = p;
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::SetEatPiece(Piece* p)
{
	selectionPieceEat = p;
	selectionPieceEat->SetEat();
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::ShowPossibleMove(Piece* p, WindowGame* wd, bool check)
{
	if (check)
	{
		for (int i = 0; i < p->GetSizePossibleMoveLocation(); i++)
		{
			s_possibleMove.setPosition(Vector2f(landMark + p->GetPossibleMoveOfNumber(i).x * sizeimage, landMark + p->GetPossibleMoveOfNumber(i).y * sizeimage));
			wd->Draw(s_possibleMove);
		}
	}
}
/*-----------------------------------------------------------------------------------*/
Piece* BoardChess::GetSelectionPieceMove()
{
	return selectionPieceMove;
}
/*-----------------------------------------------------------------------------------*/
Piece* BoardChess::GetSelectionPieceEat()
{
	return selectionPieceEat;
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::MovePieceToNewPlace(Piece* p, int c, int r)
{
	p->MoveNewPlace(c, r);
}
/*-----------------------------------------------------------------------------------*/
void BoardChess::DrawPieceEat(WindowGame* wd)
{
	for (int i = 0; i < blackPieces->haveEatPieces.size(); i++)
	{
		if (i >= 8)
		{
			blackPieces->haveEatPieces[i]->spritePiece.setPosition(775 + 45, 768 - 45 * (i - 8) - 45 - 24);
		}
		else
		{
			blackPieces->haveEatPieces[i]->spritePiece.setPosition(775, 768 - 45 * i - 45 - 24);
		}

		wd->Draw(blackPieces->haveEatPieces[i]->spritePiece);

	}
	for (int i = 0; i < whitePieces->haveEatPieces.size(); i++)
	{
		if (i >= 8)
		{
			whitePieces->haveEatPieces[i]->spritePiece.setPosition(775 + 45, (i - 8) * 45 + 24);
		}
		else
		{
			whitePieces->haveEatPieces[i]->spritePiece.setPosition(775, 45 * i + 24);
		}

		wd->Draw(whitePieces->haveEatPieces[i]->spritePiece);
	}
}
/*-----------------------------------------------------------------------------------*/
ColorPiece BoardChess::PieceWin()
{
	if (blackPieces->losePiece == true) return ColorPiece::White;
	else if(whitePieces->losePiece == true) return ColorPiece::Black;
}
/*-----------------------------------------------------------------------------------*/
PieceBoard BoardChess::colorOfBoard(int c, int r)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == r && j == c)
			{
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 != 0 && i % 2 != 0)) return PieceBoard::WhiteSquare;
				else return PieceBoard::BlackSquare;
			}
		}
	}
}