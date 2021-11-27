//#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include "string.h"
#include "time.h"
#include "stdlib.h"
#include "windows.h"
#include <cstdio>
using namespace std;

class Card {
public:
    int num;
    string color;
    Card() {
        num = 10;
        color = "r";
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
        for(int i = 0; i < 2; i++){
            Card card;
            card.num = 2;
            card.color = "+r";
            cardDeck.push_back(card);
        }
        for(int i = 0; i < 2; i++){
            Card card;
            card.num = 2;
            card.color = "+y";
            cardDeck.push_back(card);
        }
        for(int i = 0; i < 2; i++){
            Card card;
            card.num = 2;
            card.color = "+g";
            cardDeck.push_back(card);
        }
        for(int i = 0; i < 2; i++){
            Card card;
            card.num = 2;
            card.color = "+b";
            cardDeck.push_back(card);
        }
        random_shuffle(cardDeck.begin(), cardDeck.end());
    }

    void print() {
        for (int i = 0; i < cardDeck.size(); i++) {
            cout << cardDeck[i].num << cardDeck[i].color << ' ';
        }
        cout << endl;
    }
};

class Player {
public:
    int num;
    list<Card> handList;
public:
    virtual void displayHand() {}
    virtual void pickupCard() {}//return card type????
    virtual void playCard() {}
    virtual void sortHand() {}//if needed, we can implement later
    virtual void deal() {};
};

class humPlayer : public Player {
public:
    int num;
    list<Card> handList;
    humPlayer() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    void playCard() override {}//place card from user input
    void deal() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for (int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    void pickupCard() {
        int randNum = rand() % 88;
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
        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == playerCard.num && it->color == playerCard.color) {
                legal = true;
                break;
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        if(centerCard.color == "+r")centerCard.color = "r";
        else if(centerCard.color == "+b")centerCard.color = "b";
        else if(centerCard.color == "+y")centerCard.color = "y";
        else if(centerCard.color == "+g")centerCard.color = "g";

        if(playerCard.color == "+r")playerCard.color = "r";
        else if(playerCard.color == "+b")playerCard.color = "b";
        else if(playerCard.color == "+y")playerCard.color = "y";
        else if(playerCard.color == "+g")playerCard.color = "g";

        if (legal == true) {
            if (playerCard.num == centerCard.num || playerCard.color == centerCard.color) {
                legal = true;
            }
            else legal = false;
        }

        return legal;
    }

    bool anyLegalCard( Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if(it->color == "+r")it->color == "r";
            else if (it->color == "+b")it->color == "b";
            else if (it->color == "+g")it->color == "g";
            else if (it->color == "+y")it->color == "y";
            if (it->num == centerCard.num || it->color == centerCard.color) {
                legal = true;
                return true;
                break;
            }
        }
        return false;
    }

    void drawTwo(Card inputCard){

    }
    void print() {
        cout << "Player " << num << "'s Hand: ";
        for (auto v : handList) {
            if(v.color == "r" || v.color == "+r"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,12);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "b" || v.color == "+b"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,9);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "g"|| v.color == "+g"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,10);
                std::cout << v.num << v.color << ' ';
            }
            else if (v.color == "y"|| v.color == "+y"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,14);
                std::cout << v.num << v.color << ' ';
            }
            else std::cout << v.num << v.color << ' ';
        }
        cout << endl;
    }//for testing purposes only
};

class cpuPlayer : public Player {
    // no display hand
    void playCard() override {}//place random card for now
    void pickupCard() override {}//pickup top card of deck. should be same for humPlayer

};

