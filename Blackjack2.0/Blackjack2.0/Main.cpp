#include"Dealer.h"
#include"Deck.h"
#include"Player.h"
#include "Probability.h"
#include<string>

//globsl constants
const int DECKSIZE = 52;
const int BLACKJACK = 21;
const int DEALERMIN = 17;

int main() {

	//class objects
	Deck deck;
	Player player;
	Dealer dealer;
	Probability prob(deck);

	//variables for program loop
	string rerun = "";
	bool retry = true;
	bool again = true;

	while(retry) {
		try{
			retry = false;

			//outcome variables
			bool lose = false;
			bool dealerLose = false;
			bool push = false;
		
			//clear the deck
			//deck.clearDeck();
			player.clear();
			dealer.clear();

			//player and dealer are dealt twice
			player.hit(deck.hit());
			player.hit(deck.hit());
			dealer.hit(deck.hit());
			dealer.hit(deck.hit());

			cout << "Your Hand: ";
			player.printHand();
			if ( player.handTotal() < BLACKJACK ) prob.printProb(player);
			cout << endl;

			cout << "Dealer's Hand: ";
			dealer.printHand();
			if ( dealer.handTotal() < DEALERMIN ) prob.printProb(dealer);
			cout << endl;

			//ask player to hit
			do {
				cin.clear();
				//if total is 21, break for asking to hit
				if(player.handTotal() >= BLACKJACK || (player.hasAce() && player.handTotal()+10 == BLACKJACK) ) {
					break;
				}

				cout << "Would you like to hit? (y/n)";
				cin >> choice;
				system("CLS");

				//if yes, hit and show new total
				if(choice == 'y'|| choice == 'Y') {
					player.hit(deck.hit());

					cout << "Your Hand: ";
					player.printHand();
					if ( player.handTotal() < BLACKJACK ) prob.printProb(player);
					cout << endl;


					if(player.handTotal() != BLACKJACK) {
						cout << "Dealer's Hand: ";
						dealer.printHand();
						if ( dealer.handTotal() < DEALERMIN ) prob.printProb(dealer);
						cout << endl;
					}
				//if no, don't ask again
				} else if(choice == 'n') {
					break;
				//if input is not "y" or "n", ask again
				} else {
					cout << "Your Hand: ";
					player.printHand();
					if ( player.handTotal() < BLACKJACK ) prob.printProb(player);
					cout << endl;

					cout << "Dealer's Hand: ";
					dealer.printHand();
					if ( dealer.handTotal() < DEALERMIN ) prob.printProb(dealer);
					cout << endl;
				}
			//not sure, but it does what I want it
			} while(!player.handTotal() <= BLACKJACK);
		
			//if the player hasn't bust, dealer hits until >= 17
			if(player.handTotal() <= BLACKJACK) {
				while(dealer.handTotal() < DEALERMIN) {
					system("CLS");
					cout << "Your Hand: ";
					player.printHand();
					cout << endl;
				
					dealer.hit(deck.hit());
					cout << "Dealer's Hand: ";
					dealer.printHand();
					cout << endl;
					system("PAUSE");
				}
			}

			int pHand = player.handTotal();
			int dHand = dealer.handTotal();

			if ( player.hasAce() && pHand+10 <= BLACKJACK ) pHand +=10;

			//determine winner
			if(player.handTotal() > BLACKJACK) {
				lose = true;
			} else if(dealer.handTotal() > BLACKJACK) {
				dealerLose = true;
			} else if(player.handTotal() == dealer.handTotal()) {
				push = true;
			} else if(player.handTotal() > dealer.handTotal()) {
				dealerLose = true;
			} else {
				lose = true;
			}

			//output results 
			if(lose) {
				cout << "\nYOU LOSE, you loser!" << endl;
			} else if(push) {
				cout << "\nPUSH, don't push me over the edge baby!" << endl;
			} else {
				cout << "\nYOU WIN, winner winner, chicken dinner!" << endl;
			}

			//play again?
			again = true;
			while(again) {
				again = false;

				cout << "Would you like play again? (y/n)"<< endl;
				cin >> rerun;
				if(rerun == "y") {
					system("CLS");
					retry = true;
					continue;
				} else if(rerun == "n") {
					cout << endl;
					cout << "Goodbye." << endl;
					system("Pause");
					return 0;
				} else {
					cout << "\nInvalid input." << endl;
					system("Pause");
					system("CLS");
					again = true;
					continue;
				}
			system("PAUSE");
			}
		} catch ( string s ){

			cout << s << endl << endl;
			
			char response;
			bool repeat = true;

			do{
				cout << "Would you like to shuffle and start again? (y/n)";

				cin >> response;
				cin.clear();

				if ( response == 'y' || response == 'Y' ) {
					repeat = false;
					deck.clear();
					retry = true;
				} else if ( response == 'n' || response =='N' ){
					cout << "goodbye";
					system ("CLS");
					system ("PAuSE");
					repeat = false;
					return 0;
				}

				system("CLS");
			} while ( repeat );
		}
	}
}
