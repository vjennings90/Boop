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

		void return_to_bank(Space& piece);

		//bool is_valid_position(int row, int col);

		/**
	    * @brief checking if there are three cats in a row to make a cat
		* 
		* @param move - a string
        */
		void make_cat(const std::string& move);
		
		/**
	    * @brief
        */
		int evaluate() const;
		
		/**
	    * @brief 
        */
		bool is_game_over() const;

		who winning() const;

    private:
        Space board[SIZE][SIZE];
        int p1c;// # of player 1's cats
        int p2c;// # of player 2's cats
        int p1k;// # of player 1's kittens
        int p2k;// # of player 2's kittens
        int move_count;
        
};
}

#endif