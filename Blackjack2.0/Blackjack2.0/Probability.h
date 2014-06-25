#pragma once
#include "Player.h"
#include "Deck.h"
#include <iomanip>

class Probability
{
private:
	const static int DECKSIZE = 52;
	const static int BLACKJACK = 21;

	Deck& deck;

	double pStay;
	double pBlackJ;
	double pBust;

public:
	Probability ( Deck& deck )
		: deck(deck)
	{}

	void calc( Player& player )
	{
		int cardsLeft = DECKSIZE - deck.getCardsUsed();

		int difference = BLACKJACK - player.handTotal();
		bool hasAce = player.hasAce();

		int stay = 0;
		int BJ = 0 ;
		int bust = 0 ;

		for ( int i=0; i<DECKSIZE; i++ )
		{
			if ( !deck.isCardUsed(i) )
			{
				if ( deck.getCardValue(i) == difference ) BJ++;
				else if ( hasAce && deck.getCardValue(i)+10 == difference ) BJ++;
				else if ( deck.getCardValue(i) < difference ) stay++;
				else bust++;
			}
		}

		pStay = (double)stay/(double)cardsLeft;
		pBlackJ = (double)BJ/(double)cardsLeft;
		pBust = (double)bust/(double)cardsLeft;
		
	}

	double stay() { return pStay; }
	double blackJack() { return pBlackJ; }
	double bust() { return pBust; }

	void printProb( Player& player)
	{
		calc(player);

		std::cout << std::setprecision(2) << std::fixed;

		std::cout << "probabilities: \n";
		std::cout << "Black Jack: " << pBlackJ << " Stay: " << pStay << " Bust: " << pBust << endl;
	}
};

