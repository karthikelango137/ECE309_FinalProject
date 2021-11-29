class cpuPlayer : public Player{ //YOU SHOULD ONLY NEED TO CALL PLAYCARD FUNCTION IN ORDER TO GET THE CPU TO PLAY -will
public:
    int num;
    list<Card> handList;
    cpuPlayer(){
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }
    void playCard(Card centerCard){
        bool state = false; //indicates whether we have found a legal card yet
        list<Card>::iterator it;
        Card tmp;
        for(it = this->handList.begin(); it != this->handList.end();it++){
            tmp.num = it->num;
            tmp.color = it->color;
            if(isLegal(tmp, centerCard)) {  //checks to see if the car chosen is legal
                removeCard(tmp);
                cout << "Card removed: " << tmp.num << tmp.color << endl;       //TESTING TEXT
                state = true;
                break;
            }
        }
        if(!state) {    //if we reach the end of the hand and no legal card is found, pickup a new one.
            pickupCard();
            cout << "Card picked up."<< endl;       //TESTING TEXT
        }
        cout<<endl;
    }
    void deal() {
        Deck dealDeck;
        //list<Card> returnDeck;
        for(int i = 0; i < 7; i++) {
            handList.push_back(dealDeck.cardDeck[i]);
        }
    }

    void pickupCard(){
        int randNum = rand()%80;
        Deck dealdeck;
        handList.push_back(dealdeck.cardDeck[randNum]);
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

    bool anyLegalCard( Card centerCard) {
        //check if card is in hand
        //if card matches centerCard
        bool legal = false;
        list<Card>::iterator it;
        for (it = this->handList.begin(); it != this->handList.end(); it++) {
            if (it->num == centerCard.num || it->color == centerCard.color) {
                legal = true;
                return true;
                break;
            }
        }
        return false;
    }

    void print(){
        cout << "Player " << num << "'s Hand: ";
        for (auto v : handList){
            std::cout << v.num << v.color << ' ';
        }
        cout << endl;
    }//for testing purposes only
};
