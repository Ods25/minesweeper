#include "cell.hpp"

const std::string Cell::FLAG = "F";
const std::string Cell::MINE = "*";
const std::string Cell::NO_ADJACENT_MINES = "▢";
Cell::Cell(bool mine)
{
	this->mine = mine;
	this->flagBool = false;
	this-> clicked = false;
	this->mineCount =0;
}
bool Cell::IsMine()
{
	return this->mine;
}
bool Cell::Click()
{
	if(!this->flagBool)
	{
		this->clicked = !this->clicked;
	}
	return this->clicked;
}
bool Cell::getClicked()
{
	return this->clicked;
}
void Cell::ToggleFlag()
{
	if(!this->clicked)
		this->flagBool = !this->flagBool;
}
bool Cell::getFlag()
{
	return this->flagBool;
}
void Cell::SetAdjacentMineCount(int mC)
{
	this->mineCount = mC;
}
int Cell::GetAdjacentMineCount()
{
	return this->mineCount;
}
std::ostream& operator << (std::ostream & ostr, const Cell &c)
{

	if(c.clicked and c.mine)
		ostr << c.MINE; //if clicked and a mine, then youre dead. Clicked cannot happen if flag is set. 
	else if (c.clicked and !c.mine and c.mineCount==0)
		ostr << c.NO_ADJACENT_MINES; //if clicked and not a mine and adjacent mines is 0, then blank slate. However, if flag then clicked cannot happen.
	else if (c.clicked and !c.mine and c.mineCount>0) //if clicked and not a mine and adjacent mines >0, then put number However, if flag then clicked cannot happen/
		ostr << c.mineCount;
	else if (c.flagBool) 
		ostr << c.FLAG; //if flag is set, set a flag
	else
		ostr << " "; //else, the cell is not clicked, thus it is blank
	return ostr;
}
