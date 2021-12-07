#ifndef ECE309_PROJECT_UNO_H
#define ECE309_PROJECT_UNO_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include "string.h"
#include "time.h"
#include "windows.h"
#include <cstdio>
#include <string>
using namespace std;

class Card {
public:
    int num;
    string color;
    string wColor;
    Card() {
        num = 10;
        color = "default";
    }
};

class Deck {
public:

    vector<Card> cardDeck;
    Deck() {
        for (int i = 0; i < 20; i++) {//19 red cards 1 0 and 2 of 1-9
            Card card;
            card.num = i / 2;
            card.color = "r";
            cardDeck.push_back(card);
        }
        for (int j = 0; j < 20; j++) {
            Card card;
            card.num = j / 2;
            card.color = "b";
            cardDeck.push_back(card);
        }
        for (int k = 0; k < 20; k++) {
            Card card;
            card.num = k / 2;
            card.color = "g";
            cardDeck.push_back(card);
        }
        for (int n = 0; n < 20; n++) {
            Card card;
            card.num = n / 2;
            card.color = "y";
            cardDeck.push_back(card);
        }
        for (int n = 0; n < 5; n++) {
            Card card;
            card.num = 0;
            card.color = "w";
            cardDeck.push_back(card);
        }
        for (int n = 0; n < 5; n++) {
            Card card;
            card.num = 4;
            card.color = "w";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 2;
            card.color = "+r";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 2;
            card.color = "+y";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 2;
            card.color = "+g";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 2;
            card.color = "+b";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Sr";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Sb";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Sg";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Sy";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Rr";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Rb";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Rg";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 2; i++) {
            Card card;
            card.num = 0;
            card.color = "Ry";
            cardDeck.push_back(card);
        }
        random_shuffle(cardDeck.begin(), cardDeck.end());
    }

};

class Player {
public:
    int num;
    bool cpu;
    list<Card> handList;
public:
    virtual void deal() = 0;
    virtual void removeCard(Card inputCard) = 0;
    virtual void pickupCard() = 0;
    virtual bool isLegal(Card playerCard, Card centerCard) = 0;
    virtual bool anyLegalCard(Card centerCard) = 0;
    virtual void print() = 0;
    virtual Card playCard(Card centerCard) = 0;//return card type????
    //virtual void playCard() {}
    //virtual void sortHand() {}//if needed, we can implement later

};

