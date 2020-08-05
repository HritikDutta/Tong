#include "../includes/menu.h"

int main()
{
	// Initialize ncurses
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);	// Don't display cursor

	main_menu();

	// End ncurses
	endwin();
}