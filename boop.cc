#include "boop.h"
#include "space.h"
#include <iostream>
#include <string>
#include "colors.h"
using namespace std;
using namespace main_savitch_14;


/*Notes
last_mover() - tells who last made a last_mover

if(next_mover == HUMAN) - Player 1's Turn
if(next_mover == COMPUTER) - Player 2's Turn
*/

Boop::Boop(){
    restart();
}

void Boop::restart(){
    p1c = 0;
    p2c = 0;
    p1k = 8;
    p2k = 8;
    game::restart(); //sets move number to 0

    for(int row = 0; row < SIZE; row++){
        for(int column = 0; column < SIZE; column++){
            board[row][column].set_type(0);
        }
    }
}

void Boop::make_move(const string& move){
    char answer;
    string begin_row;
    //Interpreting Move
    //c or k part
    char animal = toupper(move.at(0));
    // column part
    //char column = move.at(1);
    int column = move.at(1) - '1'; 
    //row part
    int row = toupper(move.at(2)) - 'U';

    int type_num = 0;
    //KEY: p1k = 1, p2k = 2, p1c = 3, p2c = 4, empty = 0
    if(next_mover() == HUMAN){ //Player 1's turn
        if(animal == 'K'){
            type_num = 1;
            p1k = p1k - 1;
            board[row][column].set_type(type_num);
        }else{
            type_num = 3;
            p1c = p1c - 1;
            board[row][column].set_type(type_num);
        }  
    }else{//Player 2's turn
        if(animal == 'K'|| animal == 'k'){
            type_num = 2;
            p2k = p2k - 1;
            board[row][column].set_type(type_num);
        }else{
            type_num = 4;
            p2c = p2c - 1;
            board[row][column].set_type(type_num); 
        }
    }
    

    //checking for any booping
    booping(move);


    //if there are enough kittens or cats on board to have kittens in a row
    if((p1k <= 6 && p1c >= 1) || (p2k <= 6 && p2c >= 1) || (p1k <= 5)|| (p2k <= 5)){
        display_status();
        cout << "Are there three kittens in a row?(y/n): " << endl;
        cin >> answer;
        if(cin.peek() == '\n') cin.ignore();

        if(answer == 'n' || answer == 'N'){//no cats to create
            game::make_move(move);// increments it
            return;
        }else{
            cout << "Where does row begin? and in what diretion?" << endl;
            cout << "Input format: direction(v,h,d), column, row...ex: d1z(diagonal, column 1, row z)" << endl;
            cin >> begin_row;
            if(cin.peek() == '\n') cin.ignore();
            make_cat(begin_row);
        }
    }


    game::make_move(move);// increments it
}


void Boop::return_to_bank(Space& piece){
    if(piece.get_type() == 1){
        piece.set_type(0);
        p1k++;
    }
    else if(piece.get_type() == 2){
        piece.set_type(0);
        p2k++;
    }
    else if(piece.get_type() == 3){
        piece.set_type(0);
        p1c++;
    }
    else if(piece.get_type() == 4){
        piece.set_type(0);
        p2c++;
    }
    
}