class humPlayer : public Player {
public:
    int num;
    list<Card> handList;
    humPlayer() {
        cpu = false;
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    Card playCard(Card centerCard) override { return centerCard; }//place card from user input
    void deal() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    void pickupCard() {
        int randNum = rand() % 80;
        Deck dealdeck;
        handList.push_back(dealdeck.cardDeck[randNum]);
        cout << endl;
    }
    void removeCard(const Card inputCard) {
        list<Card>::iterator it;

        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == inputCard.num && it->color == inputCard.color) {
                this->handList.erase(it++);
                break;//to only erase first instance
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        cout << endl;
    }

    bool isLegal(Card playerCard, Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        //TWO Wild cases:
        //1. Player plays wild
        if (playerCard.color == "w") {
            legal = true;
            if (playerCard.num == 4) {
                //Draw Four Case
                legal = true;
            }
            return legal;
        }

        //2. Center card is wild
        if (centerCard.color == "w") {
            //wild case
            if (playerCard.color == centerCard.wColor) {
                legal = true;
                return legal;
            }
            if (playerCard.num == 4) {
                //Draw Four Case
                if (playerCard.color == centerCard.wColor) {
                    legal = true;
                    return legal;
                }
            }
        }

        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == playerCard.num && it->color == playerCard.color) {
                legal = true;
                break;
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        if (playerCard.color == "+r" || playerCard.color == "Sr" || playerCard.color == "Rr") playerCard.color = "r";
        else if (playerCard.color == "+b" || playerCard.color == "Sb" || playerCard.color == "Rb") playerCard.color = "b";
        else if (playerCard.color == "+g" || playerCard.color == "Sg" || playerCard.color == "Rg") playerCard.color = "g";
        else if (playerCard.color == "+y" || playerCard.color == "Sy" || playerCard.color == "Ry") playerCard.color = "y";
        if (centerCard.color == "+r" || centerCard.color == "Sr" || centerCard.color == "Rr")centerCard.color = "r";
        else if (centerCard.color == "+b" || centerCard.color == "Sb" || centerCard.color == "Rb")centerCard.color = "b";
        else if (centerCard.color == "+y" || centerCard.color == "Sy" || centerCard.color == "Ry")centerCard.color = "y";
        else if (centerCard.color == "+g" || centerCard.color == "Sg" || centerCard.color == "Rg")centerCard.color = "g";
        if (legal == true) {
            if (playerCard.num == centerCard.num || playerCard.color == centerCard.color) {
                legal = true;
            }
            else legal = false;
        }

        return legal;
    }

    bool anyLegalCard(Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        if (centerCard.color == "+r" || centerCard.color == "Sr")centerCard.color = "r";
        else if (centerCard.color == "+b" || centerCard.color == "Sb")centerCard.color = "b";
        else if (centerCard.color == "+y" || centerCard.color == "Sy")centerCard.color = "y";
        else if (centerCard.color == "+g" || centerCard.color == "Sg")centerCard.color = "g";

        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == centerCard.num || it->color == centerCard.color || it->color == "w") {
                legal = true;
                return true;
                break;
            }
            else if (centerCard.color == "w" && it->color == centerCard.wColor) {
                legal = true;
                return true;
                break;
            }
        }
        return false;
    }

    void print() {
        cout << "Player " << num << "'s Hand: ";
        for (auto v : handList) {
            if (v.color == "r" || v.color[1] == 'r') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "b" || v.color[1] == 'b') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 9);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "g" || v.color[1] == 'g') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "y" || v.color[1] == 'y') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << v.num << v.color << ' ';
            }
            else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << v.num << v.color << ' ';
            }
        }
        cout << endl;
    }//for testing purposes only
};

