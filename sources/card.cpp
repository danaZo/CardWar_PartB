#include "card.hpp"
#include <map> // to map numbers to names

namespace ariel{
    
    Card::Card(){}

    Card::Card(std::string suit, int rank)
    {
        this->suit = suit;
        this->rank = rank;
    }
    
    std::string Card::get_suit() const { 
        return this->suit; 
    }

    int Card::get_rank() const { 
        return this->rank; 
    }

    /*  implementation: creating map of rank values to their corresponding names.
        convert rank to string. checking if the current card's rank is present in the
        'rank_names' map.
        the function find() returns an iterator pointing to the element with the key
        equal to the 'rank' value (if it exists in the map), otherwise it returns the
        iterator pointing to the end of the map.
        so, the condition 'rank_names.find(this->rank) != rank_names.end()'
        is true if the 'rank' value exists in the map.
        if the rank is in the map, it means that it's a special card (Ace,Jack,Queen or King).
        use the corresponding name instead of the number.
        at the end - return a string with the rank and suit of the card
    */
    std::string Card::toString() const {
        std::map<int, std::string> rank_names = {{1, "Ace"}, {11, "Jack"}, {12, "Queen"}, {13, "King"}};
        std::string rank_str = std::to_string(this->rank);
        if (rank_names.find(this->rank) != rank_names.end()) {
            rank_str = rank_names[this->rank];
        }
        return rank_str + " of " + this->suit;
    }
}