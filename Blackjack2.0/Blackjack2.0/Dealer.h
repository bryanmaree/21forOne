#pragma once

#include "Card.h"
#include "Player.h"
#include <iostream>
#include <sstream>

int where = 0;

//------------------------Dealer Class.h---------------------------------
class Dealer: public Player{
private:
	static const int DEALERMIN = 17;
public:
	Dealer(void);
	~Dealer(void);

	void printHand();
	void hit(const Card& );
	int handTotal();
	bool hasAce() { return false; }
};

//------------------------Dealer Class.cpp---------------------------------
Dealer::Dealer()
{
	Player();
}

Dealer::~Dealer(void)
{
}

void Dealer::hit(const Card& c) {
	if(handTotal() <= DEALERMIN) {
		hand[cardNumber++] = c;
	}
}

void Dealer::printHand() {
	for(int i = 0; i < cardNumber; i++) {
			cout << hand[i] << ", ";
	}

	if(handTotal() == BLACKJACK) {
		cout << "\nTotal: " << handTotal() << ", Blackjack!!" << endl;
	} else if(handTotal() > BLACKJACK) {
		cout << "\nTotal: " << handTotal() << ", Bust!!" << endl;
	} else if(handTotal() >= DEALERMIN) {
		cout << "\nDealer stands at " << handTotal() << "."  << endl;
	} else {
		cout << "\nTotal: " << handTotal() << endl;
	}
}

int Dealer::handTotal(){
	int handTotal = 0;
	bool aces = false;

	for(int i = 0; i < cardNumber; i++) {
		if(hand[i].face > 10 ) {
			handTotal += 10;
		} else if ( !aces && hand[i].face == 1 ){
			handTotal += 11;
			aces ++;
		}else {
			handTotal += hand[i].face;
		}
	}
	return handTotal;
}