class cpuPlayer : public Player { //YOU SHOULD ONLY NEED TO CALL PLAYCARD FUNCTION -will
public:
    int num;
    list<Card> handList;
    cpuPlayer() {
        cpu = true;
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    Card playCard(Card centerCard) {
        list<Card>::iterator it;
        Card tmp;
        if (this->anyLegalCard(centerCard)) {
            for (it = this->handList.begin(); it != this->handList.end(); it++) {
                tmp.num = it->num;
                tmp.color = it->color;
                if (isLegal(tmp, centerCard)) {  //checks to see if the car chosen is legal
                    removeCard(tmp);
                    cout << "Played card: " << tmp.num << tmp.color << endl;       //TESTING TEXT
                    cout << endl;
                    if (tmp.color == "w") {
                        int randNum = rand() % 3;
                        switch (randNum) {
                            case 0:
                                tmp.color = "r";
                                break;
                            case 1:
                                tmp.color = "b";
                                break;
                            case 2:
                                tmp.color = "g";
                                break;
                            case 3:
                                tmp.color = "y";
                                break;
                            default:
                                break;
                        }
                    }
                    centerCard = tmp;
                    break;
                }
            }
        }
        else {
            pickupCard();
            cout << "Card picked up." << endl;
            cout << endl;
        }
        return centerCard;
    }
    void deal() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    void pickupCard() {
        int randNum = rand() % 80;
        Deck dealdeck;
        handList.push_back(dealdeck.cardDeck[randNum]);
        cout << endl;
    }
    void removeCard(const Card inputCard) {
        list<Card>::iterator it;
        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == inputCard.num && it->color == inputCard.color) {
                this->handList.erase(it++);
                break;//to only erase first instance
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        cout << endl;
    }

    bool isLegal(Card playerCard, Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        //TWO Wild cases:
        //1. Player plays wild
        if (playerCard.color == "w") {
            legal = true;
            if (playerCard.num == 4) {
                //Draw Four Case
                legal = true;
            }
            return legal;
        }

        //2. Center card is wild
        if (centerCard.color == "w") {
            //wild case
            if (playerCard.color == centerCard.wColor) {
                legal = true;
                return legal;
            }
            if (playerCard.num == 4) {
                //Draw Four Case
                if (playerCard.color == centerCard.wColor) {
                    legal = true;
                    return legal;
                }
            }
        }

        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == playerCard.num && it->color == playerCard.color) {
                legal = true;
                break;
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        if (playerCard.color == "+r" || playerCard.color == "Sr" || playerCard.color == "Rr") playerCard.color = "r";
        else if (playerCard.color == "+b" || playerCard.color == "Sb" || playerCard.color == "Rb") playerCard.color = "b";
        else if (playerCard.color == "+g" || playerCard.color == "Sg" || playerCard.color == "Rg") playerCard.color = "g";
        else if (playerCard.color == "+y" || playerCard.color == "Sy" || playerCard.color == "Ry") playerCard.color = "y";
        if (centerCard.color == "+r" || centerCard.color == "Sr" || centerCard.color == "Rr")centerCard.color = "r";
        else if (centerCard.color == "+b" || centerCard.color == "Sb" || centerCard.color == "Rb")centerCard.color = "b";
        else if (centerCard.color == "+y" || centerCard.color == "Sy" || centerCard.color == "Ry")centerCard.color = "y";
        else if (centerCard.color == "+g" || centerCard.color == "Sg" || centerCard.color == "Rg")centerCard.color = "g";
        if (legal == true) {
            if (playerCard.num == centerCard.num || playerCard.color == centerCard.color) {
                legal = true;
            }
            else legal = false;
        }

        return legal;
    }

    bool anyLegalCard(Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        if (centerCard.color == "+r" || centerCard.color == "Sr")centerCard.color = "r";
        else if (centerCard.color == "+b" || centerCard.color == "Sb")centerCard.color = "b";
        else if (centerCard.color == "+y" || centerCard.color == "Sy")centerCard.color = "y";
        else if (centerCard.color == "+g" || centerCard.color == "Sg")centerCard.color = "g";

        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == centerCard.num || it->color == centerCard.color || it->color == "w") {
                legal = true;
                return true;
                break;
            }
            else if (centerCard.color == "w" && it->color == centerCard.wColor) {
                legal = true;
                return true;
                break;
            }
        }
        return false;
    }

    void print() {
        cout << "Player " << num << "'s Hand: ";
        for (auto v : handList) {
            if (v.color == "r" || v.color[1] == 'r') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "b" || v.color[1] == 'b') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 9);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "g" || v.color[1] == 'g') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "y" || v.color[1] == 'y') {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << v.num << v.color << ' ';
            }
            else {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << v.num << v.color << ' ';
            }
        }
        cout << endl;
    }//for testing purposes only
};


Card convertInput(string Card) {
    //convert user input string to a Card type
    class Card test;
    if (Card[1] == '+' || Card[1] == 'S' || Card[1] == 'R') {
        test.num = stoi(Card);
        test.color = Card.substr(1, 2);
    }
    else {
        test.num = stoi(Card);
        test.color = Card[1];
    }

    return test;
}

int switchPlayer(int numplayers, int pnowNum) {//skip and reverse special cards will be implemented here
    //Player nextPlayer;
    int next;
    if (numplayers == 2) {
        if (pnowNum == 1) next = 2;
        else if (pnowNum == 2) next = 1;
    }
    else if (numplayers == 4) {
        if (pnowNum == 1)next = 2;
        else if (pnowNum == 2) next = 3;
        else if (pnowNum == 3) next = 4;
        else if (pnowNum == 4) next = 1;
    }
    else if (numplayers == 3) {
        if (pnowNum == 1)next = 2;
        else if (pnowNum == 2)next = 3;
        else if (pnowNum == 3) next = 1;
    }

    return next;
}

int RSwitchPlayer(int numplayers, int pnowNum) {
    int next;
    if (numplayers == 2) {
        if (pnowNum == 1) next = 2;
        else if (pnowNum == 2) next = 1;
    }
    else if (numplayers == 4) {
        if (pnowNum == 1)next = 4;
        else if (pnowNum == 2) next = 1;
        else if (pnowNum == 3) next = 2;
        else if (pnowNum == 4) next = 3;
    }
    else if (numplayers == 3) {
        if (pnowNum == 1)next = 3;
        else if (pnowNum == 2)next = 1;
        else if (pnowNum == 3) next = 2;
    }

    return next;
}

