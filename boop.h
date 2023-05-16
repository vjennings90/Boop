#ifndef BOOP_H
#define BOOP_H
#include "space.h"
#include "game.h"

namespace main_savitch_14{

class Boop: public game{
    public:
		static const int SIZE = 6;

		/**
	    * @brief constructing on a Boop object, by calling the restart function
        */
        Boop();

		/**
	    * @brief checking if a move can be made with numerous conditions
		* such as empty string, order of the move string, if it is k or c, etc
        */
        bool is_legal(const std::string& move) const;


		/**
	    * @brief setting the type of the space to show a piece
		* 
		* @param move - a string
        */
        void make_move(const std::string& move);

		// Restart the game from the beginning:
		/**
	    * @brief Restarting the game from beginning, all board spaces empty
        */
		void restart();

		/**
	    * @brief 
        */
		game* clone() const;
		// Compute all the moves that the next player can make:

		/**
	    * @brief 
        */
		void compute_moves(std::queue<std::string>& moves) const;

		/**
	    * @brief display the board, default is with all empty spaces, columns 1 - 6, rows U - Z
        */
		void display_status() const;

		/**
	    * @brief checking booping conditions and moving pieces based off evaluation
		* 
		* @param move - a string
        */
		void booping(const std::string& move);

		/**
	    * @brief depending on piece, adds piece type back to player's bank
		* 
		* @param Space - piece
        */
		void return_to_bank(Space& piece);


		/**
	    * @brief checking if there are three cats in a row to make a cat
		* 
		* @param move - a string
        */
		void make_cat(const std::string& move);
		
		/**
	    * @brief evaluates each computers board to find best move
        */
		int evaluate() const;
		
		/**
	    * @brief checks to see if there are three cats in a row or all pieces on board
        */
		bool is_game_over() const;

		/**
	    * @brief checks which player is winning
		* 
        */
		who winning() const;


		/**
	    * @brief adds a single piece to board and boops pieces
		* 
		* @param move - a string
        */
		void make_move_1(const std::string& move);

		/**
	    * @brief creates 3 cats and adding pieces to board
		* 
		* @param move - a string
        */
		void make_move_2(const std::string& move);

		/**
	    * @brief if there are all pieces on board it will remove one piece and add a cat to bank
		* 
		* @param move - a string
        */
		void make_move_3(const std::string& move);

		/**
	    * @brief checks if there are three kittens or a mixture of cats and kittens in a row
		* 
        */
		bool kitten_row();

		/**
	    * @brief checks if input is valid, for one piece
		* 
		* @param move - a string
        */
		bool is_legal_1(const std::string& move) const;

		/**
	    * @brief checking if there are a mixture of cats and kittens in a row 
		* 
		* @param move - a string
        */
		bool is_legal_2(const std::string& move) const;

		/**
	    * @brief checks if piece that will be removed is of the correct player type
		* 
		* @param move - a string
        */
		bool is_legal_3(const std::string& move) const;

		/**
	    * @brief returns user
        */
		std::string get_user_move() const;

    private:
        Space board[SIZE][SIZE];
        int p1c;// # of player 1's cats
        int p2c;// # of player 2's cats
        int p1k;// # of player 1's kittens
        int p2k;// # of player 2's kittens
        int move_count;
		int turn_type;
        
};
}

#endif