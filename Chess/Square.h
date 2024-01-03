#pragma once
class Square
{
private:
	int row;
	int col;
public:
	Square()
	{
		row = 0;
		col = 0;
	}
	~Square();
	Square(int c, int r);
	void ChangeSquare(int c, int r);
	int GetRow();
	int GetCol();
};