#pragma once
#include "Card.h"
#include <iostream>

using namespace std;

char choice;
//------------------------Player Class.h---------------------------------
class Player {
protected:
	static const int MAXCARDS = 11;
	static const int BLACKJACK = 21;
	Card hand[MAXCARDS];
	int cardNumber;
	bool aced;
public:
	Player();
	~Player(void);
	void clear();
	int handTotalHelp(int index);
	
	void hit(const Card& c);
	void printHand();
	int handTotal();
	bool hasAce() { return aced; }
};

//------------------------Player Class.cpp---------------------------------
Player::Player()
{
	clear();
}

Player::~Player(void)
{
}

void Player::clear() {
	for(int i = 0; i <MAXCARDS; i++) {
		hand[i] = Card();
	}
	cardNumber = 0;
	aced = false;
}

void Player::hit(const Card& c) {
	hand[cardNumber++] = c;
	if ( c.face == 1 ) aced = true;
}

void Player::printHand() {

	for(int i = 0; i < cardNumber; i++) {
			cout << hand[i] << ", ";
	}

	int hand = handTotal();


	if ( aced && hand+10 <= BLACKJACK ) hand += 10;

	if(handTotal() == BLACKJACK) {
		cout << "\nTotal: " << hand << ", Blackjack!!" << endl;
	} else if(handTotal() > BLACKJACK) {
		cout << "\nTotal: " << hand << ", Bust!!" << endl;
	} else {
		cout << "\nTotal: " << hand << endl;
	}
}

int Player::handTotal() 
{
	int index = 0;
	return handTotalHelp(index);
}
int Player::handTotalHelp(int index)
{
	//base case: if the index is equal to the number of cards. just return the value of thatcard
	if(index == cardNumber)
	{
		int temp = 0;
			if(hand[index].face > 10 ) {
			temp = 10;
		} else {
			temp = hand[index].face;
		}
			return temp;
	}//if the face value is 10 or higher, return a ten. aces will be calculated later
	if(hand[index].face > 10 ) {
	return 10 + handTotalHelp(index +1);
	} else {//anything else just retrun the face value of that card.
		return hand[index].face + handTotalHelp(index +1);
	}
	
}