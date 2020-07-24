#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	char* name;
	char** choices;

	int selected;
	int num_choices;

	// Window data
	int x, y;
	int width, height;
	WINDOW* m_window;
} MENU;

MENU* create_menu(char* name, char* choices[], int num_choices);
void print_menu(MENU* menu);


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

#endif // MENU_H