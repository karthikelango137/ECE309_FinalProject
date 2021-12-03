#pragma once
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

	void print() {
		for (int i = 0; i < cardDeck.size(); i++) {
			cout << cardDeck[i].num << cardDeck[i].color << ' ';
		}
		cout << endl;
	}//for testing purposes only
};

class Player {
public:
	int num;
	bool cpu = false;
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
					cout << "Card removed: " << tmp.num << tmp.color << endl;       //TESTING TEXT
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

#endif //ECE309_PROJECT_UNO_H