void Boop::booping(const string& move){
    //Interpreting Move
    //c or k part
    char animal = toupper(move.at(0));
    // column part
    //char column = move.at(1);
    int column = move.at(1) - '1'; 
    //row part
    int row = toupper(move.at(2)) - 'U';

    //checking if move is a kitten piece
    bool kitten = false;
    if(animal == 'K'|| animal == 'k'){
        kitten = true;
    }
    //checking if move is a cat piece
    bool cat = false;
    if(animal == 'C' || animal == 'c'){
        cat = true;
    }

    //CHECKING SPACES AROUND MOVE
    
    //top left corner space
    if(row - 2 >= 0 && column - 2 >= 0 && board[row - 2][column - 2].get_type() == 0){//checking booping space is empty
        if((board[row - 1][column - 1].get_type() == 1 || board[row - 1][column - 1].get_type() == 2) && (kitten)){
            board[row - 2][column - 2].set_type(board[row -1][column - 1].get_type());
            board[row - 1][column - 1].set_type(0);
        }else if(board[row - 1][column - 1].get_type() != 0 && (cat)){
            board[row - 2][column - 2].set_type(board[row - 1][column - 1].get_type());
            board[row - 1][column - 1].set_type(0);
        }
    }
    else if((row - 1 == 0 || column - 1 == 0 )&& (board[row - 1][column - 1].get_type() == 1 || board[row - 1][column - 1].get_type() == 2) && (kitten)){
        if(board[row - 1][column - 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row - 1][column - 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row - 1][column - 1].set_type(0);
    }
    else if(row - 1 >= 0 && column - 1 >= 0 && (row - 1 == 0 || column - 1 == 0) && board[row - 1][column - 1].get_type() != 0 && (cat)){
        if(board[row - 1][column - 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row - 1][column - 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row - 1][column - 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row - 1][column - 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row - 1][column - 1].set_type(0);
    }


    //top middle space
    if(row - 2 >= 0 && board[row - 2][column].get_type() == 0){//checking booping space is empty
        if((board[row - 1][column].get_type() == 1 || board[row - 1][column].get_type() == 2) && (kitten)){
            board[row - 2][column].set_type(board[row - 1][column].get_type());
            board[row - 1][column].set_type(0);
        }else if(board[row - 1][column].get_type() != 0 && (cat)){
            board[row - 2][column].set_type(board[row - 1][column].get_type());
            board[row - 1][column].set_type(0);
        }
    }
    else if(row - 1 == 0 && (board[row - 1][column].get_type() == 1 || board[row - 1][column].get_type() == 2) && (kitten)){
        if(board[row - 1][column].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row - 1][column].get_type() == 2){//p2k
            p2k++;
        }
        board[row - 1][column].set_type(0);
    }
    else if(row - 1 >= 0 && row - 1 == 0 && board[row - 1][column].get_type() != 0 && (cat)){
        if(board[row - 1][column].get_type() == 1){//p1k
            p1k++;
        }else if(board[row - 1][column].get_type() == 2){//p2k
            p2k++;
        }else if(board[row - 1][column].get_type() == 3){//p1c
            p1c++;
        }else if(board[row - 1][column].get_type() == 4){//p2c
            p2c++;
        }
        board[row - 1][column].set_type(0);
    }

    //top right corner space
    if(row - 2 >= 0 && column + 2 < 6 && board[row - 2][column + 2].get_type() == 0){//checking booping space is empty
        if((board[row - 1][column + 1].get_type() == 1 || board[row - 1][column + 1].get_type() == 2) && (kitten)){
            board[row - 2][column + 2].set_type(board[row - 1][column + 1].get_type());
            board[row - 1][column + 1].set_type(0);
        }else if(board[row - 1][column + 1].get_type() != 0 && (cat)){
            board[row - 2][column + 2].set_type(board[row - 1][column + 1].get_type());
            board[row - 1][column + 1].set_type(0);
        }
    }else if((row - 1 == 0 || column + 1 == 5) && (board[row - 1][column + 1].get_type() == 1 || board[row - 1][column + 1].get_type() == 2) && (kitten)){
        if(board[row - 1][column + 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row - 1][column + 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row - 1][column + 1].set_type(0);
    }
    else if(row - 1 >= 0 && column + 1 < 6 && (row - 1 == 0 || column + 1 == 5) && board[row - 1][column + 1].get_type() != 0 && (cat)){
        if(board[row - 1][column + 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row - 1][column + 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row - 1][column + 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row - 1][column + 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row - 1][column + 1].set_type(0);
    }


    //directly right space
    if(column + 2 < 6 && board[row][column + 2].get_type() == 0){//checking booping space is empty
        if((board[row][column + 1].get_type() == 1 || board[row][column + 1].get_type() == 2) && (kitten)){
            board[row][column + 2].set_type(board[row][column + 1].get_type());
            board[row][column + 1].set_type(0);
        }else if(board[row][column + 1].get_type() != 0 && (cat)){
            board[row][column + 2].set_type(board[row][column + 1].get_type());
            board[row][column + 1].set_type(0);
        }
    }else if(column + 1 == 5 && (board[row][column + 1].get_type() == 1 || board[row][column + 1].get_type() == 2) && (kitten)){
        if(board[row][column + 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row][column + 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row][column + 1].set_type(0);
    }
    else if(column + 1 < 6 && column + 1 == 5 && board[row][column + 1].get_type() != 0 && (cat)){
        if(board[row][column + 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row][column + 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row][column + 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row][column + 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row][column + 1].set_type(0);
    }

    //bottom right corner space
    if(row + 2 < 6 && column + 2 < 6 && board[row + 2][column + 2].get_type() == 0){//checking booping space is empty
        if((board[row + 1][column + 1].get_type() == 1 || board[row + 1][column + 1].get_type() == 2) && (kitten)){
            board[row + 2][column + 2].set_type(board[row + 1][column + 1].get_type());
            board[row + 1][column + 1].set_type(0);
        }else if(board[row + 1][column + 1].get_type() != 0  && (cat)){
            board[row + 2][column + 2].set_type(board[row + 1][column + 1].get_type());
            board[row + 1][column + 1].set_type(0);
        }
    }else if((row + 1 == 5 || column + 1 == 5) && (board[row + 1][column + 1].get_type() == 1 || board[row + 1][column + 1].get_type() == 2) && (kitten)){
        if(board[row + 1][column + 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row + 1][column + 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row + 1][column + 1].set_type(0);
    }
    else if(row + 1 < 6 && column + 1 < 6 && (row + 1 == 5 || column + 1 == 5) && board[row + 1][column + 1].get_type() != 0 && (cat)){
        if(board[row + 1][column + 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row + 1][column + 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row + 1][column + 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row + 1][column + 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row + 1][column + 1].set_type(0);
    }

    //bottom middle space
    if(row + 2 < 6 && board[row + 2][column].get_type() == 0){//checking booping space is empty
        if((board[row + 1][column].get_type() == 1 || board[row + 1][column].get_type() == 2) && (kitten)){
            board[row + 2][column].set_type(board[row + 1][column].get_type());
            board[row + 1][column].set_type(0);
        }else if(board[row + 1][column].get_type() != 0 && (cat)){
            board[row + 2][column].set_type(board[row + 1][column].get_type());
            board[row + 1][column].set_type(0);
        }
    }else if(row + 1 == 5 && (board[row + 1][column].get_type() == 1 || board[row + 1][column].get_type() == 2) && (kitten)){
        if(board[row + 1][column].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row + 1][column].get_type() == 2){//p2k
            p2k++;
        }
        board[row + 1][column].set_type(0);
    }
    else if(row + 1 < 6 && row + 1 == 5 && board[row + 1][column].get_type() != 0 && (cat)){
        if(board[row + 1][column].get_type() == 1){//p1k
            p1k++;
        }else if(board[row + 1][column].get_type() == 2){//p2k
            p2k++;
        }else if(board[row + 1][column].get_type() == 3){//p1c
            p1c++;
        }else if(board[row + 1][column].get_type() == 4){//p2c
            p2c++;
        }
        board[row + 1][column].set_type(0);
    }

    //bottom left corner space
    if(row + 2 < 6 && column - 2 >= 0 && board[row + 2][column - 2].get_type() == 0){//checking booping space is empty
        if((board[row + 1][column - 1].get_type() == 1 || board[row + 1][column - 1].get_type() == 2) && (kitten)){
            board[row + 2][column - 2].set_type(board[row + 1][column - 1].get_type());
            board[row + 1][column - 1].set_type(0);
        }else if(board[row + 1][column - 1].get_type() != 0 && (cat)){
            board[row + 2][column - 2].set_type(board[row + 1][column - 1].get_type());
            board[row + 1][column - 1].set_type(0);
        }
    }else if((row + 1 == 5 || column - 1 == 0 ) && (board[row + 1][column - 1].get_type() == 1 || board[row + 1][column - 1].get_type() == 2) && (kitten)){
        if(board[row + 1][column - 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row + 1][column - 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row + 1][column - 1].set_type(0);
    }
    else if((row + 1 == 5 || column - 1 == 0) && row + 1 < 6 && column - 1 >= 0 && board[row + 1][column - 1].get_type() != 0 && (cat)){
        if(board[row + 1][column - 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row + 1][column - 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row + 1][column - 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row + 1][column - 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row + 1][column - 1].set_type(0);
    }

    //directly left space
    if(column - 2 >= 0 && board[row][column - 2].get_type() == 0){//checking booping space is empty
        if((board[row][column - 1].get_type() == 1 || board[row][column - 1].get_type() == 2) && (kitten)){
            board[row][column - 2].set_type(board[row][column - 1].get_type());
            board[row][column - 1].set_type(0);
        }else if(board[row][column - 1].get_type() != 0 && (cat)){
            board[row][column - 2].set_type(board[row][column - 1].get_type());
            board[row][column - 1].set_type(0);
        }
    }else if(column - 1 == 0 && (board[row][column - 1].get_type() == 1 || board[row][column - 1].get_type() == 2) && (kitten)){
        if(board[row][column - 1].get_type() == 1){//p1k
            p1k++;
        }
        else if(board[row][column - 1].get_type() == 2){//p2k
            p2k++;
        }
        board[row][column - 1].set_type(0);
    }
    else if(column - 1 >= 0 && column - 1 == 0 && board[row][column - 1].get_type() != 0 && (cat)){
        if(board[row][column - 1].get_type() == 1){//p1k
            p1k++;
        }else if(board[row][column - 1].get_type() == 2){//p2k
            p2k++;
        }else if(board[row][column - 1].get_type() == 3){//p1c
            p1c++;
        }else if(board[row][column - 1].get_type() == 4){//p2c
            p2c++;
        }
        board[row][column - 1].set_type(0);
    }
}

void Boop::make_cat(const string& move){
    //Interpreting Move
    //c or k part
    char direction = toupper(move.at(0));
    // column part
    //char column = move.at(1);
    int column = move.at(1) - '1'; 
    //row part
    int row = toupper(move.at(2)) - 'U';

    //Diagonal Row of Kittens
    if(next_mover() == HUMAN && (direction == 'd' || direction == 'D')){//PLayer 1's turn
        if(board[row - 2][column + 2].get_type() == 1 || board[row - 2][column + 2].get_type() == 3){//checking for right diagonal
            if(board[row - 1][column + 1].get_type() == 1 || board[row - 1][column + 1].get_type() == 3){
                //setting all spaces to 0 and adding pieces back to bank
                board[row - 1][column + 1].set_type(3);
                board[row - 2][column + 2].set_type(3);
                board[row][column].set_type(3);
                return_to_bank(board[row - 1][column + 1]);
                return_to_bank(board[row - 2][column + 2]);
                return_to_bank(board[row][column]);
            }
        }
        else if(board[row - 2][column - 2].get_type() == 1 || board[row - 2][column - 2].get_type() == 3){//checking for left diagonal
            if(board[row - 1][column - 1].get_type() == 1 || board[row - 1][column - 1].get_type() == 3){
                //setting all spaces to 0 and adding pieces back to bank
                board[row - 1][column - 1].set_type(3);
                board[row - 2][column - 2].set_type(3);
                board[row][column].set_type(3);
                return_to_bank(board[row - 1][column - 1]);
                return_to_bank(board[row - 2][column - 2]);
                return_to_bank(board[row][column]);
            }
        }
    }
    else if (next_mover() == COMPUTER && (direction == 'd' || direction == 'D')){//Player 2's Turn
         if(board[row - 2][column + 2].get_type() == 2 || board[row - 2][column + 2].get_type() == 4){//checking for right diagonal
            if(board[row - 1][column + 1].get_type() == 2 || board[row - 1][column + 1].get_type() == 4){
                //setting all spaces to 0 and adding pieces back to bank
                board[row - 1][column + 1].set_type(4);
                board[row - 2][column + 2].set_type(4);
                board[row][column].set_type(4);
                return_to_bank(board[row - 1][column + 1]);
                return_to_bank(board[row - 2][column + 2]);
                return_to_bank(board[row][column]);
            }
        }
        else if(board[row - 2][column - 2].get_type() == 2 || board[row - 2][column - 2].get_type() == 4){//checking for left diagonal
            if(board[row - 1][column - 1].get_type() == 2 || board[row - 1][column - 1].get_type() == 4){
                //setting all spaces to 0 and adding pieces back to bank
                board[row - 1][column - 1].set_type(4);
                board[row - 2][column - 2].set_type(4);
                board[row][column].set_type(4);
                return_to_bank(board[row - 1][column - 1]);
                return_to_bank(board[row - 2][column - 2]);
                return_to_bank(board[row][column]);
            }
        }
    }

    //Horizontal Row of Kittens
    if(next_mover() == HUMAN && (direction == 'h' || direction == 'H')){//Player 1's turn
        if(board[row][column + 2].get_type() == 1 || board[row][column + 2].get_type() == 3){//checking for horizontal to the right
            if(board[row][column + 1].get_type() == 1 || board[row][column + 1].get_type() == 3){
                //setting all spaces to 0 and adding pieces back to bank
                board[row][column + 1].set_type(3);
                board[row ][column + 2].set_type(3);
                board[row][column].set_type(3);
                return_to_bank(board[row][column + 1]);
                return_to_bank(board[row][column + 2]);
                return_to_bank(board[row][column]);
            }
        }
    }
    else if(next_mover() == COMPUTER && (direction == 'h' || direction == 'H')){//Player 2's Turn
        if(board[row][column + 2].get_type() == 2 || board[row][column + 2].get_type() == 4){//checking for horizontal to the right
            if(board[row][column + 1].get_type() == 2 || board[row][column + 1].get_type() == 4){
                //setting all spaces to 0 and adding pieces back to bank
                board[row][column + 1].set_type(4);
                board[row][column + 2].set_type(4);
                board[row][column].set_type(4);
                return_to_bank(board[row][column + 1]);
                return_to_bank(board[row][column + 2]);
                return_to_bank(board[row][column]);
            }
        }
    }

    //Vertical Row of Kittens
    if(next_mover() == HUMAN && (direction == 'v' || direction == 'V')){//Player 1's turn
        if(board[row + 2][column].get_type() == 1 || board[row + 2][column].get_type() == 3){//checking downwards
            if(board[row + 1][column].get_type() == 1 || board[row + 1][column].get_type() == 3){
                //setting all spaces to 0 and adding pieces back to bank
                board[row + 1][column].set_type(3);
                board[row + 2][column].set_type(3);
                board[row][column].set_type(3);
                return_to_bank(board[row + 1][column]);
                return_to_bank(board[row + 2][column]);
                return_to_bank(board[row][column]);
            }
        }
    }
    else if(next_mover() == COMPUTER && (direction == 'v' || direction == 'V')){//Player 2's Turn
        if(board[row + 2][column].get_type() == 2 || board[row + 2][column].get_type() == 4){//checking downwards
            if(board[row + 1][column].get_type() == 2 || board[row + 1][column].get_type() == 4){
                //setting all spaces to 0 and adding pieces back to bank
                board[row + 1][column].set_type(4);
                board[row + 2][column].set_type(4);
                board[row][column].set_type(4);
                return_to_bank(board[row + 1][column]);
                return_to_bank(board[row + 2][column]);
                return_to_bank(board[row][column]);
            }
        }
    }
}




game* Boop::clone() const{
    return new Boop(*this);
}

void Boop::compute_moves(std::queue<std::string>& moves) const{
    //needs to find all legal moves computer can make and push into queue
    //make move string
    string move = "   ";
    //cycle through all combinations check if is legal and then push in queue
    for(char r = '1'; r < '7'; r++){
        for(char c = 'U'; c < '')
            move[0] = 'k';
            move[1] = r;
            move[2] = c;
    }
    if(is_legal(move)){
        moves.push(move);
    }
}

void Boop::display_status() const{
    //top of the board
    cout << endl << endl << endl << "    1     2     3     4     5     6" << endl;
    cout << "______________________________________" << endl;

    int row = 0;
    for(int inside_row = 0; inside_row < 18; inside_row++){
        
        if(inside_row == 1){
            cout << "U|";
        }
        else if(inside_row == 4){
            cout << "V|";
        }
        else if(inside_row == 7){
            cout << "W|";
        }
        else if(inside_row == 10){
            cout << "X|";
        }
        else if(inside_row == 13){
            cout << "Y|";
        }
        else if(inside_row == 16){
            cout << "Z|";
        }else{
            cout << " |";
        }
    
        //KEY: p1k = 1, p2k = 2, p1c = 3, p2c = 4, empty = 0
            for(int column = 0; column < SIZE; column++){
                if(board[row][column].get_type() == 0){
                    cout << "     ";
                }
                else if(board[row][column].get_type() == 1){//p1k
                    cout << RED;
                    if(inside_row % 3 == 1){
                        cout << "{^_^}";
                    }
                    else{
                        cout << "     ";
                    }
                    cout << RESET;
                }
                else if(board[row][column].get_type() == 2){//p2k
                    cout << BLUE;
                    if(inside_row % 3 == 1){
                        cout << "{^_^}";
                    }
                    else{
                        cout << "     ";
                    }
                    cout << RESET;
                }
                else if(board[row][column].get_type() == 3){//p1c
                    cout << RED;
                    if(inside_row % 3 == 0){
                        cout << " ^_^ ";
                    }
                    if(inside_row % 3 == 1){
                        cout << "{*_*}";
                    }
                    if(inside_row % 3 == 2){
                        cout << " ~ ~ ";
                    }
                    cout << RESET;
                }
                else if(board[row][column].get_type() == 4){//p2c
                    cout << BLUE;
                    if(inside_row % 3 == 0){
                        cout << " ^_^ ";
                    }
                    if(inside_row % 3 == 1){
                        cout << "{*_*}";
                    }
                    if(inside_row % 3 == 2){
                        cout << " ~ ~ ";
                    }
                    cout << RESET;
                }
                cout << "|";
            }
            
        cout << endl;
        if(inside_row % 3 == 2){
            cout << "--------------------------------------" << endl;
            row++;
        }
    }

    //showing user their available pieces
    cout << endl;
    cout << "Number of Player 1 Kittens Available: " << p1k << endl;
    cout << "Number of Player 1 Cats Available:    " << p1c << endl;
    cout << "Number of Player 2 Kittens Available: " << p2k << endl;
    cout << "Number of Player 2 Cats Available:    " << p2c << endl;
}

int Boop::evaluate() const{
    int const KITTEN = 10;
    int const CAT = 20;
    int const NEAR = 5;
    int human_count = 0;
    int computer_count = 0;
    for(int row = 0; row < 6; row++){
        for(int column = 0; column < 6; column++){
            int space_type = board[row][column].get_type();
            if(space_type == 1 || space_type == 3){//human kitten or human cat
                if(row - 1 >= 0 && board[row - 1][column].get_type() == space_type){
                    human_count = human_count + NEAR;
                }
                //top right corner
                if(row - 1 >= 0 && column + 1 < 6 && board[row - 1][column + 1].get_type() == space_type){
                    human_count = human_count + NEAR;
                }
                //directly right
                if(column + 1 < 6 && board[row][column + 1].get_type() == space_type){
                    human_count = human_count + NEAR; 
                }
                //bottom right corner
                if(row + 1 < 6 && column + 1 < 6 && board[row + 1][column + 1].get_type() == space_type){
                    human_count = human_count + NEAR; 
                }
                //bottom middle
                if(row + 1 < 6 && board[row + 1][column].get_type() == space_type){
                    human_count = human_count + NEAR; 
                }
                //bottom left corner
                if(row + 1 < 6 && column - 1 >= 0 && board[row + 1][column - 1].get_type() == space_type){
                   human_count = human_count + NEAR; 
                }
                //directly left
                if(column - 1 >= 0 && board[row][column - 1].get_type() == space_type){
                    human_count = human_count + NEAR; 
                }
                //top left corner
                if(row - 1 >= 0 && column - 1 >= 0 && board[row - 1][column - 1].get_type() == space_type){
                    human_count = human_count + NEAR; 
                }
            }else if(space_type == 2 || space_type == 4){//computer cat or computer kitten
                if(row - 1 >= 0 && board[row - 1][column].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //top right corner
                if(row - 1 >= 0 && column + 1 < 6 && board[row - 1][column + 1].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //directly right
                if(column + 1 < 6 && board[row][column + 1].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //bottom right corner
                if(row + 1 < 6 && column + 1 < 6 && board[row + 1][column + 1].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //bottom middle
                if(row + 1 < 6 && board[row + 1][column].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //bottom left corner
                if(row + 1 < 6 && column - 1 >= 0 && board[row + 1][column - 1].get_type() == space_type){
                   computer_count = computer_count + NEAR;
                }
                //directly left
                if(column - 1 >= 0 && board[row][column - 1].get_type() == space_type){
                    computer_count = computer_count + NEAR;
                }
                //top left corner
                if(row - 1 >= 0 && column - 1 >= 0 && board[row - 1][column - 1].get_type() == space_type){
                   computer_count = computer_count + NEAR;
                }
            }

            switch(space_type){
                case 1://human kitten
                    human_count = human_count + KITTEN;
                    break;
                case 2://computer kitten
                    computer_count = computer_count + KITTEN;
                    break;
                case 3://human cat
                    human_count = human_count + CAT;
                    break;
                case 4://computer cat
                    computer_count = computer_count + CAT;
                    break;
            }
        }
    }

    //in the bank cats more than kitten, less than on board values
    //three cats in a row is very good, 100000
    return computer_count - human_count;
}

Boop::who Boop::winning( ) const{
    //player 1 or 2 winning
    bool p1 = false;
    bool p2 = false;

    for (int row = 0; row < 6; row ++){
    for (int column = 0; column < 6; column ++){
        for (int r = -1; r <= 1; r++){
        for (int c = -1; c <= 1; c++){
            if (r == 0 && c == 0){//center piece
                continue;
            }
            if (board[row][column].get_type() < 3){//piece is not a cat
                continue;
            }

            //Out of bounds cases - Edges
            if (0 > row + r || row + r >= 6){
                continue; 
            }
            if (0 > row - r || row - r >= 6){
                continue;
            }
            if (0 > column + c || column + c >= 6){
                continue;
            }
            if (0 > column - c || column - c >= 6){
                continue; 
            }

            //Different type of cat then needed
            if (board[row][column].get_type() != board[row + r][column + c].get_type()){
                continue; 
            }
            if (board[row][column].get_type() != board[row - r][column - c].get_type()){
                continue;
            }

            //All tests passed, check cat color and set win flag
            if (board[row][column].get_type() == 3){
                p1 = true;
            }
            else{
                p2 = true;
            }
        }
        }
    }
    }

    if(p1 && p2){//tie
        return NEUTRAL;
    }
    if (p1){//player 1 won
        return HUMAN;
    }
    if (p2){//player 2 won
        return COMPUTER;
    }
    return NEUTRAL;
}

bool Boop::is_game_over() const{
    if((p1c == 0 && p1k == 0)|| (p2c == 0 && p2k == 0)){//8 cats on the board
        return true;
    }
    //checking each row individually to see if there are 3 cats in a row
    for(int row = 0; row < 6; row++){
        for(int column = 0; column < 6; column++){
            int space_type = board[row][column].get_type();
            if(space_type == 3 || space_type == 4){//there's a cat
                //top middle 
                if(row - 1 >= 0 && board[row - 1][column].get_type() == space_type){
                    if(row - 2 >= 0 && board[row - 2][column].get_type() == space_type){
                        return true;
                    }
                }
                //top right corner
                if(row - 1 >= 0 && column + 1 < 6 && board[row - 1][column + 1].get_type() == space_type){
                    if(row - 2 >= 0 && column + 2 < 6 && board[row - 2][column + 2].get_type() == space_type){
                        return true;
                    }
                }
                //directly right
                if(column + 1 < 6 && board[row][column + 1].get_type() == space_type){
                    if(column + 2 < 6 && board[row][column + 2].get_type() == space_type){
                        return true;
                    }
                }
                //bottom right corner
                if(row + 1 < 6 && column + 1 < 6 && board[row + 1][column + 1].get_type() == space_type){
                    if(row + 2 < 6 && column + 2 < 6 && board[row + 2][column + 2].get_type() == space_type){
                        return true;
                    } 
                }
                //bottom middle
                if(row + 1 < 6 && board[row + 1][column].get_type() == space_type){
                    if(row + 2 < 6 && board[row + 2][column].get_type() == space_type){
                        return true;
                    }
                }
                //bottom left corner
                if(row + 1 < 6 && column - 1 >= 0 && board[row + 1][column - 1].get_type() == space_type){
                    if(row + 2 < 6 && column - 2 >= 0 && board[row + 2][column - 2].get_type() == space_type){
                        return true;
                    }
                }
                //directly left
                if(column - 1 >= 0 && board[row][column - 1].get_type() == space_type){
                    if(column - 2 >= 0 && board[row][column - 2].get_type() == space_type){
                        return true;
                    }
                }
                //top left corner
                if(row - 1 >= 0 && column - 1 >= 0 && board[row - 1][column - 1].get_type() == space_type){
                    if(row - 2 >= 0 && column - 2 >= 0 && board[row - 2][column - 2].get_type() == space_type){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Boop::is_legal(const string& move) const{
    //Is string length 3
    if (move.length() != 3) return false;
    //Interpreting Move
    //c or k part
    char animal = toupper(move.at(0));
    // column part
    //char column = move.at(1);
    int column = move.at(1) - '1'; 
    //row part
    int row = toupper(move.at(2)) - 'U';


    //Checking input is 1,2,3,4,5, or 6
    if(column > 5 || column < 0){
        return false;
    } 

    //Checking input is U, V, W, X, Y, or Z
    if(row > 5 || row < 0 ){
        return false;
    }

    //Checking spot is empty
    if(board[row][column].get_type() != 0){
        return false;
    }

    //Checking input is C, c, k, or K
    if((animal != 'C' && animal != 'c') && (animal != 'K' && animal != 'k')){
        return false;
    }

    //Checking Players have enough pieces
    if(next_mover() == HUMAN){//Player 1
        if((animal == 'C' || animal == 'c') && p1c == 0){
            cout << "Invailid option, you have no cats available" << endl;
            return false;
        }
        if((animal == 'K' || animal == 'k' ) && p1k == 0){
            cout << "Invalid option, you have no kittens available" << endl;
            return false;
        }
    }else{//Player 2
        if((animal == 'C' || animal == 'c') && p2c == 0){
            cout << "Invalid option, you have no cats available" << endl;
            return false;
        }
        if((animal == 'K' || animal == 'k' ) && p2k == 0){
            cout << "Invalid option, you have no kittens available" << endl;
            return false;
        }
    }


    //if no other conditions are met then move is legal
    return true;
}