#include "board.hpp"
Board::Board(std::string fn)
{

	this->scorchedEarth = false;
	std::ifstream ifs(fn,std::ifstream::in); //input file stream for parsing through passed filename	
	this->validFile = ifs.is_open();
	 findRowsAndColumns(ifs);
	this-> cellArray = new Cell*[this->row];
	for(int i=0; i<this->row; ++i)
	       this->cellArray[i] = new Cell[this->col];	
	buryMines(ifs);
}

bool Board::getValidFile()
{
	return this->validFile;
}
void Board::findRowsAndColumns(std::ifstream &ifs)
{
	this->row = 0;
	this->col = 0;
	char ch=ifs.get();
	while (ifs.good()) //find the number of rows and columns 
	{
		if(ch == ' ' or ch == '*')
			++this->col;
		if(ch=='\n')
		{
			++this->row;
			this->col=0;
		}
		ch = ifs.get();
	}
	if(ifs.eof()) //treat the end of file bit being set as another row.
		++this->row;	
	ifs.clear();
	ifs.seekg(0,std::ios::beg);
}







bool Board::isCell(int x, int y)
{
	  return (y >= 0) && (y < this->row) && (x >= 0) && (x < this->col); 
}







void Board::buryMines(std::ifstream &ifs)
{

	int r=0;
	int c=0;
	char ch=ifs.get();
	while (ifs.good()) //instantiate mines at positions
	{
		
		if(ch == '*')
		{
			//std::cout << "MINE BEING PLANTED AT: " << r << "," <<c <<std::endl;
			this->cellArray[r][c] = Cell(true);
			//plant the mines
			for(int i=-1; i<2;++i)
				for(int j=-1; j<2;++j)
				{
				if(isCell(r-i,c-j) == true)
					this->cellArray[r-i][c-j].SetAdjacentMineCount(this->cellArray[r-i][c-j].GetAdjacentMineCount()+1);
				}
			

				
		}
		
		if(ch == ' ' or ch == '*')
			++c;
		if(ch=='\n')
		{
			++r;
			c=0;
		}
		ch = ifs.get();
	}

	if(ifs.eof()) //treat the end of file bit being set as another row.
		++r;
		
	ifs.clear();
	ifs.seekg(0,std::ios::beg);
}


bool Board::clickCell(int x, int y)
{
	return this->cellArray[x][y].Click();
}

bool Board::flag(int x, int y)
{
	bool val;
	if(isCell(x,y))
	{
		val=true;
		this->cellArray[x][y].ToggleFlag();
	}
	return val;
}

void Board::clearBoard()
{

	//clear the board
	for(int i=0; i<this->row;++i)
		for(int j=0; j<this->col;++j)
		{
			if(cellArray[i][j].getFlag())
				cellArray[i][j].ToggleFlag();
			if(cellArray[i][j].getClicked())
				cellArray[i][j].Click();
		}
}
void Board::unearthMines()
{
	for(int i=0; i<this->row;++i)
		for(int j=0; j<this->col;++j)
		{
			if (cellArray[i][j].IsMine() and cellArray[i][j].getFlag())
			{
				cellArray[i][j].ToggleFlag();
				cellArray[i][j].Click();
			}
			if(cellArray[i][j].IsMine() and !cellArray[i][j].getClicked())
				cellArray[i][j].Click();
		}
}


bool Board::checkGameOver()
{
	bool val=false;

	if(this->scorchedEarth == false)
	{
	int numberOfNonMinescovered=0;
	for(int i=0; i<this->row;++i)
		for(int j=0; j<this->col;++j)
			if(!this->cellArray[i][j].IsMine() and !this->cellArray[i][j].getClicked())
			++numberOfNonMinescovered;	
	
	if(numberOfNonMinescovered == 0)
		val = true;
	}
	else if(scorchedEarth == true)
		val = true;
	return val;
}

//recursive function
bool Board::clearNearbyCells(int x, int y)
{
	bool val = false;
	if(isCell(x,y))
	{
		val = true;
		if(this->cellArray[x][y].IsMine() and !this->cellArray[x][y].getFlag())
		{
			unearthMines(); // :)
			this->scorchedEarth = true;
		}
		else if( !this->cellArray[x][y].getClicked() and this->cellArray[x][y].GetAdjacentMineCount()==0)
		{
			this->cellArray[x][y].Click();
			for(int i=-1; i<2; ++i)
				for(int j=-1; j<2; ++j)
					clearNearbyCells(x+i,y+j);
		}
		else if( !this->cellArray[x][y].getClicked() and this->cellArray[x][y].GetAdjacentMineCount()>0)
			this->cellArray[x][y].Click();
		else
			val=false;
	}
	return val;
}


Cell Board::getCell(int row, int col) const
{
        return this->cellArray[row][col];
}





Board::~Board()
{
	for (int i=0; i<this->row; ++i)
		delete[] cellArray[i];
	delete[] cellArray;
}


std::ostream& operator << (std::ostream & ostr, const Board &b)
{
	std::string uglyline;
	ostr << "    ";
	for(int i=0; i<b.col;++i)
		ostr << "  "<<i<<" ";
	ostr << "\n";
	for(int i=0; i<b.row; ++i)
	{
		ostr<<"    "; 
		for(int j=0; j<b.col; ++j)
			ostr<<"+---";
		ostr<<"+\n";
		ostr<<"  "<<i<<" ";
		for(int j=0; j<b.col; ++j)
		{
			
			ostr<<"| "<<b.getCell(i,j)<<" ";
		}
		ostr<<"|\n";

	}

	ostr<<"    "; 
	for(int j=0; j<b.col; ++j)
		ostr<<"+---";

	ostr<<"+\n";
	return ostr;
} //MY BRAIN, (I'll clean this later)


