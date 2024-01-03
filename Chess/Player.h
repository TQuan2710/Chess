#pragma once
#include <string>
#include <iostream>
#include <fstream>
/*-----------------------------------------------------------------------------------*/
class Player
{
private:
	std::string name;
	int numberOfWin;
	int numberOfLose;
	std::string movePiece;
public:
	Player();
	~Player();
	Player(std::string s);
	std::string GetName();
	void addMovePiece(std::string move);
	void backMovePiece();
};