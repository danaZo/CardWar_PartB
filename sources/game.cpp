#include "game.hpp"
#include <iostream> // writing to a file
// to shuffle the pack
#include <algorithm> 
#include <random> 

/* Web Sources I used:
    - https://www.techiedelight.com/shuffle-vector-cpp/
    - https://stackoverflow.com/questions/3827320/simple-class-concepts-in-c-cards-in-a-deck
    - https://cplusplus.com/forum/general/265502/
    - https://en.cppreference.com/w/cpp/algorithm/random_shuffle
*/

namespace ariel{

    // empty constructor
    Game::Game(){} 

    /* constructor for the 'Game' class
       takes 2 players as arguments
       assigning the players that passed as arguments to the corresponding
       members of the Game being constructed
       this is setting up the two players for the game being created.
       then, we create a new pack of 52 cards, shuffle the cards, 
       and give to each player 26 cards. 
       creating a log file to save the game results*/
    Game::Game(Player& _p1, Player& _p2) 
    {
        this->player_1 = &_p1;
        this->player_2 = &_p2;
        this->pack = createPack();
        giveCards();
        this->logs.open("game_log.txt");
        this->turns_num = 0;
        this->draws = 0;
        this->player1gamesWon = 0;
        this->player2gamesWon = 0;
    }


    /*  implementation: creating new pack of cards, and a map to map rank number to name.
        looping through the card's ranks from 1 - Ace to 13 - King
        adding cards of the current rank and suit to the pack
        function push_back is a member function of the std::vector class.
        it is used to add elements to the end of the vector.
    */
    std::vector<Card> Game::createPack(){
        std::vector<Card> new_pack;
        
        for (int i = 1; i <= 13; i++)
        {
            new_pack.push_back(Card("Spades", i));
            new_pack.push_back(Card("Hearts", i));
            new_pack.push_back(Card("Diamonds", i));
            new_pack.push_back(Card("Clubs", i));
        }
        // Create a random number generator engine
        std::mt19937 rng{std::random_device{}()};

        // Shuffle the vector using the random engine
        std::shuffle(new_pack.begin(), new_pack.end(), rng);
        return new_pack;  
    }


    /*  implementation: giving 26 cards to each player
        looping 26 times
        at each loop add one card to player 1 and remove it from the pack
        then add one card to player 2 and remove it from the pack
    */
    void Game::giveCards(){
        for (int i = 0; i < 26; i++)
        {
            this->player_1->addCardToStack(this->pack.back());
            this->pack.pop_back();

            this->player_2->addCardToStack(this->pack.back());
            this->pack.pop_back();
        }

    }


    /*  implementation - checking that they both have cards, if no - game ended.
        each player throws a card: 
        card1 refers to player_1, card2 refers to player_2.
        printing the cards played to the log file.
        checking which card has the higher rank, using the function compareCards that return int to indicate the result.
        if result is 1 - player_1 wins, if the result is 2 - player_2 wins, if the result is 0 - draw - going to war
        
    */
    void Game::playTurn(){
        if (this->player_1->stacksize() == 0 && this->player_2->stacksize() == 0)
        {
            throw std::runtime_error("Game is over. Cannot play a new turn.");
            return; 
        }

        if (this->player_1->getName() == this->player_2->getName()) {
            throw std::invalid_argument("Error: Can't play with only 1 player.");
            return;
        }
        
        Card card1 = this->player_1->removeTopCard();
        Card card2 = this->player_2->removeTopCard();

        this->logs << this->player_1->getName() << " played " << card1.toString() << " " << player_2->getName() << " played " << card2.toString() << ". ";

        int result = compareCards(card1, card2);

        if (result == 1) 
        {
            this->logs << this->player_1->getName() << " wins.\n";
            this->player_1->setCardesT(this->player_1->cardesTaken() + 2);
            set_turns_num(get_turns_num()+1);
            set_player1gamesWon(this->player1gamesWon + 1);
        } 
        
        else if (result == 2) 
        {
            this->logs << this->player_2->getName() << " wins.\n";
            this->player_2->setCardesT(this->player_2->cardesTaken() + 2);
            set_turns_num(get_turns_num()+1);
            set_player2gamesWon(this->player2gamesWon + 1);
        } 
        
        else 
        {
            this->logs << "Draw. ";
            set_turns_num(get_turns_num()+1);
            set_draws(get_draws()+1);
            war(this->player_1->stacksize(), this->player_2->stacksize(), 1, 1);
        }
        
    }

