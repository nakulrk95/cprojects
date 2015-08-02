/*blackjack.h- This contains the function declarations used in main.c*/
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
typedef struct user_info { 
	char user_name[50], user_username[50], user_password[50];
	int user_age;
	float user_bal;
}user_info;
user_info user;

float bet;

void create_csv();
void gotoxy(int x, int y);
void change_info();
int password(char *pass);
void buy_chips();
void sell_chips();
void logout();
void guide();
void credits();
void login();
int check_username(char *entun);
void new_user();
void ingame_menu(int flag1);
void disp_bal();
void play_game();
void create_deck();
int conv_to_cv(char *face_char);
void deal(int num1, int num2);
void result(int num);
