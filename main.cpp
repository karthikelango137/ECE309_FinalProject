#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
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
        for (int i = 0; i < 20; i++) {
            Card card;
            card.num = i / 2;
            card.color = "b";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 20; i++) {
            Card card;
            card.num = i / 2;
            card.color = "g";
            cardDeck.push_back(card);
        }
        for (int i = 0; i < 20; i++) {
            Card card;
            card.num = i / 2;
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
    list<Card> handList;
    humPlayer(){
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    void playCard() override{}//place card from user input
    void deal(){
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    //void removeCard(Card inputCard){
    //    handList.remove(inputCard);
   // }

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
    class Card test;/*
    test.num = stoi(Card);
    test.color = Card[1];
    cout << "converted: " << test.num << test.color << endl;*/
    return test;
}

bool isLegal(int playerNum, string playerColor, int centerNum, string centerColor){
    return false;
}

int main() {
    Deck fullDeck;
    fullDeck.print();
    humPlayer p1;
    p1.print();
    humPlayer p2;
    p2.print();

    int randNum = rand()%80;
    cout << "Card to Play: " << fullDeck.cardDeck[randNum].num << fullDeck.cardDeck[randNum].color << endl ;
    cout << "Your Turn: ";
    string  inputCard;
    cin >> inputCard;
    //Card cardtoRemove = convertInput(inputCard);
    //cout << "cardtoRemove " << cardtoRemove.num << cardtoRemove.color << endl;
    //p1.removeCard(cardtoRemove);
    //p1.print();
    return 0;
}