    /*  the war condition
        if the players has no cards, each player takes the card he drew and game is over.
        no cards -> stacksize = 0 -> every player put one card on the table (the cards that made a war)
        else if the players have only one card, they can only put the card that is upside down
        and not the card to determine the winner so each takes the cards he threw - 2 cards for each.
        else - they have enough cards
        each player puts a card upside down, then a card face up.
        we compare the cards with face up.
        the compareCards function return int that indicates the result
        if result is 1 - player_1 wins and takes all the cards - 6 cards
        if the result is 2 - player 2 wins and takes all the cards - 6 cards
    */
    void Game::war(int stack1, int stack2, int onTable1, int onTable2) {
        
        if ( stack1 < 2 && stack2 < 2)
        {
            this->player_1->setCardesT(this->player_1->cardesTaken() + stack1 + onTable1);
            this->player_2->setCardesT(this->player_2->cardesTaken() + stack2 + onTable2);
            if(this->player_1->stacksize()>0)this->player_1->removeTopCard();
            if(this->player_2->stacksize()>0)this->player_2->removeTopCard();
            
        }
        
        else 
        {
            
            Card p1_down = player_1->removeTopCard(); 
            onTable1 ++;

            Card p2_down = player_2->removeTopCard(); 
            onTable2 ++;

            Card p1_up = player_1->removeTopCard();
            onTable1 ++;

            Card p2_up = player_2->removeTopCard(); 
            onTable2 ++;

            this->logs << this->player_1->getName() << " played " << p1_up.toString() << " " << player_2->getName() << " played " << p2_up.toString() << ". ";

            int result = compareCards(p1_up, p2_up);

            if (result == 1) 
            {
                this->logs << this->player_1->getName() << " wins.\n";
                this->player_1->setCardesT(this->player_1->cardesTaken() + onTable1 + onTable2);
                set_turns_num(get_turns_num()+1);
                set_player1gamesWon(this->player1gamesWon + 1);
            } 
            
            else if (result == 2) 
            {
                this->logs << this->player_2->getName() << " wins.\n";
                this->player_2->setCardesT(this->player_2->cardesTaken() + onTable1 + onTable2);
                set_turns_num(get_turns_num()+1);
                set_player2gamesWon(this->player2gamesWon + 1);
            } 
            
            else 
            {
                this->logs << "Draw. ";
                set_turns_num(get_turns_num()+1);
                set_draws(get_draws()+1);
                war(this->player_1->stacksize(), this->player_2->stacksize(), onTable1 , onTable2);
            }
        }

    }


    /*  conditions:
        1) card1 is Ace , card2 is not 2 -> Ace wins -> player_1 wins
        2) card2 is Ace, card1 is not 2 -> Ace wins -> player_2 wins
        3) card1 is Ace, card2 is 2 -> player_2 wins
        4) card2 is Ace, card1 is 2 -> player_1 wins
        5) card1 > card2 -> player_1 wins
        6) card1 < card2 -> player_2 wins
        7) draw - going to war

        1 - player_1 wins
        2 - player_2 wins
        0 - draw
    */
    int Game::compareCards(Card card1, Card card2){

        if (card1.get_rank() == 1 && card2.get_rank() > 2)
        {
            return 1;
        }

        // 2) card2 is Ace, card1 is not 2 -> Ace wins -> player_2 wins
        else if (card2.get_rank() == 1 && card1.get_rank() > 2)
        {
            return 2;
        }

        // 3) card1 is Ace, card2 is 2 -> player_2 wins
        else if (card1.get_rank() == 1 && card2.get_rank() == 2)
        {
            return 2;
        }

        // 4) card2 is Ace, card1 is 2 -> player_1 wins
        else if (card2.get_rank() == 1 && card1.get_rank() == 2)
        {
            return 1;
        }

        // 5) card1 > card2 -> player_1 wins
        else if (card1.get_rank() > card2.get_rank())
        {
            return 1;
        }

        // 6) card1 < card2 -> player_2 wins
        else if (card1.get_rank() < card2.get_rank())
        {
            return 2;
        }
        
        // 7) draw - going to war
        else {
            return 0;

        }
    }

