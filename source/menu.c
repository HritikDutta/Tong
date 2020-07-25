#include "../includes/menu.h"

#include <string.h>
#include <stdlib.h>

MENU* create_menu(char* name, char* choices[], int num_choices)
{
	MENU* menu = (MENU*)malloc(sizeof(MENU));
	
	// Name
	menu->name = (char*)calloc(strlen(name) + 1, sizeof(char));
	strcpy(menu->name, name);

	// Choices
	menu->choices = (char**)calloc(num_choices, sizeof(char*));
	for (int i = 0; i < num_choices; i++)
	{
		menu->choices[i] = (char*)calloc(strlen(choices[i]) + 1, sizeof(char));
		strcpy(menu->choices[i], choices[i]);
	}

	// Data
	menu->selected = 0;
	menu->num_choices = num_choices;

	// Window Data
	menu->width = 40;
	menu->height = menu->num_choices + 4;
	menu->x = 0.5 * (COLS - menu->width);
	menu->y = 0.5 * (LINES - menu->height);
	menu->m_window = newwin(menu->height, menu->width, menu->y, menu->x);

	// Ready Menu
	box(menu->m_window, 0, 0);
	int menu_name_x = 0.5 * (menu->width - strlen(menu->name));
	mvwprintw(menu->m_window, 0, menu_name_x, menu->name);

	return menu;
}

void print_menu(MENU* menu)
{
	// Print Menu
	int x = 4;
	int y = 2;

	for (int i = 0; i < menu->num_choices; i++)
	{
		if (i == menu->selected)
		{
			wattron(menu->m_window, A_STANDOUT);
			mvwprintw(menu->m_window, y + i, x, menu->choices[i]);
			wattroff(menu->m_window, A_STANDOUT);
		} else
			mvwprintw(menu->m_window, y + i, x, menu->choices[i]);
	}

	wrefresh(menu->m_window);
}

void delete_menu(MENU* menu)
{
	free(menu->name);
	for (int i = 0; i < menu->num_choices; i++)
		free(menu->choices[i]);
	free(menu->choices);

	delwin(menu->m_window);
}

void menu_test()
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

	delete_menu(menu);
	endwin();
}