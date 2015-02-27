/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 2/21/15
* Edited: 2/23/15
* Assignment 4
*
* Purpose: Definitions for Dice and Characters
*******************************************************************************/

#include "characters.h"

Dice::Dice()
{
	numSides = 6;
	srand(time(NULL)); // Seeds random number generator
}

Dice::Dice(int numSides)
{
	this->numSides = numSides;
	srand(time(NULL)); // Seeds random number generator
}

int Dice::rollDice() const
{
	return (rand() % numSides) + 1;
}

//base class attack with two dice
int Character::attack( Dice* die)
{
	int roll1 = die->rollDice();
	int roll2 = die->rollDice();
	//no more reporting
	//cout << this->getName() << " rolled a " << roll1 + roll2 << " for attack.\n";
	return roll1 + roll2;
}

//base class health regeneration
void Character::regenerate( Dice* die)
{
	int roll = die->rollDice();
	
	int regen = this->getStrength() + roll;
	
	//set to regenerated health or max health
	if( regen > this->getStartStrength() )
	{
		this->setStrength( this->getStartStrength() );
	}
	else
	{
		this->setStrength( regen );
	}
}

void Team::addFighter( int selection, string team )
{
	switch(selection)
	{
		case 1:
		{
			Character* fighter = new Barbarian(team);
			lineup.push(fighter);
		}
		break;
		case 2:
		{
			Character* fighter = new Reptile(team);
			lineup.push(fighter);
		}
		break;
		case 3:
		{
			Character* fighter = new Blue(team);
			lineup.push(fighter);
		}
		break;
		case 4:
		{
			Character* fighter = new Goblin(team);
			lineup.push(fighter);
		}
		break;
		case 5:
		{
			Character* fighter = new Shadow(team);
			lineup.push(fighter);
		}
		break;
		default:
			cout << "Invalid selection" << endl;
			exit(-1);	
	}
}

//barbarian definitions
void Barbarian::defend( Dice* die, int attackDamage, string attacker )
{
	//2 dice for defense
	int defense = die->rollDice() + die->rollDice();
	
	//cout << this->getName() << " rolled " << defense << " for defense.\n";
	
	int damage = attackDamage - defense;
	
	if ( damage > 0)
	{
		damage -= this->armor;
		if ( damage > 0 )
		{
			this->setStrength( this->getStrength() - damage );
		}
	}
}

//reptile peeps definitions
int Reptile::attack( Dice* die )
{
	//roll 3 die
	int roll1 = die->rollDice();
	int roll2 = die->rollDice();
	int roll3 = die->rollDice();
	
	//cout << this->getName() << " rolled a " << roll1 + roll2 + roll3 << " for attack.\n";
	
	return roll1 + roll2 + roll3;
}

void Reptile::defend( Dice* die, int attackDamage, string attacker )
{
	//only one die for defense
	int defense = die->rollDice();
	
	//cout << this->getName() << " rolled " << defense << " for defense.\n";
	
	int damage = attackDamage - defense;
	
	if ( damage > 0)
	{
		damage -= this->armor;
		if ( damage > 0 )
		{
			this->setStrength( this->getStrength() - damage );
		}
	}
}

//blue men defintions
void Blue::defend( Dice* die, int attackDamage, string attacker )
{
	//3 dice for defense
	int defense = die->rollDice() + die->rollDice() + die->rollDice();
	
	//cout << this->getName() << " rolled " << defense << " for defense.\n";
	
	int damage = attackDamage - defense;
	
	if ( damage > 0)
	{
		damage -= this->armor;
		if ( damage > 0 )
		{
			this->setStrength( this->getStrength() - damage );
		}
	}
}

//goblin special defense and attack
int Goblin::attack( Dice* die )
{
	//roll 2 die
	int roll1 = die->rollDice();
	int roll2 = die->rollDice();
	int total = roll1 + roll2;
	
	if(total == 12)
	{
		this->hitAchilles();
		//cout << this->getName() << " cut the opponent's Achilles tendon!\n";
	}
	
	//cout << this->getName() << " rolled a " << roll1 + roll2 << " for attack.\n";
	
	return roll1 + roll2;
}

void Goblin::defend( Dice* die, int attackDamage, string attacker )
{
	//only one die for defense
	int defense = die->rollDice();
	
	//cout << this->getName() << " rolled " << defense << " for defense.\n";
	
	//if the achilles was cut, halve the damage (gets rounded down)
	if( this->achillesStat() && attacker != "Goblin" )
	{
		//cout << attacker << "'s attack was halved due to a damaged Achilles tendon!\n";
		attackDamage /= 2;
	}
	
	int damage = attackDamage - defense;
	
	if ( damage > 0)
	{
		damage -= this->armor;
		if ( damage > 0 )
		{
			this->setStrength( this->getStrength() - damage );
		}
	}
}

//Shadow defense
void Shadow::defend( Dice* die, int attackDamage, string attacker )
{
	//only one die for defense
	int defense = die->rollDice();
	
	//cout << this->getName() << " rolled " << defense << " for defense.\n";

	int damage = attackDamage - defense;
	
	//only takes damage half of the time
	if ( rand() % 2 )
	{
		if ( damage > 0)
		{
			
			damage -= this->armor;
			if ( damage > 0 )
			{
				this->setStrength( this->getStrength() - damage );
			}
		}
	}
	//else
	//{
	//cout << this->getName() << "avoided all damage through manipulation!\n";
	//}
}
