#ifndef CELL_HPP
#define CELL_HPP
#include <sstream>
class Cell
{
	private:
		bool mine,flagBool,clicked;
		int mineCount;
	public:
		static const std::string MINE;
		static const std::string FLAG;
		static const std::string NO_ADJACENT_MINES;
		void ToggleFlag();
		bool getFlag();
		bool Click();
		bool getClicked();
		Cell(bool mine = false);
		bool IsMine();
		void SetAdjacentMineCount(int mC);
		int GetAdjacentMineCount();
		
		friend std::ostream& operator << (std::ostream& ostr, const Cell &c);
};





#endif
