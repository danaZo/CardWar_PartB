#pragma once

#include "player.hpp"
#include <vector> // to hold the cards
#include <fstream> // for file handling

namespace ariel{
    class Game
    {
    private:
        // each game has 2 players
        Player* player_1; 
        Player* player_2;
        // each game has a pack of cards
        std::vector<Card> pack;
        // log file 
        std::ofstream logs;
        // number of turns played
        int turns_num;
        // number of draws 
        int draws;
        // number of games player 1 won
        int player1gamesWon;
        // number of games player 2 won
        int player2gamesWon;

    public:

        // empty constructor
        Game(); 
        // constructor
        Game(Player& _p1, Player& _p2); 
        
        // given functions from Demo.cpp

        // playes one turn in the game 
        void playTurn();
        void printLastTurn();
        //playes the game untill the end
        void playAll();
        void printWiner();
        void printLog();
        void printStats();


        // my helper functions

        // creating new pack of 52 cards
        std::vector<Card> createPack();  
        // give 26 cards from the pack to each player
        void giveCards(); 
        // war condition
        void war(int stack1, int stack2, int onTable1, int onTable2);
        // comparing the cards
        int compareCards(Card card1, Card card2);
        // set the turns_num
        void set_turns_num(int num);
        // get the turn num
        int get_turns_num();
        // set the draws
        void set_draws(int num);
        // get the draws
        int get_draws();
        // win rate of a player
        double winRate(std::string name);
        // set player1gamesWon
        void set_player1gamesWon(int num);
        // set player2gamesWon
        void set_player2gamesWon(int num);
    };
    
}