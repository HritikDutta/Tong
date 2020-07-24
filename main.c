#include "headers/menu.h"
#include <ncurses.h>

int main()
{
	char* name = "VIDEO GAME";

	char* choices[] = {
		"Resume Previous Match",
		"Player vs Computer",
		"Player vs Player",
		"Computer vs Computer",
		"Exit"
	};

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	// Make cursor invisible
	curs_set(0);

	printw("Press Arrow Keys to go up and down, and press Enter to select");
	refresh();

	int num_choices = sizeof(choices) / sizeof(char*);
	MENU* menu = create_menu(name, choices, num_choices);
	print_menu(menu);

	int ch, choice = -1;
	while (choice == -1 && (ch = getch()) != KEY_F(1))
	{
		switch (ch)
		{
			case KEY_UP:
				menu->selected = (menu->selected <= 0) ? menu->num_choices - 1: menu->selected - 1;
				print_menu(menu);
				break;
			
			case KEY_DOWN:
				menu->selected = (menu->selected >= menu->num_choices - 1) ? 0 : menu->selected + 1;
				print_menu(menu);
				break;

			case '\n':
				choice = menu->selected;
				break;
		}
	}

	// If an option is selected, show the user's choice at bottom of the screen
	if (choice != -1)
	{
		mvprintw(LINES - 1, 0, "You selected: %s", menu->choices[choice]);
		refresh();
		getch();
	}

	endwin();
}