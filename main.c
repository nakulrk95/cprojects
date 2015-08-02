/*admin.c - This file contains the function main() and other important functions related to the program*/
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
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include "blackjack.h"
#include "linkedlist.h"
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
//#include "ncfunc.h"

void menu();
void login_menu();
list user1, dealer1, deck;
int n = 51;

char *suit_arr[] = { "Clubs", "Spades", "Hearts", "Diamonds" };
char *face_arr[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

/*Output-Integer that is returned from getchar() function
 *Description- The function reads a single-byte character from the terminal*/
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
/*Description- The function creates a csv file of all the user profiles
 * which can be opened in spreadsheet applications like Excel and LibreOffce Calc*/
void create_csv() {
	user_info temp_user;
	FILE *f1, *f2;
	f1 =  fopen("users", "r");
	if(f1 == NULL) {
		perror("fopen failed");
	}
	else {
		
		f2 = fopen("adm_users.csv", "w");
		fprintf(f2, "User Name, Name, Age, Password, Balance\n");
		while(fread(&temp_user, sizeof(temp_user), 1, f1)) {
			fprintf(f2, "%s, %s, %d, %s, %f\n", temp_user.user_username, temp_user.user_name, temp_user.user_age, 				temp_user.user_password, temp_user.user_bal);
		}
		fclose(f2);
		fclose(f1);		
	}
}
/*Description- It points the cursor to the  position specified in the input
 * input- position in the terminal window*/
void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y, x);
}
/*Description- It provides a menu in which the user chooses whether he wants
 * to change his name or password*/
void change_info() {
	int opt;
	system("clear");
	printf("Which field do you want to change?\n");
	printf("1. Name\n");
	printf("2. Password\n");
	scanf("%d", &opt);
	switch(opt) {
		case 1:/*Name*/
			system("clear");
			char new_name[50];
			printf("Enter New name\n");
			scanf("%s", new_name);
			strcpy(user.user_name, new_name);
			system("clear");
			//gotoxy(20, 5);
			printf("\n\n\n\n\t\t\t\tData changed successfully");
			getch();
			break;
		case 2:/*Password*/
pass:			system("clear");
			printf("CURRENT PASSWORD : ");
			getch();
			if(password(user.user_password) == 1) {
				char new_pass[50];
				printf("\nEnter New Password\n");
				scanf("%s", new_pass);
				strcpy(user.user_password, new_pass);
				system("clear");
				//gotoxy(20, 5);
				printf("\n\n\n\n\t\t\t\tPassword changed successfully");
				getch();
			}
			else {
				goto pass;
			}
			break;
	}
}
/*Description- It masks the password and replaces it with * when user is typing
 *Input- the correct password
 *Output- 0 if password doesn't match, 1 if it matches*/
