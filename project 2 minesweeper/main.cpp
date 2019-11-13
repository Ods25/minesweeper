#include "ui.hpp"
#include <stdio.h>
void getInput(char &ch, int &r, int &c)
{
	
}




int main()
{
	UI ui;
	std::string prompt;
	bool val=false;	

	do
	{
		std::cout << ui.GetPrompt();
		std::string fn;
		std::cin >> fn;
		val = ui.SetFileName(fn);	
	}while(!val);




	do
	{

		
		std::cout << ui.GetPrompt();
		
		char ch;
		int r;
		int c;

		scanf(" %c %i %i", &ch, &r, &c);
		
		
		ui.Move(ch,r,c);
		
	}while(!ui.IsGameOver());
	return 0;
}