Card convertInput(string Card) {
    //convert user input string to a Card type
    class Card test;
    if(Card[1] != '+'){
        test.num = stoi(Card);
        test.color = Card[1];
    }
    else{
        test.num = stoi(Card);
        test.color = Card.substr(1,2);
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

int main() {
    srand(time(NULL));
    Deck fullDeck;
    humPlayer p1;
    p1.num = 1;
    humPlayer p2;
    p2.num = 2;
    humPlayer p3;
    p3.num = 3;
    humPlayer p4;
    p4.num = 4;
    int nextNum = 0;
    int numPlayers = 4;
    humPlayer pNow;
    pNow = p1;
    bool end = false;
    bool drawTwo;

    int randNum = rand() % 88;
    Card centerCard = fullDeck.cardDeck[randNum];
    //system("Color 1B");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,15);
    cout <<  "Welcome to UNO!" << endl << "You may type end at any point as your card to end the game." << endl << endl;
    string inputCard;
    //begin the main while loop
    while (!end) {

        //prompts for user
        bool promptAgain = true;
        //drawTwo = false;
        while (promptAgain) {
            cout << "Card to Play: ";
            if(centerCard.color == "r" || centerCard.color == "+r"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,12);
                std::cout << centerCard.num << centerCard.color << ' ';
            }
            else if (centerCard.color == "b"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,9);
                std::cout << centerCard.num << centerCard.color << ' ';
            }
            else if (centerCard.color == "g"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,10);
                std::cout << centerCard.num << centerCard.color << ' ';
            }
            else if (centerCard.color == "y"){
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,14);
                std::cout << centerCard.num << centerCard.color << ' ';
            }
            cout << endl;
            SetConsoleTextAttribute(hConsole,15);
            pNow.print();
            SetConsoleTextAttribute(hConsole,15);
            if (pNow.anyLegalCard(centerCard))
                cout << "Your Turn, Play or Pickup a Card: ";
            else
                cout << "You have no playable cards. You can pickup a card by typing 'pickup'" << endl;
            //input the card if you can play any card
            cin >> inputCard;
            //begin main nested if statement
            cout <<"322 OUTPUTCARD: "<<inputCard[1]<<endl;
            if (inputCard == "pickup") {				//pickup case
                pNow.pickupCard();
                promptAgain = false;
            }
            else if (inputCard[1] == '+'){
                Card temp = convertInput(inputCard);
                bool legal = pNow.isLegal(temp, centerCard);
                if(legal){
                    drawTwo = true;
                    Card cardtoRemove = convertInput(inputCard);
                    pNow.removeCard(cardtoRemove);//remove the card
                    centerCard = cardtoRemove;//update the ceneter card
                    //we don't need to prompt this user for more info
                    promptAgain = false;
                }
                else{
                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD-------" << endl;
                    promptAgain = true;
                }
            }
            else if (inputCard == "end") {				//end case
                cout << "The game has been quit." << endl;
                end = true;
                break;

                //else assume that it's a card
            }else {										//card case
                Card cardtoRemove = convertInput(inputCard);
                bool legal = pNow.isLegal(cardtoRemove, centerCard);
                if (legal) {//if the card is a legal card to be played
                    pNow.removeCard(cardtoRemove);//remove the card
                    centerCard = cardtoRemove;//update the ceneter card
                    //we don't need to prompt this user for more info
                    promptAgain = false;
                }
                else {//catch-all case, illagal move or unexpected input
                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                    promptAgain = true;
                }
            }
        }
        //win case
        //will need to add option to play again and restart the game
        if (pNow.handList.empty() == true) {
            cout << "Player " << pNow.num << "has won!" << endl;
            //end game
            return 0;
        }

        if (pNow.num == 1) {
            p1 = pNow;
            p1.num = 1;
        }
        else if (pNow.num == 2) {
            p2 = pNow;
            p2.num = 2;
        }
        else if (pNow.num == 3) {
            p3 = pNow;
            p3.num = 3;
        }
        else if (pNow.num == 4) {
            p4 = pNow;
            p4.num = 4;
        }

        //switch players for while loop
        if(drawTwo){
            nextNum = switchPlayer(numPlayers, pNow.num);
            if (nextNum == 1)
                pNow = p1;
            else if (nextNum == 2)
                pNow = p2;
            else if (nextNum == 3)
                pNow = p3;
            else if (nextNum == 4)
                pNow = p4;
            pNow.pickupCard();
            pNow.pickupCard();
            nextNum = switchPlayer(numPlayers, pNow.num);
            if (nextNum == 1)
                pNow = p1;
            else if (nextNum == 2)
                pNow = p2;
            else if (nextNum == 3)
                pNow = p3;
            else if (nextNum == 4)
                pNow = p4;
            drawTwo = false;
        }
        else{
            nextNum = switchPlayer(numPlayers, pNow.num);
            if (nextNum == 1)
                pNow = p1;
            else if (nextNum == 2)
                pNow = p2;
            else if (nextNum == 3)
                pNow = p3;
            else if (nextNum == 4)
                pNow = p4;
        }

    }

    return 0;
}