/*************************************************************************
   This is a sample of what the main should like for the final phase of 
   the Boop game.

   Patricia Lindner	Ohio University		Fall 2019
*************************************************************************/
#include <iostream>
#include "boop.h"
using namespace std;
using namespace main_savitch_14;


int main(){
   Boop mygame;
   game::who winner = mygame.play();

   if(winner == game::HUMAN) cout << "Human Wins!\n\n";
   else cout << "Computer Wins!\n\n";

   return 0;
}