void printRules(){
    cout << "Uno is the highly popular card game played by millions around the globe. This game is played by matching and then discarding the cards in one's hand till none are left. Since its inception, there are now many versions of Uno that one can play. Here are the rules of the original or classic Uno.\n"
            "\n"
            "Setup: The game is for 2-10 players, ages 7 and over. Every player starts with seven cards, and they are dealt face down. The rest of the cards are placed in a Draw Pile face down. Next to the pile a space should be designated for a Discard Pile. The top card should be placed in the Discard Pile, and the game begins!\n"
            "\n"
            "Game Play: The first player is normally the player to the left of the dealer (you can also choose the youngest player) and gameplay usually follows a clockwise direction. Every player views his/her cards and tries to match the card in the Discard Pile.\n"
            "\n"
            "You have to match either by the number, color, or the symbol/Action. For instance, if the Discard Pile has a red card that is an 8 you have to place either a red card or a card with an 8 on it. You can also play a Wild card (which can alter current color in play).\n"
            "\n"
            "If the player has no matches or they choose not to play any of their cards even though they might have a match, they must draw a card from the Draw pile. If that card can be played, play it. Otherwise, keep the card, and the game moves on to the next person in turn. You can also play a Wild card, or a Wild Draw Four card on your turn.\n"
            "\n"
            "Note: If the first card turned up from the Draw Pile (to form the Discard Pile) is an Action card, the Action from that card applies and must be carried out by the first player (as stated, it is usually the player to the dealer's left). The exceptions are if a Wild or Wild Draw Four card is turned up.\n"
            "\n"
            "If it is a Wild card, Mattel has now stated that the first player to start (usually the one on the dealer's left), can choose whatever color to begin play. If the first card is a Wild Draw Four card - Return it to the Draw Pile, shuffle the deck, and turn over a new card. At any time during the game, if the Draw Pile becomes depleted and no one has yet won the round, take the Discard Pile, shuffle it, and turn it over to regenerate a new Draw Pile.\n"
            "\n"
            "Take note that you can only put down one card at a time; you cannot stack two or more cards together on the same turn. For example, you cannot put down a Draw Two on top of another Draw Two, or Wild Draw Four during the same turn, or put down two Wild Draw Four cards together.\n"
            "\n"
            "The game continues until a player has one card left. \n"
            "\n"
            "Once a player has no cards remaining, the game round is over, points are scored, and the game begins over again. Normally, everyone tries to be the first one to achieve 500 points, but you can also choose whatever points number to win the game, as long as everyone agrees to it.\n"
            "\n"
            "Action Cards: Besides the number cards, there are several other cards that help mix up the game. These are called Action or Symbol cards.\n"
            "\n"
            "uno action cards\n"
            "\n"
            "Reverse - If going clockwise, switch to counterclockwise or vice versa. It can only be played on a card that matches by color, or on another Reverse card. If turned up at the beginning of play, the dealer goes first, and the player to the dealer's right is next (normally it would be the player to the dealer's left).\n"
            "Skip - When a player places this card, the next player has to skip their turn. It can only be played on a card that matches by color, or on another Skip card. If turned up at the beginning of play, the first player (to the dealer's left) loses his/her turn. The next player to that player's right starts the game instead.\n"
            "Draw Two - When a person places this card, the next player will have to pick up two cards and forfeit his/her turn. It can only be played on a card that matches by color, or on another Draw Two.y\n"
            "Wild - This card represents all four colors, and can be placed on any card. The player has to state which color it will represent for the next player. It can be played regardless of whether another card is available. If turned up at the beginning of play, the first player chooses what color to continue play.\n"
            "Wild Draw Four - This acts just like the wild card except that the next player also has to draw four cards as well as forfeit his/her turn. \n"
             << endl;
    return;
}

#endif //ECE309_PROJECT_UNO_H