/* Name: Daniel Westrich
   Title: ghost.cpp
   Purpose: to define the ghost class
*/

#include <iostream>
#include <cmath>
#include "termfuncs.h"
#include "constants.h"
#include "ghost.h"
#include "pacman.h"


// Constructor
// Arguments: none
// Returns: none
Ghost::Ghost()
{
	row = 0;
	col = 0;
}


bool Ghost::move(char board[][COLS], int target_r, int target_c)
{
        go(target_r, target_c, board);  // moves the ghost toward pacman
        place_on_board(board);  // prints the ghost
        if(is_at(target_r, target_c)){ // if ghost hits pacman, return true
                return true;
        }else{
                return false;
        }
}


void Ghost::place_on_board(char board[][COLS])
{
	board[row][col] = GHOST;
}

int Ghost::get_row()
{
	return row;
}

int Ghost::get_col()
{
	return col;
}

void Ghost::set_location(int r, int c)
{
	row = r;
	col = c;     
}

bool Ghost::is_at(int r, int c)
{
	if(r == row and c == col){
		return true;
	}else{
		return false;
	}
}

void Ghost::go(int r, int c, char board[][COLS])
{
        if((std::abs(r - row)) > (std::abs(c - col))){
                if(board[row+1][col] != GHOST and r > row){ //
                        row++;  // if next space does not have a ghost, move
                }
                if(board[row-1][col] != GHOST and r < row){
                        row--;
                }
        }else{
                if(board[row][col+1] != GHOST and c > col){
                        col++;
                }
                if(board[row][col-1] != GHOST and c < col){
                        col--;
                }
        }
}

