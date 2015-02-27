/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 2/21/15
* Edited: 2/23/15
* Assignment 4
*
* Purpose: Function declarations for the main program
*******************************************************************************/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "characters.h"
#include <stack>

using std::cin;
using std::endl;
using std::stack;

//controls the battle between two characters
//string battle( Character* p1, Character* p2, Dice* d6);
string battle( Character* p1, Character* p2, Dice* d10, Dice* d6);

//controls whether the user would like to replay
bool askToReplay();

//allows user to choose fighter
int selectPlayer( int player );

//prints the list of fighters
void printList();

//selects the appropriate battle combination
//string selectBattle( int, int );

//gets a positive int from the user
int getPositiveInt();

//reports which team won
void reportWinner( Team p1, Team p2 );

//reports the top 3 fighters
void reportBestFighters( stack<Character*> );

#endif
