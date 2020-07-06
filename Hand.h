#pragma once
#include <vector>
#include "Card.h"

class Hand {

private:

	std::vector<Card> Cards;
	int playerNum;
	int team;

public:

	Hand(int playerNum, std::vector<Card> Cards);
	void clear() { Cards.clear(); };
	void refresh(std::vector<Card> newCards);
	std::vector<Card> getCards() { return Cards; };
	void clearCards() { Cards.clear(); };
	void setCards(std::vector<Card>& newCards) { Cards = newCards; };

};