/*linkedlist.h- This contains the function declarations used in linkedlist.c and the typedef of the structures*/
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
typedef struct node {
	char *str;
	char *suit;
	int node_val;
	struct node *next, *prev;
}node;
typedef struct list{
	node *head, *tail;
	int length;
}list;
float bet;
list user1, dealer1, deck;
void init(list *l);
void delete_full_list(list *l);
void remov(list *l);
void traverse(list *l);
void append(list *l, node *card_app);
int val_total(list *l);
node *shuffle(list *l, int pos);
