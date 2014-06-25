#pragma once

#include <ostream>

using namespace std;

struct Card
{
	int face;
	int suit;
	bool used;

	Card* use()
	{
		if ( used == false )
		{
			used = true;
			return this;
		}

		else return nullptr;
	}

	friend std::ostream& operator<<( std::ostream& os, const Card& c )
	{

		char suits[] = {'S','H','C','D'};
		char faces[] = {'A','2','3','4','5','6','7','8','9','0','J','Q','K'};

		if ( faces[c.face-1] == '0' ) os << '1';
		os << faces[c.face-1];
		os << " ";
		os << suits[c.suit];

		return os;
	}

	Card()
		: face(0), suit(0), used(0)
	{}

	Card(int face, int suit)
		: face(face), suit(suit), used(false)
	{}

	Card(Card& cd)
		: suit(cd.suit), face(cd.face), used(false)
	{}

	~Card(void)
	{}
};