    /*  implementation: close the log file that created in the constructor in writing mode.
        open the file again in read mode.
        line stores the current line we read in the file.
        num_lines counts how many lines there are now in the file.
        the while loop used to get the number of lines in the file.
        the file contains empty line in the last line because i add new line after every line i write.
        so i need to read the line before the last - the one that has the last turn.
        so i seek to the beginning of the line before the last line using file.seekg.
        the line_to_read is the line before the last.
        in the for loop i go to the last line. 
        if the line isnt empty i print it, otherwise i print that the file is empty.
        at the end i open my file again, in a write mode, that way that the new lines will start
        from the end of the file.
    */
    void Game::printLastTurn(){
        this->logs.close();
        std::ifstream file("game_log.txt");
        std::string line;
        int num_lines = 0;

        // get number of lines in file
        while (std::getline(file, line)) {
            num_lines++;
        }
        
        // Seek to the beginning of the line before the last line
        file.clear(); // Clear any flags
        file.seekg(0, std::ios::beg);
        int line_to_read = num_lines - 1;
        for (int i = 0; i < line_to_read; i++) {
            std::getline(file, line);
        }

        // Read the line before the last line
        if (std::getline(file, line)) {
            std::cout << line << std::endl;
        } else {
            std::cout << "The file is empty." << std::endl;
        }

        this->logs.open("game_log.txt", std::ios::app);
    }

    /* Implementation: playing turns until there are no cards left
    */
    void Game::playAll(){
        while (this->player_1->stacksize() > 0 && this->player_2->stacksize() > 0)
        {
            playTurn();
        }
        
    }

    /*  implementation: checking which player took the most cards -> the one who did is the winner
        if they took the same number then there is no winner its a draw */
    void Game::printWiner(){

        if (this->player_1->cardesTaken() == 0 && this->player_2->cardesTaken() == 0)
        {
            std::cout << "The game isn't played yet." << std::endl;
        }
        
        else if (this->player_1->cardesTaken() > this->player_2->cardesTaken()) 
        {
            std::cout << "The winner is " << this->player_1->getName() << std::endl;
        } 
        else if (this->player_1->cardesTaken() < this->player_2->cardesTaken()) 
        {
            std::cout << "The winner is " << this->player_2->getName() << std::endl;
        } 
        else if (this->player_1->cardesTaken() ==  this->player_2->cardesTaken())
        {
            std::cout << "It's a draw" << std::endl;
        }
    }

    /*  implementation : closing the log file because it is in writing mode
        opening the log file in reading mode
        reading each line and prining it to the console
        opening the file in writing mode at the end.
    */
    void Game::printLog(){
        this->logs.close();
        std::ifstream file("game_log.txt");
        std::string line;

        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        this->logs.open("game_log.txt", std::ios::app);
    }

    int Game::get_turns_num(){
        return this->turns_num;
    }

    void Game::set_turns_num(int num){
        this->turns_num = num;
    }

    void Game::set_draws(int num){
        this->draws = num;
    }
        
    int Game::get_draws(){
        return this->draws;
    }

    double Game::winRate(std::string name){
        
        if (this->turns_num == 0) {
            return 0;
        } else if (name == this->player_1->getName()) {
            return 100.0 * this->player1gamesWon / this->turns_num;
        } else {
            return 100.0 * this->player2gamesWon / this->turns_num;
        }
    }

    void Game::set_player1gamesWon(int num){
        this->player1gamesWon = num;
    }
        
    void Game::set_player2gamesWon(int num){
        this->player2gamesWon = num;
    }

    void Game::printStats(){
        //number of turns played
        int numTurns = get_turns_num();
        //number of draws
        int drawsNum = get_draws();

        //draw rate
        double drawRate = (double) drawsNum / (double) numTurns * 100.0;

        // Print overall statistics
        std::cout << "Overall statistics:" << std::endl;
        std::cout << "  Number of turns played: " << numTurns << std::endl;
        std::cout << "  Number of draws: " << drawsNum << std::endl;
        std::cout << "  Draw rate: " << drawRate << "%" << std::endl;

        // Print player statistics
        std::cout << std::endl;
        std::cout << "Player 1 (" << this->player_1->getName() << "):" << std::endl;
        std::cout << "  Win rate: " << winRate(this->player_1->getName()) << "%" << std::endl;
        std::cout << "  Cards won: " << this->player_1->cardesTaken() << std::endl;
        
        std::cout << std::endl;
        std::cout << "Player 2 (" << this->player_2->getName() << "):" << std::endl;
        std::cout << "  Win rate: " << winRate(this->player_2->getName()) << "%" << std::endl;
        std::cout << "  Cards won: " << this->player_2->cardesTaken() << std::endl;
        
    }
        
};
