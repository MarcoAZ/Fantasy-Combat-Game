/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 2/21/15
* Edited: 2/24/15
* Assignment 4
*
* Purpose: Fantasy Comabt Tournament - the main program and functions
*******************************************************************************/
#include "characters.h"
#include "functions.h"

int main()
{
	//get number of fighters
	cout << "How many fighters will each team have?" << endl;
	int numFighters = getPositiveInt();
	
	//player 1 chooses fighters
	Team player1;
	cout << "Player 1, choose you characters." << endl;
	for( int i = 0; i < numFighters; i++ )
	{
		player1.addFighter( selectPlayer( i+1 ), "Player 1" );
	}
	
	//make space
	cout << endl;
	
	//player 2 chooses fighters
	Team player2;
	cout << "Player 2, choose you characters." << endl;
	for( int i = 0; i < numFighters; i++ )
	{
		player2.addFighter( selectPlayer( i+1 ), "Player 2" );
	}
	cout << endl;
	
	//prepare the loser pile
	stack<Character*> losers;
	
	//while neither queue is empty
	while( !( player1.getQueue() )->empty() && !( player2.getQueue() )->empty() )
	{
		//create dice
		Dice d10(10);
		Dice d6;
		
		//get head of each queue for the fight and remove them from the lineups
		Character* fighter1 = ( player1.getQueue() )->front();
		( player1.getQueue() )->pop();
		Character* fighter2 = ( player2.getQueue() )->front();
		( player2.getQueue() )->pop();
		
		//who's fighting?
		cout << fighter1->getName() << " vs. " << fighter2->getName() << endl;
		//fight!
		string winner = battle( fighter1, fighter2, &d10, &d6);
		
		//winner gets put back into his lineup, loser gets put in the loser pile
		if( winner == fighter1->getName() )
		{
			cout << "Winner: Player 1's " << winner << endl;
			//gets point to character and team
			fighter1->addPoint();
			player1.addPoint();
			
			//regenerate
			fighter1->regenerate( &d6 );
			
			//gets put in pack of team queue
			( player1.getQueue() )->push( fighter1 );
			
			//loser gets put in loser pile
			losers.push( fighter2 );
		}
		else if( winner == fighter2->getName() )
		{
			cout << "Winner: Player 2's " << winner << endl;
			//gets point to character and team
			fighter2->addPoint();
			player2.addPoint();
			
			//regenerate
			fighter2->regenerate( &d6 );
			
			//gets put in pack of team queue
			( player2.getQueue() )->push( fighter2 );
			
			//loser gets put in loser pile
			losers.push( fighter1 );		
		}
		else
		{
			cout << "Error: No winner was reported." << endl;
			exit(-1);
		}
		
		cout << endl;
	}
		
	//compare team points to get winners
	reportWinner( player1,  player2);
	
	//add the remaining fighters to the loser pile
	while( !( player1.getQueue() )->empty() )
	{
		Character* fighter = ( player1.getQueue() )->front();
		( player1.getQueue() )->pop();
		losers.push( fighter );
	}
	while(  !( player2.getQueue() )->empty() )
	{
		Character* fighter = ( player2.getQueue() )->front();
		( player2.getQueue() )->pop();
		losers.push( fighter );
	}
	
	//get the top 3 winners
	reportBestFighters( losers );
	
	//clean up by deleting fighters
	while( !losers.empty() )
	{
		delete losers.top();
		losers.pop();
	}
	
	//exit
	return 0;
}

