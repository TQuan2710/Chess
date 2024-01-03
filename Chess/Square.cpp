#include "Square.h"
/*-----------------------------------------------------------------------------------*/
Square::Square(int r, int c)
{
	col = r;
	row = c;
}
/*-----------------------------------------------------------------------------------*/
Square::~Square()
{

}
/*-----------------------------------------------------------------------------------*/
void Square::ChangeSquare(int r, int c)
{
	col = c;
	row = r;
}
int Square::GetCol()
{
	return col;
}
int Square::GetRow()
{
	return row;
}