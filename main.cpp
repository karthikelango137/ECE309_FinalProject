/*
*/
#include "uno.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "time.h"
#include "windows.h"

using namespace std;


int main() {
    cout << "Welcome to UNO!" << endl;

    cout << "Would like to review the rules first? (y or n): ";
    string rules;
    cin >> rules;

    //if the user would like to read the rules display them.
    if(rules == "y")
        printRules();

    cout << "You may type end at any point as your card to end the game." << endl;
    cout << "Do you want to 1v1 the CPU? (y or n): ";
    string onevone;
    cin >> onevone;
    //if the user indicates they wish to have a 1v1 again the computer then do so, if not then ask what type of players
    //they would like to play as

    if(onevone == "y") {
        bool humanTurn = true;          //determines whether it is currently the users turn
        cout << "ONE ON ONE" << endl;
        humPlayer p1;
        cpuPlayer p2;

        srand(time(NULL));  //Allows the random number generator to be truly random instead of pseudo-random
        Deck fullDeck;
        p1.num = 1;
        p2.num = 2;
        int numPlayers = 2;
        int nextNum;
        Card lastPlayedCard;
        bool end = false;
        bool reverse = false;
        int randNum = rand() % 80;
        Card centerCard = fullDeck.cardDeck[randNum];
        while (centerCard.color == "w"){              //if the first card is a wild card pull another card.
            srand(time(NULL));
            int randNum = rand() % 80;
            Card centerCard = fullDeck.cardDeck[randNum];
        }
        Card cardtoPlay;
        string inputCard;

        while (!end) {  //until the game ends run this section
            bool promptAgain = true;
            while (promptAgain) {
                while (promptAgain) {
                    cout << "Card to Play: ";   //displays the center card with colored text
                    if (centerCard.color == "r" || centerCard.color[1] == 'r') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "b" || centerCard.color[1] == 'b') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 9);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "g" || centerCard.color[1] == 'g') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 10);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "y" || centerCard.color[1] == 'y') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 14);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }//wild card cases added 11/29
                    else if (centerCard.color == "w" || centerCard.color[1] == 'w') {
                        if (centerCard.wColor == "r") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 12);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "b") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 9);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "g") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 10);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "y") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 14);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        }

                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 15);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }
                    cout << endl;
                    if (humanTurn) {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 15);
                        p1.print();
                        SetConsoleTextAttribute(hConsole, 15);

                        {
                            if (p1.anyLegalCard(centerCard))
                                cout << "Your Turn, Play or Pickup a Card: ";
                            else
                                cout << "You have no playable cards. You can pickup a card by typing 'pickup'" << endl;
                            //input the card if you can play any card
                            cin >> inputCard;
                            //begin main nested if statement
                            if (inputCard == "pickup") {//pickup case
                                //this if statement checks if we didn't need to pickup
                                //THIS ISN'T WORKING FOR PICKING UP A CARD YOU CAN PLAY (needs to be fixed)
                                if (p1.anyLegalCard(centerCard)) {
                                    p1.pickupCard();
                                    promptAgain = false;
                                    humanTurn = false;
                                    break;
                                } else {
                                    p1.pickupCard();
                                    if (p1.anyLegalCard(centerCard)) {
                                        cout << "You may play your new card!" << endl;
                                        promptAgain = true;
                                    } else{
                                        promptAgain = false;
                                        humanTurn = false;
                                    }
                                }
                            } else if (inputCard == "end") {                //end case
                                cout << "The game has been quit." << endl;
                                end = true;
                                break;

                                //else assume that it's a card
                            } else if (inputCard[1] == 'R') {
                                Card cardtoRemove = convertInput(inputCard);
                                lastPlayedCard = cardtoRemove;
                                bool legal = p1.isLegal(cardtoRemove, centerCard);
                                if (legal) {
                                    cout << "Order is Reversed" << endl << endl;
                                    if (reverse == false) reverse = true;
                                    else reverse = false;
                                    promptAgain = false;
                                    humanTurn = false;
                                } else {
                                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                                    promptAgain = true;
                                    humanTurn = true;
                                }
                            } else if (inputCard[1] == 'S') {
                                Card cardtoRemove = convertInput(inputCard);
                                bool legal = p1.isLegal(cardtoRemove, centerCard);
                                if (legal) {
                                    p1.removeCard(cardtoRemove);
                                    centerCard = cardtoRemove;
                                    nextNum = switchPlayer(numPlayers, p1.num);

                                    cout << "Player " << p2.num << " is skipped" << endl;

                                    promptAgain = false;
                                    humanTurn = false;
                                } else {
                                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                                    promptAgain = true;
                                    humanTurn = true;
                                }
                            } else if (inputCard[1] == '+') {
                                Card cardtoRemove = convertInput(inputCard);
                                bool legal = p1.isLegal(cardtoRemove, centerCard);
                                if (legal) {
                                    p1.removeCard(cardtoRemove);
                                    centerCard = cardtoRemove;
                                    nextNum = switchPlayer(numPlayers, p1.num);
                                    cout << "Player " << p2.num << " draw's 2" << endl;

                                    p2.pickupCard();
                                    p2.pickupCard();
                                    promptAgain = false;
                                    humanTurn = false;
                                } else {
                                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                                    promptAgain = true;
                                    humanTurn = true;
                                }
                            } else {                                        //card case
                                Card cardtoRemove = convertInput(inputCard);
                                lastPlayedCard = cardtoRemove;
                                bool legal = p1.isLegal(cardtoRemove, centerCard);
                                if (legal) {//if the card is a legal card to be played
                                    p1.removeCard(cardtoRemove);//remove the card
                                    centerCard = cardtoRemove;//update the center card
                                    //lastPlayedCard = cardtoRemove;
                                    //WILD CASE added 11/29
                                    if (cardtoRemove.color == "w") {
                                        string wildColor;
                                        while (wildColor != "r" || wildColor != "b" || wildColor != "g" ||
                                               wildColor != "y") {
                                            cout << "Color of wild (r, b, y, g): ";
                                            cin >> wildColor;
                                            cout << endl;
                                            if (wildColor == "r" || "b" || "g" || "y")
                                                break;
                                            if (wildColor != "r" || wildColor != "b" || wildColor != "g" ||
                                                wildColor != "y")
                                                cout << "Incorrect Input" << endl;
                                        }
                                        centerCard.color = wildColor;
                                        if (cardtoRemove.num == 4) {//DRAW FOUR CASE
                                            nextNum = switchPlayer(numPlayers, p1.num);
                                            cout << "Player " << p2.num << " draw's 4" << endl << endl;

                                            p2.pickupCard();
                                            p2.pickupCard();
                                            p2.pickupCard();
                                            p2.pickupCard();
                                            promptAgain = false;
                                            humanTurn = false;


                                        }

                                    }
                                    //we don't need to prompt this user for more info
                                    promptAgain = false;
                                    humanTurn = false;
                                } else {//catch-all case, illegal move or unexpected input
                                    cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                                    promptAgain = true;
                                    humanTurn = true;
                                }
                            }
                        }

                    }
                    else{
                        cardtoPlay = p2.playCard(centerCard); //plays the first legal card
                        centerCard = cardtoPlay;
                        if (cardtoPlay.color.find('+') != string::npos) {   //if the card is a draw 2
                            nextNum = switchPlayer(numPlayers, p2.num);
                            humanTurn = true;
                            cout << "Player " << p1.num << " draw's 2" << endl;

                            p1.pickupCard();
                            p1.pickupCard();
                            promptAgain = false;
                            humanTurn = true;
                        }else if(cardtoPlay.color.find('R') != string::npos){   //if the card is a reverse
                            if (reverse == false)
                                reverse = true;
                            else
                                reverse = false;

                            promptAgain = false;
                            humanTurn = true;
                        }else if(cardtoPlay.color.find('S') != string::npos){
                            nextNum = switchPlayer(numPlayers, p2.num);
                            humanTurn = true;

                            cout << "Player " << p1.num << " is skipped" << endl;

                            promptAgain = false;
                            humanTurn = true;
                        }
                        promptAgain = false;
                        humanTurn = true;
                    }
                }
            }
        }
    }

    else{
        cout << "Would you like to play as 4 players or 4 computers? (p or c): ";
        string gameType;
        cin >> gameType;
        if(gameType == "c") {
            cpuPlayer p1;
            cpuPlayer p2;
            cpuPlayer p3;
            cpuPlayer p4;
            cpuPlayer pNow;

            srand(time(NULL));
            Deck fullDeck;
            p1.num = 1;
            p2.num = 2;
            p3.num = 3;
            p4.num = 4;
            int nextNum = 0;
            int numPlayers = 4;
            pNow = p1;
            Card lastPlayedCard;
            bool end = false;
            bool reverse = false;
            int randNum = rand() % 80;
            Card centerCard = fullDeck.cardDeck[randNum];
            if (centerCard.color == "w"){
                srand(time(NULL));
                int randNum = rand() % 80;
                Card centerCard = fullDeck.cardDeck[randNum];
            }
            Card cardtoPlay;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 15);

            string inputCard;
            //begin the main while loop
            while (!end) {
                //prompts for user
                bool promptAgain = true;
                while (promptAgain) {
                    cout << "Card to Play: ";
                    if (centerCard.color == "r" || centerCard.color[1] == 'r') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "b" || centerCard.color[1] == 'b') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 9);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "g" || centerCard.color[1] == 'g') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 10);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "y" || centerCard.color[1] == 'y') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 14);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }//wild card cases added 11/29
                    else if (centerCard.color == "w" || centerCard.color[1] == 'w') {
                        if (centerCard.wColor == "r") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 12);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "b") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 9);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "g") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 10);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "y") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 14);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        }

                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 15);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }
                    cout << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    pNow.print();
                    SetConsoleTextAttribute(hConsole, 15);

                    //===========================================================================
                    // IF THE PLAYER IS A CPU IT WILL NOT ASK FOR INPUTS
                    //===========================================================================
                    cardtoPlay = pNow.playCard(centerCard); //plays the first legal card
                    centerCard = cardtoPlay;
                    if (cardtoPlay.color.find('+') != string::npos) {   //if the card is a draw 2
                        if (pNow.num == 1) {
                            p1 = pNow;
                            p1.num = 1;
                        } else if (pNow.num == 2) {
                            p2 = pNow;
                            p2.num = 2;
                        } else if (pNow.num == 3) {
                            p3 = pNow;
                            p3.num = 3;
                        } else if (pNow.num == 4) {
                            p4 = pNow;
                            p4.num = 4;
                        }
                        nextNum = switchPlayer(numPlayers, pNow.num);
                        if (nextNum == 1)
                            pNow = p1;
                        else if (nextNum == 2)
                            pNow = p2;
                        else if (nextNum == 3)
                            pNow = p3;
                        else if (nextNum == 4)
                            pNow = p4;

                        cout << "Player " << pNow.num << " draw's 2" << endl;

                        pNow.pickupCard();
                        pNow.pickupCard();
                        promptAgain = false;
                    } else if (cardtoPlay.color.find('R') != string::npos) {   //if the card is a reverse
                        if (reverse == false)
                            reverse = true;
                        else
                            reverse = false;

                        promptAgain = false;
                    } else if (cardtoPlay.color.find('S') != string::npos) {
                        if (pNow.num == 1) {
                            p1 = pNow;
                            p1.num = 1;
                        } else if (pNow.num == 2) {
                            p2 = pNow;
                            p2.num = 2;
                        } else if (pNow.num == 3) {
                            p3 = pNow;
                            p3.num = 3;
                        } else if (pNow.num == 4) {
                            p4 = pNow;
                            p4.num = 4;
                        }
                        nextNum = switchPlayer(numPlayers, pNow.num);
                        if (nextNum == 1)
                            pNow = p1;
                        else if (nextNum == 2)
                            pNow = p2;
                        else if (nextNum == 3)
                            pNow = p3;
                        else if (nextNum == 4)
                            pNow = p4;

                        cout << "Player " << pNow.num << " is skipped" << endl;

                        promptAgain = false;
                    }
                    promptAgain = false;
                }

                //win case
                //will need to add option to play again and restart the game
                if (pNow.handList.empty()) {
                    cout << "Player " << pNow.num << " has won!" << endl;
                    //end game
                    return 0;
                }

                //initialize player numbers for switch function
                if (pNow.num == 1) {
                    p1 = pNow;
                    p1.num = 1;
                } else if (pNow.num == 2) {
                    p2 = pNow;
                    p2.num = 2;
                } else if (pNow.num == 3) {
                    p3 = pNow;
                    p3.num = 3;
                } else if (pNow.num == 4) {
                    p4 = pNow;
                    p4.num = 4;
                }

                //switch players for while loop
                if (reverse == false) nextNum = switchPlayer(numPlayers, pNow.num);
                else nextNum = RSwitchPlayer(numPlayers, pNow.num);

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
        else if(gameType == "p"){
            humPlayer p1;
            humPlayer p2;
            humPlayer p3;
            humPlayer p4;
            humPlayer pNow;

            srand(time(NULL));
            Deck fullDeck;
            p1.num = 1;
            p2.num = 2;
            p3.num = 3;
            p4.num = 4;
            int nextNum = 0;
            int numPlayers = 4;

            Card lastPlayedCard;
            bool end = false;
            bool reverse = false;
            pNow = p1;
            int randNum = rand() % 80;
            Card centerCard = fullDeck.cardDeck[randNum];
            if (centerCard.color == "w"){
                srand(time(NULL));
                int randNum = rand() % 80;
                Card centerCard = fullDeck.cardDeck[randNum];
            }
            Card cardtoPlay;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 15);

            string inputCard;
            //begin the main while loop
            while (!end) {
                //prompts for user
                bool promptAgain = true;
                while (promptAgain) {
                    cout << "Card to Play: ";
                    if (centerCard.color == "r" || centerCard.color[1] == 'r') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "b" || centerCard.color[1] == 'b') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 9);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "g" || centerCard.color[1] == 'g') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 10);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    } else if (centerCard.color == "y" || centerCard.color[1] == 'y') {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 14);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }//wild card cases added 11/29
                    else if (centerCard.color == "w" || centerCard.color[1] == 'w') {
                        if (centerCard.wColor == "r") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 12);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "b") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 9);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "g") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 10);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        } else if (centerCard.wColor == "y") {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 14);
                            std::cout << centerCard.num << centerCard.color << ' ';
                        }

                    } else {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 15);
                        std::cout << centerCard.num << centerCard.color << ' ';
                    }
                    cout << endl;
                    SetConsoleTextAttribute(hConsole, 15);
                    pNow.print();
                    SetConsoleTextAttribute(hConsole, 15);

                    //===========================================================================
                    // IF THE PLAYER IS A HUMAN IT WILL ASK FOR INPUTS
                    //===========================================================================

                    if (pNow.anyLegalCard(centerCard))
                        cout << "Your Turn, Play or Pickup a Card: ";
                    else
                        cout << "You have no playable cards. You can pickup a card by typing 'pickup'" << endl;
                    //input the card if you can play any card
                    cin >> inputCard;
                    //begin main nested if statement
                    if (inputCard == "pickup") {//pickup case
                        //this if statement checks if we didn't need to pickup
                        //THIS ISN'T WORKING FOR PICKING UP A CARD YOU CAN PLAY (needs to be fixed)
                        if (pNow.anyLegalCard(centerCard)) {
                            pNow.pickupCard();
                            promptAgain = false;
                            break;
                        } else {
                            pNow.pickupCard();
                            if (pNow.anyLegalCard(centerCard)) {
                                cout << "You may play your new card!" << endl;
                                promptAgain = true;
                            } else
                                promptAgain = false;
                        }
                    } else if (inputCard == "end") {                //end case
                        cout << "The game has been quit." << endl;
                        end = true;
                        break;

                        //else assume that it's a card
                    } else if (inputCard[1] == 'R') {
                        Card cardtoRemove = convertInput(inputCard);
                        lastPlayedCard = cardtoRemove;
                        bool legal = pNow.isLegal(cardtoRemove, centerCard);
                        if (legal) {
                            cout << "Order is Reversed" << endl << endl;
                            if (reverse == false) reverse = true;
                            else reverse = false;
                            promptAgain = false;
                        } else {
                            cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                            promptAgain = true;
                        }
                    } else if (inputCard[1] == 'S') {
                        Card cardtoRemove = convertInput(inputCard);
                        bool legal = pNow.isLegal(cardtoRemove, centerCard);
                        if (legal) {
                            pNow.removeCard(cardtoRemove);
                            if (pNow.num == 1) {
                                p1 = pNow;
                                p1.num = 1;
                            } else if (pNow.num == 2) {
                                p2 = pNow;
                                p2.num = 2;
                            } else if (pNow.num == 3) {
                                p3 = pNow;
                                p3.num = 3;
                            } else if (pNow.num == 4) {
                                p4 = pNow;
                                p4.num = 4;
                            }
                            centerCard = cardtoRemove;
                            nextNum = switchPlayer(numPlayers, pNow.num);
                            if (nextNum == 1)
                                pNow = p1;
                            else if (nextNum == 2)
                                pNow = p2;
                            else if (nextNum == 3)
                                pNow = p3;
                            else if (nextNum == 4)
                                pNow = p4;

                            cout << "Player " << pNow.num << " is skipped" << endl;

                            promptAgain = false;
                        } else {
                            cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                            promptAgain = true;
                        }
                    } else if (inputCard[1] == '+') {
                        Card cardtoRemove = convertInput(inputCard);
                        bool legal = pNow.isLegal(cardtoRemove, centerCard);
                        if (legal) {
                            pNow.removeCard(cardtoRemove);
                            if (pNow.num == 1) {
                                p1 = pNow;
                                p1.num = 1;
                            } else if (pNow.num == 2) {
                                p2 = pNow;
                                p2.num = 2;
                            } else if (pNow.num == 3) {
                                p3 = pNow;
                                p3.num = 3;
                            } else if (pNow.num == 4) {
                                p4 = pNow;
                                p4.num = 4;
                            }
                            centerCard = cardtoRemove;
                            nextNum = switchPlayer(numPlayers, pNow.num);
                            if (nextNum == 1)
                                pNow = p1;
                            else if (nextNum == 2)
                                pNow = p2;
                            else if (nextNum == 3)
                                pNow = p3;
                            else if (nextNum == 4)
                                pNow = p4;

                            cout << "Player " << pNow.num << " draw's 2" << endl;

                            pNow.pickupCard();
                            pNow.pickupCard();
                            promptAgain = false;
                        } else {
                            cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                            promptAgain = true;
                        }
                    } else {                                        //card case
                        Card cardtoRemove = convertInput(inputCard);
                        lastPlayedCard = cardtoRemove;
                        bool legal = pNow.isLegal(cardtoRemove, centerCard);
                        if (legal) {//if the card is a legal card to be played
                            pNow.removeCard(cardtoRemove);//remove the card
                            centerCard = cardtoRemove;//update the center card
                            //lastPlayedCard = cardtoRemove;
                            //WILD CASE added 11/29
                            if (cardtoRemove.color == "w") {
                                string wildColor;
                                while (wildColor != "r" || wildColor != "b" || wildColor != "g" ||
                                       wildColor != "y") {
                                    cout << "Color of wild (r, b, y, g): ";
                                    cin >> wildColor;
                                    cout << endl;
                                    if (wildColor == "r" || "b" || "g" || "y")
                                        break;
                                    if (wildColor != "r" || wildColor != "b" || wildColor != "g" ||
                                        wildColor != "y")
                                        cout << "Incorrect Input" << endl;
                                }
                                centerCard.color = wildColor;
                                if (cardtoRemove.num == 4) {//DRAW FOUR CASE
                                    if (pNow.num == 1) {
                                        p1 = pNow;
                                        p1.num = 1;
                                    } else if (pNow.num == 2) {
                                        p2 = pNow;
                                        p2.num = 2;
                                    } else if (pNow.num == 3) {
                                        p3 = pNow;
                                        p3.num = 3;
                                    } else if (pNow.num == 4) {
                                        p4 = pNow;
                                        p4.num = 4;
                                    }
                                    nextNum = switchPlayer(numPlayers, pNow.num);
                                    if (nextNum == 1)
                                        pNow = p1;
                                    else if (nextNum == 2)
                                        pNow = p2;
                                    else if (nextNum == 3)
                                        pNow = p3;
                                    else if (nextNum == 4)
                                        pNow = p4;
                                    cout << "Player " << pNow.num << " draw's 4" << endl << endl;

                                    pNow.pickupCard();
                                    pNow.pickupCard();
                                    pNow.pickupCard();
                                    pNow.pickupCard();
                                    promptAgain = false;


                                }

                            }
                            //we don't need to prompt this user for more info
                            promptAgain = false;
                        } else {//catch-all case, illegal move or unexpected input
                            cout << "ILLEGAL MOVE, DRAW OR PLAY ANOTHER CARD" << endl;
                            promptAgain = true;
                        }
                    }

                }
                //win case
                //will need to add option to play again and restart the game
                if (pNow.handList.empty()) {
                    cout << "Player " << pNow.num << " has won!" << endl;
                    //end game
                    return 0;
                }

                //initialize player numbers for switch function
                if (pNow.num == 1) {
                    p1 = pNow;
                    p1.num = 1;
                } else if (pNow.num == 2) {
                    p2 = pNow;
                    p2.num = 2;
                } else if (pNow.num == 3) {
                    p3 = pNow;
                    p3.num = 3;
                } else if (pNow.num == 4) {
                    p4 = pNow;
                    p4.num = 4;
                }

                //switch players for while loop
                if (reverse == false) nextNum = switchPlayer(numPlayers, pNow.num);
                else nextNum = RSwitchPlayer(numPlayers, pNow.num);

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
    }
    return 0;
}
