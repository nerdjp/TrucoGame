#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <time.h>
#include <fstream>
#include "Hand.h"
#include "Card.h"

enum class MODE { Normal, Truco, Seis, Nove, Doze, Corri};

class GameManager {

private:

	std::vector<Hand> Hands;
	std::vector<Card> Deck;
	Card Empate{0, 0};
	int round;
	std::pair<int, int> scores{	0, 0 };
	MODE mode = MODE::Normal;
	std::fstream scoreFile;
	
public:

	MODE currentMode() const { return mode; };
	void setNormal() { mode = MODE::Normal; };
	void setTruco() { mode = MODE::Truco; };
	void setSeis() { mode = MODE::Seis; };
	void setNove() { mode = MODE::Nove; };
	void setDoze() { mode = MODE::Doze; };
	void setRun() { mode = MODE::Corri; };
	GameManager(int numOfPlayers);
	void Shuffle();
	std::string getCardName(Card cardId) const;
	std::vector<Card> getCards();
	std::vector<Card> getDeck() const { return Deck; };
	std::vector<Hand> &getHands() { return Hands; };
	std::pair<int, int> getScore() const { return scores; };
	void removeCard(int i, std::vector<Card> &playersCards);
	void setPlayers(int numOfPlayers);
	Card selectCard(int player, int card);
	Card compareCards(Card c1, Card c2);
	Card compareCards(Card c1, Card c2, Card c3, Card c4);
	void increaseScore(int team, MODE currentMode);
	void displayCards(int player);
	void resetGame();
	bool aceitaTruco(int playerTrucou, int &player);
	void cleanScreen();
	void pauseScreen();
	bool isCardsEquals(Card c1, Card c2);
};