#include "ui.hpp"

UI::UI()
{
	this->fileIsValid = false;
	this->validMoveMade = true;
	this->gameover = false;
}

bool UI::IsGameOver()
{
	return this->gameover;
}



std::string UI::GetPrompt()
{
	if(!this->fileIsValid)
		return "Please enter a file name with the minefield information: " ;
	else if(this->validMoveMade) 
	{
		std::ostringstream os;	
		os << *this->b ;
		if(this->b->checkGameOver())
		{
			this->gameover = true;
			os<< "Game Over!";
		}
		else
			os << "Choose your next move(c or f) and cell, e.g. c 0 3 to click row zero column 3: ";
		return os.str();

	}	
	else 
	{
		return "Invalid move. Please enter your next move: ";
	}
}

bool UI::Move(char ch, int r, int c)
{
	this->validMoveMade = false;
	if(ch=='c' or ch=='C')
	{
		this->validMoveMade = this->b->clearNearbyCells(r,c);
	}
	else if(ch=='f' or ch=='F')
	{
		this->validMoveMade = this->b->flag(r,c);
	}
	return this->validMoveMade;
}

bool UI::SetFileName(std::string fn)
{
	if(this->b != nullptr)
	{
		this->b->~Board();
	}
	this->b = new Board(fn);
	this->fileIsValid = this->b->getValidFile();
	return this->fileIsValid;
}

UI::~UI()
{
	delete b;
}
