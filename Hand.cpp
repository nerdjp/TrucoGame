#include "Hand.h"

Hand::Hand(int playerNum, std::vector<Card> Cards) : playerNum(playerNum)
{
	refresh(Cards);
}

void Hand::refresh(std::vector<Card> newCards)
{
	Cards = newCards;
	for (auto& card : Cards) {
		card.player = playerNum;
	}
}
