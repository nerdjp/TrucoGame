#include <iostream>
#include <string>
#include <vector>
#include "GameManager.h"

void mainMenu() {
	std::cout << "========== Truco ==========" << std::endl
			  << "P - Play!" << std::endl
			  << "Q - Quit" << std::endl;
}

void cleanScreen() {
	system("cls||clear");
}

void pauseScreen() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	char c;
	std::cout << "press C to continue." << std::endl;
	do {
		std::cin >> c;
	} while (toupper(c) != 'C');
}

void pickACard(GameManager &gm, std::vector<Card>& playersCards, int player, int& card) {
	while (true) {
		try {
			playersCards.push_back(gm.getHands().at(player - 1).getCards().at(card - 1));
			gm.removeCard(player, playersCards);
			break;
		}
		catch (const std::out_of_range &e) {
			std::cout << std::endl << "Invalid option, try again" << std::endl;
			std::cin >> card;
		}
	}
	return;
}

void play() {
	system("cls||clear");
	GameManager gm{ 4 };

	int card;
	int winner;
	int runner{};
	bool truco{false};
	int trucoPlayer{};
	std::vector<Card> playersCards;

	std::cout << "How many players? " << std::endl << "1: Two Players" << std::endl << "2: Four Players" << std::endl;
	int players;
	std::cin >> players;
	if(players == 2) {
		std::cout << "The teams are 1 & 3 and 2 & 4! " << std::endl;
		pauseScreen();
	}
	players *= 2;

	while (gm.getScore().first < 12 && gm.getScore().second < 12) {

		cleanScreen();
		
		srand(time(NULL));

		for (size_t i{ 1 }; i <= players; i++) {

			if (i == trucoPlayer) {
				i++;
			}

			cleanScreen();

			std::cout << "Player " << i << ", " << std::endl;
			pauseScreen();
		

			gm.displayCards(i);
			switch (gm.currentMode()) {
			case MODE::Normal:
				std::cout << "4: TRUCO!" << std::endl;
				break;
			case MODE::Truco:
				std::cout << "4: SEIS!" << std::endl << "5: DESCE!" << std::endl << "6: Corre." << std::endl;
				break;		  							 							 
			case MODE::Seis:  							 							 
				std::cout << "4: NOVE!" << std::endl << "5: DESCE!" << std::endl << "6: Corre." << std::endl;
				break;		  							 							 
			case MODE::Nove:  							 							 
				std::cout << "4: DOZE!" << std::endl << "5: DESCE!" << std::endl << "6: Corre." << std::endl;
				break;
			case MODE::Doze:
				std::cout << "4: -/- " << std::endl << "5: DESCE!" << std::endl << "6: Corre." << std::endl;
				break;
			}

			std::cout << "Choose a card to play: ";
			std::cin >> card;

			if (gm.currentMode() == MODE::Normal) {
				switch (card) {
				case 1:
				case 2:
				case 3:
					pickACard(gm, playersCards, i, card);
					break;
				case 4:
					gm.setTruco();
					std::cout << "Mark a card to play: ";
					std::cin >> card;
					pickACard(gm, playersCards, i, card);
					if (!gm.aceitaTruco(players, players)) {
						gm.setRun();
						runner = players;
					}
					break;
				}
			}
			else {
				bool repeat = false;
				do{
					repeat = false;
					switch (card) {
					case 4:
						switch (gm.currentMode()) {
						case MODE::Normal:
							gm.setTruco();
							break;
						case MODE::Truco:
							gm.setSeis();
							std::cout << "Mark a card to play: ";
							std::cin >> card;
							if (card <= 3) {
								playersCards.push_back(gm.getHands().at(i - 1).getCards().at(card - 1));
								gm.removeCard(i, playersCards);
							}
							else {
								std::cout << "Invalid Option. " << std::endl;
								break;
							}
							break;
						case MODE::Seis:
							gm.setNove();
							std::cout << "Mark a card to play: ";
							std::cin >> card;
							if (card <= 3) {
								playersCards.push_back(gm.getHands().at(i - 1).getCards().at(card - 1));
								gm.removeCard(i, playersCards);
							}
							else {
								std::cout << "Invalid Option. " << std::endl;
								break;
							}
							break;
						case MODE::Nove:
							gm.setDoze();
							std::cout << "Mark a card to play: ";
							std::cin >> card;
							if (card <= 3) {
								playersCards.push_back(gm.getHands().at(i - 1).getCards().at(card - 1));
								gm.removeCard(i, playersCards);
							}
							else {
								std::cout << "Invalid Option. " << std::endl;
								break;
							}
							break;
						case MODE::Doze:
							std::cout << "Invalid Option, Try again. " << std::endl;
							std::cin >> card;
							break;
						default:
							break;
						}
						if (gm.aceitaTruco(players, players)) {
							gm.setRun();
						}
						break;
					case 5:
						gm.displayCards(i);
						std::cout << "Mark a card to play: ";
						std::cin >> card;
						if (card <= 3) {
							pickACard(gm, playersCards, i, card);
						}
						else {
							std::cout << "Invalid Option. " << std::endl;
							break;
						}
						break;
					case 6:
						runner = players;
						gm.setRun();
						break;

					default:
						std::cout << "Please select a response. " << std::endl;
						std::cin >> card;
						repeat = true;
						break;
					}
				} while (repeat);
			}
		}

		if (gm.currentMode() != MODE::Corri) {
			if (players == 2) {
				winner = gm.compareCards(playersCards.at(0), playersCards.at(1)).player;
			}
			else {
				winner = gm.compareCards(playersCards.at(0), playersCards.at(1), playersCards.at(2), playersCards.at(3)).player;
			}
			cleanScreen();

			if (winner != 0) {
				std::cout << "Winner of the round is the player " << winner << "!" << std::endl;
			}
			else {
				std::cout << "That's a draw! No points won" << std::endl;
			}
		}
		else {
			cleanScreen();
			winner = runner;
			std::cout << winner << " ran away! " << std::endl;
		}

		gm.increaseScore(winner, gm.currentMode());

		std::cout << "Team 1 has " << gm.getScore().first << " point(s). Team 2 has " << gm.getScore().second << "!\n";

		playersCards.clear();

		if (gm.getHands().at(0).getCards().empty() || gm.currentMode() != MODE::Normal) {
			gm.resetGame();
		}
		pauseScreen();
	}

	std::cout << "Thanks for playing!" << std::endl;

}

int main()
{
	
	char choice;
	
	do{
		mainMenu();


		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch (toupper(choice)) {
		case 'P':
			play();
			choice = ' ';
			break;
		case 'Q':
			break;
		}
	} while (toupper(choice) != 'Q');
	return 0;
}
