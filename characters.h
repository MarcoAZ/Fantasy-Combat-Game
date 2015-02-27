/*******************************************************************************
* Author: Marco Zamora
* Class: CS 162
* Date: 2/21/15
* Edited: 2/24/15
* Assignment 4
*
* Purpose: Declarations for Dice and Characters
*******************************************************************************/
#ifndef CHAR_H
#define CHAR_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::string;
using std::queue;

class Dice
{
public:
	Dice();
	Dice( int numSides );
	virtual int rollDice() const;
	
protected:
	int numSides;
};

//abstract class
class Character
{
public:
	Character(){};
	Character(int ar, int str, string n)
	{
		this->armor = ar;
		this->strength = str;
		this->name = n;
		this->startStr = str;
		this->points = 0;
	}
	
	virtual ~Character(){};
	
	virtual int attack( Dice* die);
	
	virtual void defend( Dice* die, int attackDamage, string attacker ) = 0;
	
	void regenerate( Dice* die);

	void setStrength( int s )
	{	strength = s;}
	
	int getStrength()
	{	return strength;}
	
	int getStartStrength()
	{	return startStr;}
	
	string getName()
	{	return name;}
	
	void setName( string n )
	{	name = n;}
	
	void addPoint()
	{	points++;}
	
	int getPoints()
	{	return points;}
	
	string getTeam()
	{	return team;}
	
protected:
	int armor;
	int strength;
	string name;
	int startStr; //hold copy of starting strength for regeneration later
	int points;
	string team;
};

//barbarian class
class Barbarian : public Character
{
public:
	Barbarian() : Character( 0, 12, "Barbarian" ){};
	Barbarian(string tm) : Character( 0, 12, "Barbarian" )
	{
		this->team = tm;
	};
	
//	int attack( Dice* die );
	void defend( Dice* die, int attackDamage, string attacker );
	
private:

};

//reptile people declarations
class Reptile : public Character
{
public:
	Reptile() : Character( 7, 18, "Reptile People" ){};
	Reptile(string tm) : Character( 7, 18, "Reptile People" )
	{
		this->team = tm;
	};
	
	int attack( Dice* die);
	void defend( Dice* die, int attackDamage, string attacker );
};

//blue men
class Blue : public Character
{
public:
	Blue() : Character( 3, 12, "Blue Men" ){};
	Blue(string tm) : Character( 3, 12, "Blue Men" )
	{
		this->team = tm;
	};
	
	void defend( Dice* die, int attackDamage, string attacker );
};

//goblin class
class Goblin : public Character
{
public:
	Goblin() : Character( 3, 8, "Goblin" )
	{
		this->achilles = false;
	};
	
	Goblin(string tm) : Character( 3, 8, "Goblin" )
	{
		this->achilles = false;
		this->team = tm;
	};
	
	int attack( Dice* die );
	void defend( Dice* die, int attackDamage, string attacker );
	void hitAchilles()
	{	achilles = true;}
	
	bool achillesStat()
	{	return achilles;}
	
private:
	bool achilles;
};

//shadow class
class Shadow : public Character
{
public:
	Shadow() : Character( 0, 12, "The Shadow" ){};
	Shadow(string tm) : Character( 0, 12, "The Shadow" )
	{
		this->team = tm;
	};
	
	void defend( Dice* die, int attackDamage, string attacker );
};

//team class
class Team
{
public:
	Team()
	{
		points = 0;
	};
	
	void addFighter( int selection, string team );

	void addPoint()
	{	points++;}
	
	int getPoints()
	{ 	return points;}
	
	queue<Character*>* getQueue()
	{	return &lineup;}

private:
	queue<Character*> lineup;
	int points;
};

#endif
