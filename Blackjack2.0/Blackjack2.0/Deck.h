#pragma once
#include "Card.h"
#include <array>
#include <random>
#include <algorithm>
#include <iostream>
#include <time.h>
using namespace std;

//------------------------Deck Class.h---------------------------------
class Deck {
private:
	static const int DECKSIZE = 52;
	static const int FACES = 13;
	static const int SUITS = 4;

	Card cards[DECKSIZE];

	int cardsUsed;

public:
	Deck(void);
	~Deck(void);
	void clear();

	//Draw a card from the deck and increment the cardsUsed.
	Card& hit();
	//Shuffle the deck so that that it is random.
	void shuffleIt();

	void print();

	int getCardsUsed() { return cardsUsed; }

	bool isCardUsed(int location) { return cards[location].used; }

	int getCardValue( int location );
};

//------------------------Deck Class.cpp---------------------------------
Deck::Deck(void) {
	
	clear();
}

Deck::~Deck(void) {}

void Deck::clear() {

	for( int i=0; i<SUITS; i++ )
	{
		for( int j=1; j<=FACES; j++ )
		{
			cards [ i*FACES + j -1 ] = Card(j,i);
		}
	}

	cardsUsed = 0;
	shuffleIt();
}

Card& Deck::hit() {
	if( cardsUsed < DECKSIZE ) {
		return *cards[cardsUsed++].use();
	}

	else throw string("Deck overflow");
}

void Deck::shuffleIt() {
	//Create a temporary deck to put cards in a random order.
	Card tempDeck[DECKSIZE];

	srand(time(NULL));

	//here comes the shuffle
	for(int i = 0; i < DECKSIZE; i++) {
		//make spot be a random remainder of the deck count 52
		int spot = rand() % DECKSIZE;
		bool loop = true;
		do {
			// If the spot is open put the deck[i] in that spot
			if(tempDeck[spot].face == 0) {
				tempDeck[spot] = cards[i];
				//do not loop
				loop = false;
			} else {
				//because spot wasn"t open, just move one spot. 
				//or if the spot has gone past the end of the deck loop back arround to 0
				spot = (spot+1) % DECKSIZE;
				loop = true;
			}
		}while(loop);
	}

	//Point the deck to the tempDeck we just created.
	for ( int i=0; i<DECKSIZE; i++)
	{
		cards[i] = tempDeck[i];
	}
}

void Deck::print() {
	for(int i = 0; i< DECKSIZE; i++) {
		
		cout << cards[i] << endl;

	}
}

int Deck::getCardValue(int location)
{
	if ( cards[location].face > 9 ) return 10;
	else return cards[location].face;
}