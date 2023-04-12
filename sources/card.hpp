#pragma once
#include <string>

namespace ariel{

    class Card
    {
    private:
        int rank; // the value of the card
        std::string suit; // the shape and color of the card type
    
    public:
        Card();
        Card(std::string suit, int rank);
        std::string get_suit() const;
        int get_rank() const;
        // returns string representation of a card
        std::string toString() const;
    };
    
}