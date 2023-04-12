#pragma once

#include "card.hpp"

#include <string>   // for the player's name
#include <vector> // to hold the cards

namespace ariel{
    class Player
    {
    private:
        // the name of the player
        std::string name;
        // the size of the player's stack - how many cards he holds now
        int stackS;
        // the number of cards the player took
        int cardesT;
        // the cards the player has now
        std::vector<Card> stack;

    public:
        Player(); // empty constructor
        Player(std::string player_name); // constructor

        // given functions from Demo.cpp

        //prints the amount of cards left.
        int stacksize(); 
        // prints the amount of cards this player has won.
        int cardesTaken(); 


        // my helper functions

        // adds a card to the player's stack.
        void addCardToStack(Card card); 
        // removes the top card from the stack
        Card removeTopCard();
        // get the name of the player
        std::string getName() const;
        // set player's caredT
        void setCardesT(int cards);
        
    };

    
}