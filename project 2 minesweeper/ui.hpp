#ifndef UI_HPP
#define UI_HPP
#include "board.hpp"
class UI
{
	private:
		bool fileIsValid;
		bool gameover;
		bool validMoveMade;
		int prompt;

		Board *b = nullptr;
	public:
		UI();
		bool IsGameOver();
		bool Move(char ch, int r, int c);
		std::string GetPrompt();
		bool SetFileName(std::string fn);
		~UI();	

};
#endif
