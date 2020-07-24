#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

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

#endif // MENU_H