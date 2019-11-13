#ifndef BOARD_HPP
#define BOARD_HPP
#include <iostream>
#include <sstream>
#include "cell.hpp"
#include <fstream>


class Board 
{
	private:
		int row;
		int col;
		Cell** cellArray;
		bool validFile;
		bool scorchedEarth;
	public:
		Board(std::string fn);
		bool getValidFile();
		Cell getCell(int row, int col) const;
		void findRowsAndColumns( std::ifstream &ifs);
		void buryMines(std::ifstream &ifs);
		bool clickCell(int x, int y);
		bool checkGameOver();	
		bool clearNearbyCells(int x, int y);
		void unearthMines();
		void clearBoard();
		bool isCell(int x, int y);
		bool flag(int x, int y);
		~Board();
		friend std::ostream& operator << (std::ostream& ostr, const Board &b);
};
#endif
