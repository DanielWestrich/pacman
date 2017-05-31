/* Name: Daniel Westrich
 * Title: dot.cpp
 * Purpose: to define the Dot class
 */

#include "dot.h"
#include "termfuncs.h"


// Constructor
// Arguments: none
// Returns: none
Dot::Dot()
{
        row = 0;
        col = 0;
        eaten = false;
}

/*
 * Purpose: to set the location of the dot
 * Arguments: a 2D char board
 * Returns: none
 */
void Dot::set_random_location(char board[][COLS])
{
        // keep picking random locations until the spaces are blank
        do{
                row = random_int(0, ROWS-1);
                col = random_int(0, COLS-1);
        }while( board[row][col] != ' ' );
}

/*
 * Purpose: to place the dot on the board, at its location
 * Arguments: a 2D char board array
 * Returns: none
 */
void Dot::place_on_board(char board[][COLS])
{
        if(was_eaten() == false){  // place all dots that have not been eaten
		            board[row][col] = DOT;
	      }else{
		            return;
	      }
}

/*
 * Purpose: to see if the dot is at a specific place on the board
 * Arguments: a 2D char board array
 * Returns: bool
 */
bool Dot::is_at(int r, int c)
{
        if(r == row and c == col){
                return true;
        }else{
                return false;
        }
}

/*
 * Purpose: to set whether the dot has been eaten
 * Arguments: bool
 * Returns: none
 */
void Dot::set_eaten(bool i)
{
        eaten = i;
}

/*
 * Purpose: to find whether the dot has been eaten
 * Arguments: bool
 * Returns: bool
 */
bool Dot::was_eaten()
{
        return eaten;
}

// Purpose: to get the dot's row
// Arguments: none
// Returns: int
int Dot::get_row()
{
	return row;
}

// Purpose: to get the dot's col
// Arguments: none
// Returns: int
int Dot::get_col()
{
	return col;
}


