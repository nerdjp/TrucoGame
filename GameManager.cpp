#include "GameManager.h"

GameManager::GameManager(int numOfPlayers)
{
    //scoreFile.open("scores.txt", );
    if(scoreFile)

    Shuffle();

    setPlayers(numOfPlayers);

}

void GameManager::Shuffle()
{

    /* Clears the deck and all players hands, refills the deck with all the cards and shuffles it*/

    Hands.clear();

    Deck.clear();

    for (size_t i = 1; i <= 6; i++) {

        for (size_t j = 1; j <= 11; j++) {

            if (j < 5 && i == 1) {
                Deck.push_back({ static_cast<int>(j), 7 });

            }
            else if (j == 5 && i > 4) {
                Deck.push_back({ static_cast<int>(j), static_cast<int>(i) });

            }
            else if (j > 5 && i <= 4) {
                Deck.push_back({ static_cast<int>(j), static_cast<int>(i) });

            }
        }
    }

    srand(time(NULL));
    std::random_shuffle(Deck.begin(), Deck.end());

}

std::string GameManager::getCardName(Card cardId) const
{

    /* Return the card name based on card Id and Naipe Id */

    std::string cardName;
    switch (cardId.id) {
    case 1:
        return "4 de Paus";
        break;
    case 2:
        return "7 de Copas";
        break;
    case 3:
        return "As de Espadas";
        break;
    case 4:
        return "7 de Ouros";
        break;
    case 5:
        cardName.append("Coringa");
        break;
    case 6:
        cardName.append("3");
        break;
    case 7:
        cardName.append("2");
        break;
    case 8:
        cardName.append("As");
        break;
    case 9:
        cardName.append("Rei");
        break;
    case 10:
        cardName.append("Valete");
        break;
    case 11:
        cardName.append("Dama");
        break;
    default:
        break;
    }

    switch (cardId.naipe)
    {
    case 1:
        cardName.append(" de Espadas");
        break;
    case 2:
        cardName.append(" de Copas");
        break;
    case 3:
        cardName.append(" de Paus");
        break;
    case 4:
        cardName.append(" de Ouros");
        break;
    case 5:
        cardName.append(" Preto");
        break;
    case 6:
        cardName.append(" Vermelho");
        break;
    default:
        break;
    }

    return cardName;
}

std::vector<Card> GameManager::getCards()
{
    std::vector<Card> tempCard;
    for (size_t i = 0; i < 3; i++) {
        tempCard.push_back(Deck.back());
        Deck.pop_back();
    }
    return tempCard;
}

void GameManager::removeCard(int i, std::vector<Card> &playersCards)
{

    std::vector<Card> tempCards;
    Card pCard = playersCards.at(i - 1);

    //newCard.id != playersCards.at(i - 1).id && newCard.naipe != playersCards.at(i - 1).naipe

    for (auto& newCard : getHands().at(i - 1).getCards()) {
        if (!isCardsEquals(newCard, pCard)) {
            tempCards.push_back(newCard);
        }
    }
    Hands.at(i - 1).setCards(tempCards);
}

void GameManager::setPlayers(int numOfPlayers)
{
    for (size_t i = 1; i <= numOfPlayers; i++) {
        Hands.push_back({ static_cast<int>(i), getCards() });
    }
}

Card GameManager::selectCard(int player, int card)
{
    if (card >= 1 && card < 4)
        return getHands().at(1).getCards().at(card - 1);
    else {
        std::cout << "Numero Invalido";
    }
    
}

Card GameManager::compareCards(Card c1, Card c2)
{
    if (c1 == c2) {
        return Empate;
    }
    else if (c1 < c2) {
        return c1;
    }
    else {
        return c2;
    }
}

Card GameManager::compareCards(Card c1, Card c2, Card c3, Card c4)
{
    return compareCards (compareCards(c1, c2), compareCards(c3, c4));
}

void GameManager::increaseScore(int team, MODE currentMode)
{
    if (team != 0) {
        if (team <= 4) {
            if (team % 2 == 0) {
                switch (currentMode) {
                case MODE::Normal:
                    scores.second += 1;
                    break;
                case MODE::Truco:
                    scores.second += 3;
                    break;
                case MODE::Seis:
                    scores.second += 6;
                    break;
                case MODE::Nove:
                    scores.second += 9;
                    break;
                case MODE::Doze:
                    scores.second += 12;
                    break;
                case MODE::Corri:
                    scores.first += 1;
                    break;
                }
            }
            else {
                switch (currentMode) {
                case MODE::Normal:
                    scores.first += 1;
                    break;
                case MODE::Truco:
                    scores.first += 3;
                    break;
                case MODE::Seis:
                    scores.first += 6;
                    break;
                case MODE::Nove:
                    scores.first += 9;
                    break;
                case MODE::Doze:
                    scores.first += 12;
                    break;
                case MODE::Corri:
                    scores.second += 1;
                    break;
                }
            }
        }
    }
}

void GameManager::displayCards(int player)
{
    int index = 1;
    for (auto& card : Hands.at(player - 1).getCards()) {
        std::cout << index << ": " << getCardName(card) << std::endl;
        index++;
    }
}

void GameManager::resetGame()
{
    Shuffle();
    setPlayers(4);
    setNormal();
}

bool GameManager::aceitaTruco(int playerTrucou, int& player)
{
    int anwser;
    if (playerTrucou <= 4) {
        player = 1;
        while (player < playerTrucou) {
            cleanScreen();
            std::cout << "Player " << player << " confirm" << std::endl;
            pauseScreen();

            switch (mode) {
            case MODE::Truco:
                std::cout << "The player " << playerTrucou << " trucou, player " << player << " do you wish to continue? " << std::endl;
                break;
            case MODE::Seis:
                std::cout << "The player " << playerTrucou << " raised to six, player " << player << " do you wish to continue? " << std::endl;
                break;
            case MODE::Nove:
                std::cout << "The player " << playerTrucou << " raised to nine, player " << player << " do you wish to continue? " << std::endl;
                break;
            case MODE::Doze:
                std::cout << "The player " << playerTrucou << " raised to twelve, player " << player << " do you wish to continue? " << std::endl;
                break;
            }
            std::cout << "1: Yes. " << std::endl;
            std::cout << "2: No. " << std::endl;
            std::cin >> anwser;
            if (anwser == 1) {
                player = playerTrucou;
                return true;
            }
            else {
                player = playerTrucou;
                return false;
            }
            player++;
        }
    }
}

void GameManager::cleanScreen() {
    system("cls||clear");
}

void GameManager::pauseScreen() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool GameManager::isCardsEquals(Card c1, Card c2)
{
    if (c1.id == c2.id && c1.naipe == c2.naipe) {
        return true;
    }
    else {
        return false;
    }
    return false;
}
