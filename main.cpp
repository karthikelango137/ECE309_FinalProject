#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include "string.h"
using namespace std;

class Card{
public:
    int num;
    string color;
    Card(){
        num = 10;
        color = "default";
    }
};

class Deck{
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
        random_shuffle(cardDeck.begin(),cardDeck.end());
    }
/*
    void shuffle(){
       for(int i = 0; i < rand(); i++){
           random_shuffle(cardDeck.begin(),cardDeck.end());
       }
    }//function to shuffle deck and we take first 7 or top to put in a hand instead of randomizing
*/
    void print(){
        for(int i = 0; i < cardDeck.size(); i++){
            cout << cardDeck[i].num << cardDeck[i].color << ' ';
        }
        cout << endl;
    }//for testing purposes only
};
/*
class hand{
    list<Card> handList;

};
*/
class Player{
public:
    int num;
    list<Card> handList;
public:
    virtual void displayHand(){}
    virtual void pickupCard(){}//return card type????
    virtual void playCard(){}
    virtual void sortHand(){}//if needed, we can implement later
    virtual void deal(){};
};

class humPlayer : public Player{
public:
    int num;
    list<Card> handList;
    humPlayer(){
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    void playCard() override{}//place card from user input
    void deal() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    void removeCard(const Card inputCard){
        list<Card>::iterator it;
        for(it = this->handList.begin(); it != this->handList.end();it++){
            if(it->num == inputCard.num && it->color == inputCard.color) {
                this->handList.erase(it++);
                break;//to only erase first instance
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }
        cout << endl;
    }

    bool isLegal(Card playerCard, Card centerCard){
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        for(it = this->handList.begin(); it != this->handList.end();it++){
            if(it->num == playerCard.num && it->color == playerCard.color) {
                legal = true;
                break;
            }
            //cout << "iterator: " << it->num << it->color << ' ';
        }

        if(legal == true){
            if(playerCard.num == centerCard.num || playerCard.color == centerCard.color){
                legal = true;
            }
            else legal = false;
        }

        return legal;
    }
    void print(){
        for (auto v : handList){
            std::cout << v.num << v.color << ' ';
        }
        cout << endl;
    }//for testing purposes only
};

class cpuPlayer : public Player{
    // no display hand
    void playCard() override{}//place random card for now
    void pickupCard() override{}//pickup top card of deck. should be same for humPlayer

};

Card convertInput(string Card){
    //convert user input string to a Card type
    class Card test;
    test.num = stoi(Card);
    test.color = Card[1];
    cout << "converted: " << test.num << test.color << endl;
    return test;
}

int switchPlayer(int numplayers, Player pnow){//skip and reverse special cards will be implemented here
    //Player nextPlayer;
    int next;
    if(numplayers==2){
        if(pnow.num == 1) next = 2;
        else if (pnow.num = 2) next = 1;
    }
    else if(numplayers==4){
        if(pnow.num == 1)next = 2;
        else if (pnow.num == 2) next = 3;
        else if (pnow.num == 3) next = 4;
        else if (pnow.num == 4) next = 1;
    }
    else if (numplayers == 3){
        if(pnow.num == 1)next = 2;
        else if (pnow.num == 2)next = 3;
        else if (pnow.num == 3) next = 1;
    }

    return next;
}

int main() {
    Deck fullDeck;
    fullDeck.print();
    humPlayer p1;
    p1.num = 1;
    p1.print();
    humPlayer p2;
    p2.num = 2;
    p2.print();

    int numPlayers = 2;

    int randNum = rand()%80;
    Card centerCard = fullDeck.cardDeck[randNum];
    cout << "Card to Play: " << centerCard.num << centerCard.color << endl ;
    cout << "Your Turn, Play a Card: ";
    string  inputCard;
    cin >> inputCard;
    Card cardtoRemove = convertInput(inputCard);
    bool legal = p1.isLegal(cardtoRemove,centerCard);
    if(legal){
        p1.removeCard(cardtoRemove);
    }
    else{
        cout <<"ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" <<endl;
    }
    int nextNum = switchPlayer(numPlayers, p1);
    p1.print();


    return 0;
}
