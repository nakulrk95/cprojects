/*admin.c - This file contains functions related to the developer section or admin section of the program*/
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
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <ncurses.h>
#include "admin.h"
#include "blackjack.h"
#include "ncfunc.h"
/*Description- When this function is called it prints a menu for 
 * the developer. The developer is supposed to type 1 or 2 
 * which calls other functions.*/
void admin_menu() {
	int opt;
	system("clear");
	printf("Select an option\n");
	printf("1. Get user info in a csv file\n");
	printf("2. Logout\n");
	scanf("%d", &opt);
	switch(opt) {
		case 1: /*create csv*/
			create_csv();
			admin_menu();
			break;
		case 2:
			menu();
			break;
		default: 
			admin_menu();
			break;
	}
}
/*Description- When this function is called it asks the developer for his admin password.
 *The admin passwword is stored over here. It then checks the password and calls the 
 * admin_menu() function if the password is correct */
void admin_login() {
	char adminpass[7] = "arsenal";
	adminpass[7] = '\0';
	system("clear");
	gotoxy(20, 5);
	printf("PASSWORD : ");
	if(password(adminpass) == 1) {
		admin_menu();
	}
	else {
		menu();
	}
}
