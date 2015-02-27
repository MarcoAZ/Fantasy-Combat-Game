/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 2/21/15
* Edited: 2/24/15
* Assignment 4
*
* Purpose: Functions for the main program
*******************************************************************************/
#include "functions.h"

//function that has two oppenents battle with 10-sided dice for attack and 6-sided for defense
string battle( Character* p1, Character* p2, Dice* d10, Dice* d6)
{
	//change name if players are named the same
	if( p1->getName() == p2->getName() )
	{
		p2->setName( p2->getName() + "2" );
	}
	

	while( p1->getStrength() > 0 && p2->getStrength() > 0 )
	{
		//first player attacks first
		//check if player one is a character that uses d10 for attack
		if( p1->getName() == "Blue Men" || p1->getName() == "The Shadow")
		{
			p2->defend( d6, p1->attack( d10 ), p1->getName() );
		}
		else
		{
			//attack with regular d6 die
			p2->defend( d6, p1->attack( d6 ), p1->getName() );
		}
		//no longer reporting rolls and damage
		//cout << p2->getName() << ": Strength points = " << p2->getStrength() << ".\n";
		
		//make some room
		//cout << "\n";
		
		if( p2->getStrength() < 1 )
		{
			return p1->getName();
		}
		
		//second player attacks, again checking for creature's appropriate sided dice
		if( p2->getName() == "Blue Men" || p2->getName() == "The Shadow" || p2->getName() == "The Shadow2" || p2->getName() == "The Shadow2")
		{
			p1->defend( d6, p2->attack( d10 ), p2->getName() );
		}
		else
		{
			//attack with regual dice
			p1->defend( d6, p2->attack( d6 ), p2->getName() );
		}
		
		//cout << p1->getName() << ": Strength points = " << p1->getStrength() << ".\n";
		
		//make some room
		//cout << "\n";
		
		if( p1->getStrength() < 1 )
		{
			return p2->getName();
		}
	}

	//control should not reach here
	cout << "ERROR" << endl;
	exit(-1);

}

//controls whether the player would like to replay
bool askToReplay()
{
	char response;
	
	do
	{
		cout << "Would you like to run another battle? (y to continue)\n";
	}
	while( !(cin >> response) );
	
	if( response == 'y' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

//allows user to choose fighter
int selectPlayer( int player )
{
	//print list
	printList();
	
	int selection;
	do
	{
		cout << "Select fighter #" << player << " by number: ";
	}
	while( !(cin >> selection) || selection < 1 || selection > 5 );
	
	return selection;
}

//prints list of fighters
void printList()
{
	cout << endl;
	cout << "1. Barbarian" << endl;
	cout << "2. Reptile People" << endl;
	cout << "3. Blue Men" << endl;
	cout << "4. Goblin" << endl;
	cout << "5. The Shadow" << endl;
}

//gets a positive int from the user
int getPositiveInt()
{
	int temp;
	try
	{
		cout << "Please enter a positive integer: ";
		cin >> temp;
		
		if ( temp < 0 )
		{
			throw temp;
		}
		if ( !cin.good() )
		{
			string s = "Not a number";
			throw s;
		}
	}
	catch( int i )
	{
		cout << "Exiting program. Reason: " << i << " is less than 0." << endl;
		exit(-1);
	}
	catch( string e)
	{
		cout << "Exiting program. Reason: "<< e << endl;
		exit(-1);
	}
	catch(...)
	{
		cout << "Exiting program due to error" << endl;
		exit(-1);
	}
	
	return temp;
}

//reports which team won
void reportWinner( Team p1, Team p2 )
{
	if( p1.getPoints() > p2.getPoints() )
	{
		cout << "Player 1 wins! Score: " << p1.getPoints() << "-" << p2.getPoints() << endl;
	}
	else if( p1.getPoints() < p2.getPoints() )
	{
		cout << "Player 2 wins! Score: " << p1.getPoints() << "-" << p2.getPoints() << endl;
	}
	else
	{
		cout << "The two teams have tied!" << endl;
	}
}

//reports the top 3 fighters
void reportBestFighters( stack<Character*> fighters)
{
	Character* first = 0;
	Character* second = 0;
	Character* third = 0;
	
	Character* fighter;
	
	while( !(fighters.empty()) )
	{
		fighter = fighters.top();
		
		//check if pointint to valid object
		if(!first)
		{
			first = fighter;
		}
		else
		{
			if( fighter->getPoints() > first->getPoints() )
			{
				//second place moves to third
				third = second;
				//1st place moves to 2nd
				second = first;
				//new 1st place finisher
				first = fighter;
			}
			else if(!second)
			{
				second = fighter;
			}
			else
			{
				if( fighter->getPoints() > second->getPoints() )
				{
					//second place moves to third
					third = second;
					//new 2nd place
					second = fighter;
				}
				else if( !third )
				{
					third = fighter;
				}
				else
				{
					if( fighter->getPoints() > third->getPoints() )
					{
						third = fighter;
					}
				}
			}
		}
		
		//toss out the character
		fighters.pop();
	}
	
	cout << "First place: " << first->getTeam() << "'s " << first->getName() << " with " << first->getPoints() << " points" << endl;
	
	cout << "Second place: " << second->getTeam() << "'s " << second->getName() << " with " << second->getPoints() << " points" << endl;
	
	//there may be a chance that only two fighters competed
	if(third)
	{
	cout << "third place: " << third->getTeam() << "'s " << third->getName() << " with " << third->getPoints() << " points" << endl;
	}
	
}
