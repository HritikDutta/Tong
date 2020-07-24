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
	while (true)
	{
		switch (ch = getch())
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

		if (choice == num_choices - 1) break;

		if (choice != -1 && choice != num_choices - 1)
		{
			// Clean the line
			for (int i = 0; i < COLS; i++) mvaddch(LINES - 1, i, ' ');
			mvprintw(LINES - 1, 0, "You selected: %s", menu->choices[choice]);
			refresh();
		}
	}

	endwin();
}