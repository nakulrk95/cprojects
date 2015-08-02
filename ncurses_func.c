/*ncurses_func.c - This file contains functions related to the graphics part of the program*/
/*****************************************************************************
 * Copyright (C) Nakul 'Wenger' Ramakumar. nakulrk95@gmail.com
 * College: COEP Batch- Comp 2017 MIS No.- 111303032
 * This program was created for the Data Structures and Algorithms course
 *
 * DICLAIMER:- I do not promote any form of gambling or betting through this 
 * program.
 *
 * This program is a game of Blackjack.
 * It supports multiple users.
 * This is not a gambling or betting application.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "linkedlist.h"
#include <ncurses.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "ncfunc.h"
#include "blackjack.h"
#include "admin.h"

#define WIDTH 30
#define HEIGHT 10
int startx = 0;
int starty = 0;
char *choices[] = { 
		"How to Play",
		"Login",
		"Create Accout",
		"Credits",
		"Admin login",
		"Exit",
};
char *choices2[] = { 
		"How to Play",
		"Play Game",
		"Buy Chips",
		"Sell Chips",
		"Check Balance",
		"Change info",
		"Logout",
};
int n_choices = sizeof(choices) / sizeof(char *);
int n_choices2 = sizeof(choices2) / sizeof(char *);
/*Description - Prints the main menu in a new window using ncurses library*/
void menu() {
	system("clear");
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 20, "***************BLACKJACK****************");
	mvprintw(2, 7, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	clrtoeol();
	endwin();
	switch(choice) {
		case 1: /*Guide*/
			guide();
			menu();
			break;
		case 2: /*Login*/
			login();
			break;
		case 3: /*New account*/
			new_user();
			menu();
			break;
		case 4: /*Credits*/
			credits();
			menu();
			break;
		case 5: /*Admin*/
			admin_login();
			break;
		case 6: /*exit*/
			exit(0);
			break;
	}
}
/*Description - Prints the menu tht appears after login in a new window using ncurses library*/
void login_menu() {
	system("clear");
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 20, "***************WELCOME****************");
	mvprintw(2, 7, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu2(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices2;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices2)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu2(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}
	clrtoeol();
	endwin();
	switch(choice) {
		case 1: /*Guide*/
			guide();
			login_menu();
			break;
		case 2: /*Play Game*/
			play_game();
			break;
		case 3: /*Buy*/
			buy_chips();
			login_menu();
			break;
		case 4: /*Sell*/
			sell_chips();
			login_menu();
			break;
		case 5: /*Check bal*/
			disp_bal();
			login_menu();
			break;
		case 6: /*Change_info*/
			change_info();
			login_menu();
			break;
		case 7: /*Log out*/
			logout();
			menu();
			break;
		default:
			login_menu();
			break;
	}
}
/* Input - WINDOW pointer, integer highlight
 * Description - Prints the box and the contents in the login menu*/
void print_menu2(WINDOW *menu_win, int highlight) {
	int x, y, i;	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices2; ++i) {
		if(highlight == i + 1) { /* High light the present choice */
			wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices2[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices2[i]);
		++y;
	}
	wrefresh(menu_win);
}
/* Input - WINDOW pointer, integer highlight
 * Description - Prints the box and the contents in the main menu*/
void print_menu(WINDOW *menu_win, int highlight) {
	int x, y, i;	
	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i) {
		if(highlight == i + 1) { /* High light the present choice */
			wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}
