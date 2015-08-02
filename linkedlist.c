/*linkedlist.c - This file contains functions related to linkedlists used in the program*/
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
#include <string.h>
#include "linkedlist.h"
/*Input - list structure pointer
 *Description- initializes the structure list*/
void init(list *l) {
	l->head = l->tail = NULL;
	l->length = 0;
}
/*Input - list structure pointer
 *Description - deletes the whole linked list*/
void delete_full_list(list *l) {
	while(l->length) {
		remov(l);
	}
}
/*Input - list structure pointer
 *Description - deletes one node from the end*/
void remov(list *l) {
	node *p;
	p = l->tail;
	if(l->length == 1) {
		l->head = NULL;
		l->tail = NULL;
	}
	else {
		p->prev->next = NULL;
		l->tail = l->tail->prev;
	}	
	free(p);
	l->length--;	
}
/*Input - list structure pointer
 *Description - traverses the list and prints it*/
void traverse(list *l) {
	node *p;
	p = l->head;
	
	while(p != l->tail) {
		printf("[ ");
		printf("%s ", p->str);
		printf("%s ", p->suit);
		printf(" ]");		
		p = p->next;
	} /* p points to l->tail */
	if(p) {
		printf("[ ");
		printf("%s ", p->str);
		printf("%s ", p->suit);
		printf(" ]");		
	}
} /*Use graphics over here*/
/*Input - list structure pointer, node struct pointer
 *Description - appends the data pointed by card_app to the list pointed by l*/
void append(list *l, node *card_app) {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->str = malloc(strlen(card_app->str)+1);
	strcpy(tmp->str, card_app->str);
	tmp->suit = malloc(strlen(card_app->suit)+1);
	strcpy(tmp->suit, card_app->suit);
	tmp->node_val = card_app->node_val;
	if(l->head == NULL) {
		tmp->next = NULL;
		tmp->prev = NULL;
		l->head	= tmp;
	}
	else {
		tmp->prev = l->tail;
		tmp->next = NULL;
		l->tail->next = tmp;
	}
	l->tail = tmp;
	l->length++;
}
/*Input - list structure pointer
 *Output - Integer sum of node_val
 *Description - it returns the sum of the card values in a list*/
int val_total(list *l) {
	node *nodeptr;
	int sum = 0;
	nodeptr = l->head;
	while(nodeptr->next != NULL) {
		sum = sum + nodeptr->node_val;
		nodeptr = nodeptr->next;
	}
	sum = sum + nodeptr->node_val;
	return sum;
}

/*Input - list structure pointer, integer positions
 *Output - Node structure pointer 
 *Description - it removes the selected node and appends it at the end*/
node *shuffle(list *l, int pos){
	int i;
	node *p, *q;	
	p = l->head;
	q = l->tail;
	for(i = 0; i < pos; i++)
		p = p->next;
	if(pos == 52) {
		return p;
	}
	else if(pos == 1) {
		p->next->prev = NULL;	
	}
	else{
		p->prev->next = p->next;
		p->next->prev = p->prev;	
	}
	p->prev = q;
	p->next = NULL;
	q->next = p;
	l->tail = p;
	return p;/*???*/
}