int password(char *pass) {
	int i = 0;
	char ent_password[50];
	char c;
	while(1) {
		c = getch();
		if(c == '\n') {
			break;
		}
		ent_password[i++] = c;
		c = '*';
		printf("%c", c);
	}
	ent_password[i] = '\0';
	/*printf("%s", ent_password);*/
	if(strcmp(ent_password, pass) == 0) {
		return 1;
	}
	else {
		printf("\nWrong Password\n");
		getch();
		return 0;
	}
}
/*Description- It asks the user to type the no. of chips he wants to buy and asks him to enter his password*/
void buy_chips() {
	system("clear");
	float amount;
	printf("Enter amount of chips to buy\n");
	printf("Enter 0 to go back\n");
	scanf("%f", &amount);
	if(amount == 0) {
		login_menu();
	}
	printf("PASSWORD : ");
	getch();
	if(password(user.user_password) == 1) {
		user.user_bal = user.user_bal + amount;
		printf("\nTransaction complete! Amount has been deducted from your linked bank account\n");
		getch();
		login_menu();
	}
	else {
		buy_chips();
	}
}
/*Description- It asks the user to type the no. of chips he wants to sell and asks him to enter his password*/
void sell_chips() {
	system("clear");
	float amount;
	printf("Enter amount of chips to sell\n");
	printf("Enter 0 to go back\n");
	scanf("%f", &amount);
	if(amount == 0) {
		login_menu();
	}
	printf("PASSWORD : ");
	getch();
	if(password(user.user_password) == 1) {
		user.user_bal = user.user_bal - amount;
		system("clear");
		printf("Authenticating...");
		system("clear");
		printf("Transfering money...");
		system("clear");
		printf("\nTransaction complete! Amount has been added to your linked bank account\n");
		getch();
		login_menu();
	}
	else {
		sell_chips();
	}
}
/*Description-  Saves data into a file with the filename the same as the unique username*/
void logout() { 
	user_info tmpuser;
	int err;
	FILE *fp1 = fopen("users", "r");
	if(fp1 == NULL) {
		perror("fopen failed");
	}
	FILE *fp2 = fopen("temp", "w");
	if(fp2 == NULL) {
		perror("fopen failed");
	}
	while(fread(&tmpuser, sizeof(tmpuser), 1, fp1)) {
		if(strcmp(tmpuser.user_username, user.user_username) != 0) {
			fwrite(&tmpuser, sizeof(tmpuser), 1, fp2);
		}
		else {
			strcpy(tmpuser.user_password, user.user_password);
			strcpy(tmpuser.user_name, user.user_name);
			tmpuser.user_bal = user.user_bal;
			fwrite(&tmpuser, sizeof(tmpuser), 1, fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
	err = remove("users");
	if(err != 0) 
		perror("remove failed");
	else {
		rename("temp", "users");
	}
}
/*Description- Prints data from the text file guide.txt to the terminal*/
void guide() {
	/*Take data from file guide.txt*/
	char ch;
	FILE *fp = fopen("guide.txt", "r");
	if(fp == NULL)
		perror("fopen failed");
	else {
		while((ch = fgetc(fp)) != EOF) {
			printf("%c", ch);
		}
	}
	fclose(fp);
	getch();
	getch();	
}
/*Description- Prints data from the text file credits.txt to the terminal*/
void credits() {
	/*Take data from file credits.txt*/
	char ch;
	FILE *fp = fopen("credits.txt", "r");
	if(fp == NULL)
		perror("fopen failed");
	else {
		while((ch = fgetc(fp)) != EOF) {
			printf("%c", ch);
		}
	}
	fclose(fp);
	printf("Press any key to go back");
	getch();
}
/*Description- It asks for the username and password of the user and authenticates login*/
void login() {
	system("clear");
	user_info luser;
	char ent_username[50];
	gotoxy(20, 5);
	printf("Username : ");
	scanf("%s", ent_username);
	FILE *fp2 = fopen("users", "r");
	if(fp2 == NULL) {
		perror("fopen failed");
	}
	else {
		int flag = 0;
		int n;
		while(flag == 0) {
			n = fread(&luser, sizeof(user_info), 1, fp2);
			if(n == 0) {
				break;
			}
			/*printf("username = %s\n", luser.user_username);
			printf("name = %s\n", luser.user_name);
			printf("password = %s\n", luser.user_password);
			printf("age = %d\n", luser.user_age);
			printf("bal = %f\n", luser.user_bal);*/
			if(strcmp(luser.user_username, ent_username) == 0) {
				flag = 1;
				gotoxy(20, 7);
				printf("PASSWORD : ");
				getch();
				if(password(luser.user_password) == 1) {
					strcpy(user.user_password, luser.user_password);
					strcpy(user.user_username, luser.user_username);
					strcpy(user.user_name, luser.user_name);
					user.user_age = luser.user_age;
					user.user_bal = luser.user_bal;
					login_menu();
				}
				else {
					login();
				}
			}/*End of if*/
		}/*end of while loop*/
		fclose(fp2);
		if(flag == 0) {
			printf("Invalid username please create an account first\n");
			getch();
			printf("Press any key to go back\n");
			getch();
			menu();
		}
	}/*end of else*/	
}
/*Description- It checks if the username entered is unique or not
 * Input- username
 *Output- 1 if not unique, 0 if unique*/
int check_username(char *entun) {
	user_info chuser;
	FILE *fp2 = fopen("users", "r");
	if(fp2 == NULL) {
		perror("fopen failed");
	}
	else {
		int flag = 0;
		int n;		
		while(flag == 0) {
			n = fread(&chuser, sizeof(user_info), 1, fp2);
			if(n == 0) {
				break;
			}
			if(strcmp(chuser.user_username, entun) == 0) {
				flag = 1;				
				return 1;
			}/*End of if*/
		}/*end of while loop*/
		fclose(fp2);
		if(flag == 0) {
			return 0;
		}
	}
	return 0;
}
/*Description- It opens a form in which the user has to fill up his/her details*/
void new_user() {
	system("clear");
	int rec_count = 0;
	user_info nuser;
	printf("Enter name\n");
	scanf("%s", nuser.user_name);
un:	printf("Enter unique username\n");
	scanf("%s", nuser.user_username);
	if(rec_count != 0) {
		if(check_username(nuser.user_username) != 0) {
			printf("Choose another username\n");
			goto un;
		}
	}
	printf("Enter age\n");
	scanf("%d", &nuser.user_age);
	if(nuser.user_age < 18) {
		printf("SORRY YOU ARE UNDER THE LEGAL GAMBLING AGE\n");
		new_user();
	}
	printf("Enter a password\n");
	scanf("%s", nuser.user_password);
	printf("Buy chips\n");
	printf("Enter amount :\n");
	scanf("%f", &nuser.user_bal);
	FILE *fp;
	fp = fopen("users", "a");
	if(fp == NULL)
		perror("fopen failed");
	else {
		fwrite(&nuser, sizeof(nuser), 1, fp); 
		fclose(fp);
		rec_count++;
		printf("Account Successfully CREATED!\n");
	}
}
/*Input - flag , if 1 then display option 3
 * Description- it prints the ingame menu and is the main code of the blackjack game*/
void ingame_menu(int flag1) {
	int option2;
	printf("Select an option\n");
	printf("1. HIT\n");
	printf("2. STAND\n");
	if(flag1 == 1)
		printf("3. DOUBLE\n");
	scanf("%d", &option2);
	switch(option2) {
		case 1:/*Hit*/
			deal(1, 1);
			system("clear");
			printf("\n\n\nYour hand!\t\t\t\t\t\t\tDealer Hand! \n");
			traverse(&user1);
			printf("\t\t\t");
			traverse(&dealer1);
			printf("\nYour sum is %d\n", val_total(&user1));/*traverse(&deck);*/
			if(val_total(&user1) > 21) {
				printf("BUSTED!\n");
				result(0); /*calculates the user balance and calls the play_game func*/			
			}
			else {
				ingame_menu(0);	
			}
			break;
		case 2:/*Stand*/
			while(val_total(&dealer1) < 17) {
				deal(2,1);
				system("clear");
				printf("\n\n\nYour hand!\t\t\t\t\t\t\tDealer Hand! \n");
				traverse(&user1);
				printf("\t\t\t");
				traverse(&dealer1);
				printf("\nYour sum is %d", val_total(&user1));
				printf("\t\t\t\t\t\tDealer sum is %d\n", val_total(&dealer1));/*traverse(&deck);*/
			}
			if(val_total(&dealer1) > 21) {
				result(2);
			}
			else {
				if(val_total(&user1) > val_total(&dealer1)) 
					result(2);
				else if(val_total(&user1) == val_total(&dealer1))
					result(1);
				else
					result(0);
			}			
			break;
		case 3:/*Double*/
			if(flag1 == 0) {
				printf("Option not available\n");
				ingame_menu(0);
				break;	
			}
			user.user_bal = user.user_bal - bet;
			bet = bet * 2;
			deal(1, 1);
			system("clear");
			printf("\n\n\nYour hand!\t\t\t\t\t\t\tDealer Hand! \n");
			traverse(&user1);
			printf("\t\t\t");
			traverse(&dealer1);
			printf("\nYour sum is %d", val_total(&user1));
			printf("\t\t\t\t\t\tDealer sum is %d\n", val_total(&dealer1));
			if(val_total(&user1) > 21) {
				printf("BUSTED!\n");
				result(0); /*calculates the user balance and calls the play_game func*/			
			}
			else {
				while(val_total(&dealer1) < 17) {
					deal(2,1);
					system("clear");
					printf("\n\n\nYour hand!\t\t\t\t\t\t\tDealer Hand! \n");
					traverse(&user1);
					printf("\t\t\t");
					traverse(&dealer1);
					printf("\nYour sum is %d", val_total(&user1));
					printf("\t\t\t\t\t\tDealer sum is %d\n", val_total(&dealer1));
				}
				if(val_total(&dealer1) > 21) {
					result(2);
				}
				else {
					if(val_total(&user1) > val_total(&dealer1)) 
						result(2);
					else if(val_total(&user1) == val_total(&dealer1))
						result(1);
					else
						result(0);
				}
			}
			break;
		default :
			ingame_menu(0);
			break;
	}
}
/*Displays the user_bal(user balance chips)*/
void disp_bal() {
	gotoxy(20, 5);
	printf("WELCOME %s\n", user.user_name);
	printf("Your account balance is %f ", user.user_bal);
	getch();
}
/*Description- This function starts the game of blackjack*/
void play_game() {
	int option1;
	system("clear");
	printf("Welcome %s \n", user.user_name);
	printf("Chips remaining : %f \n", user.user_bal);
	printf("Enter your bets\n");
	scanf("%f", &bet);
	if(bet > user.user_bal) {
		printf("You don't have enough chips. Please choose an option. \n");
		printf("1. Reduce bet and play again\n");
		printf("2. Buy more chips\n");
		scanf("%d", &option1);
		switch(option1) {
			case 1: 
				play_game();
				break;
			case 2: 
				buy_chips();
				play_game();
				break;
		}
	}
	else if(bet == 0) {
		printf("Please enter a positive bet amount\n");
		play_game();
	}
	else {
		system("clear");
		user.user_bal = user.user_bal - bet;
		init(&user1);
		init(&dealer1); //printf("Debug 2\n");
		deal(1, 2); /*Self Deal 2 cards*/
		deal(2, 1); /*Dealer Deal 1 card seg fault*/
		printf("\n\n\n");
		printf("Your hand!\t\t\t\t\t\tDealer Hand! \n");
		traverse(&user1);
		printf("\t\t\t");
		traverse(&dealer1);
		printf("\nYour sum is %d", val_total(&user1)); /*try to include sum in traverse*/
		printf("\t\t\t\tDealer sum is %d\n", val_total(&dealer1)); /*traverse(&deck);*/
		if(val_total(&user1) == 21) {
			result(3); /*Blackjack case*/
		}
		else
			ingame_menu(1);
	}
}
/*Description- It creates a basic deck of 52 cards(linked list)*/
void create_deck() {
	int i, j;
	node s;
	init(&deck);
	for(i = 0; i < 4; i++) {
		s.suit =  suit_arr[i];
		for(j = 0; j < 13; j++) {
			s.str = face_arr[j];
			s.node_val = conv_to_cv(face_arr[j]);
			append(&deck, &s);
		}
	}
}
/*Description- Converts the face to a card value which follows the rules of blackjack
 *Input- Charater array of face value of cards
 *Output- The card value*/
int conv_to_cv(char *face_char) {
	if(strcmp(face_char, "A") == 0) {
		return 11;
	}
	if(strcmp(face_char, "J") == 0) {
		return 10;
	}
	if(strcmp(face_char, "Q") == 0) {
		return 10;
	}
	if(strcmp(face_char, "K") == 0) {
		return 10;
	}
	else {
		return atoi(face_char);
	}
}
/*Description- Chooses a random number which aids in the shuffle func and it appends a random card to the hand
 *Input- num1 = 1 - append to user hand, 2- append to dealer hand
 * num2 is the number of cards to be appended*/
void deal(int num1, int num2) { /*Works properly*/
	int i = 0;
	while(i < num2) {
		int number;
		srand(time(NULL));
		number = rand() % n + 1;/*printf("DEBUG : num = %d", number);*/
		--n;/*printf("DEBUG: n = %d", n);*/
		if(n < 20)
			n = 51;
		node *temp;
		temp = shuffle(&deck, number); /* use node pointer or this??? */
		//printf("debug 4\n");
		if(num1 == 1) {
			append(&user1, temp);/* add suit too or pass struct as argument*/
		}
		if(num1 == 2) {
			append(&dealer1, temp);		
		}//printf("debug 5\n");
		i++;
	}
}
/*Description- Takes action according to the possible outcomes of the game
 * Input - scenario number*/
void result(int num) {
	int dec;
	switch(num) {
		case 0: /*Lose*/
			printf("You lose! All bets lost\n");
			bet = 0;
			break;
		case 1: /*Draw*/
			printf("Push - No chips lost, No chips won\n");
			break;
		case 2: /*Win*/
			printf("You WIN You have won %f chips!\n", bet);
			bet = bet * 2;
			break;
		case 3: /*BLACKJACK*/
			printf("BLACKJACK!!! You have won %f chips!\n", (bet * 2));
			bet = bet * 3;
			break;
	}
	user.user_bal = user.user_bal + bet;
	bet = 0;
	delete_full_list(&user1);
	delete_full_list(&dealer1);
opt:	printf("Do you want to play more?\n");
	printf("1.Yes\n");
	printf("2.No\n");
	scanf("%d", &dec);
	if(dec == 1) {
		play_game();
	}
	else if(dec == 2) {
		login_menu();
	}
	else {
		printf("Please enter a valid option\n");
		goto opt;
	}
}
int main(int argc, char *argv[]) {
	create_deck();
	menu();
	return 0;
}
