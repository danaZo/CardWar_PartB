#include "player.hpp"
#include <iostream> // to print

namespace ariel {

    Player::Player(std::string player_name) // constructor
    {
        this->name = player_name;
        this->stackS = 0; // initial size is 0
        this->cardesT = 0; // initial size is 0
        this->stack = std::vector<Card>(); // holds the objects of type Card
    }

    Player::Player(){} // empty constructor

    // the amount of cards left.
    int Player::stacksize(){ 
        return this->stackS;
    } 

    // the amount of cards this player has won.
    int Player::cardesTaken(){
        return this->cardesT;
    } 
    
    /*  implementation : pushing card to the pack of cards using method push_back
        increasing by 1 the integer stackS that hols the size of the stack
    */
    void Player::addCardToStack(Card card){
        this->stack.push_back(card);
        this->stackS++;
    }


    /* implementation : removing the top card from the stack and throwing to the table
    */
    Card Player::removeTopCard(){
        Card top = this->stack.back();
        this->stack.pop_back();
        this->stackS--;
        return top;
    }

    std::string Player::getName() const {
        return this->name;
    }

    void Player::setCardesT(int cards) {
        this->cardesT = cards;
    }

}