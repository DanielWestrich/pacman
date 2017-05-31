/* Name: Daniel Westrich
 * Title: pacman.cpp
 * Purpose: to define the pacman class
 */

#include <iostream>
#include "termfuncs.h"
#include "constants.h"
#include "pacman.h"

// Constructor
// Arguments: none
// Returns: none
Pacman::Pacman()
{
        alive = true;
        center();
        num_moves = 0;
        score = 0;
}

// Purpose: initializes pacman in the center of the board
// Arguments: none
// Returns: none
void Pacman::center()
{
        row = ROWS/2;
        col = COLS/2;
	head = UP;
}

// Purpose: moves pacman
// Arguments: a 2D char board array, a char command
// Returns: bool
bool Pacman::move(char board[][COLS], char command)
{
        bool dot_eaten = false;
	board[row][col] = ' ';
	go_lat(board, command);
	go_vert(board, command);
	wrap_around();
        dot_eaten = check_if_eaten(board);  // returns true if pacman eats a dot
	num_moves++;
	place_on_board(board);
        return dot_eaten;
}

// Purpose: moves pacman laterally
// Arguments: a 2D char board array, a char command
// Returns: none
void Pacman::go_lat(char board[][COLS], char command)
{ // vert and lat were split so that the function would not exceed the limit
	if(direction(command) == RIGHT){
		head = RIGHT;
		if(hits_boulder_lat(board, head) == false){
			col++;
		}
	}
	if(direction(command) == LEFT){
		head = LEFT;
		if(hits_boulder_lat(board, head) == false){
			col--;
		}
	}
}

// Purpose: moves pacman vertically
// Arguments: a 2D char board array, a char command
// Returns: none
void Pacman::go_vert(char board[][COLS], char command)
{
	if(direction(command) == UP){
		head = UP;
		if(hits_boulder_vert(board, head) == false){
			row--;
		}
	}
	if(direction(command) == DOWN){
		head = DOWN;
		if(hits_boulder_vert(board, head) == false){
			row++;
		}
	}
}

// Purpose: to check if pacman is hitting a boulder
// Arguments: a 2d char board array, a char head
// Returns: bool
bool Pacman::hits_boulder_lat(char board[][COLS], char head)
{
	if(head == RIGHT){
                if(col == COLS-1 and board[row][0] == BOULDER){
                        return true; 
                } // if boulder prevents wrap around, return true
		if(board[row][col+1] == BOULDER){
			return true;
		}else{
			return false;
		}
	}
	if(head == LEFT){
                if(col == 0 and board[row][COLS-1] == BOULDER){
                        return true;
                }
		if(board[row][col-1] == BOULDER){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

// Purpose: to check if pacman is hitting a boulder
// Arguments: a 2d char board array, a char head
// Returns: bool
bool Pacman::hits_boulder_vert(char board[][COLS], char head)
{ // vert and lat were split so that the function would not exced the limit
	if(head == UP){
                if(row == 0 and board[ROWS-1][col] == BOULDER){
                        return true;
                }
		if(board[row-1][col] == BOULDER){
			return true;
		}else{
			return false;
		}
	}
	if(head == DOWN){
                if(row == ROWS-1 and board[0][col] == BOULDER){
                        return true;
                }
		if(board[row+1][col] == BOULDER){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

// Purpose: to wrap around the board
// Arguments: none
// Returns: none
void Pacman::wrap_around()
{
	if(row < 0){
		row = ROWS-1;
	}
	if(row > ROWS-1){
		row = 0;
	}
	if(col < 0){
		col = COLS-1;
	}
	if(col > COLS-1){
		col = 0;
	}
}	

// Purpose: to decide the direction in which pacman points
// Arguments: a char command
// Returns: char
char Pacman::direction(char command)
{
        if(command == CMD_UP){
                return UP;
        }
        if(command == CMD_DWN){
                return DOWN;
        }
        if(command == CMD_RGT){
                return RIGHT;
        }
        if(command == CMD_LFT){
                return LEFT;
        }else{
		return 1;
	}
}

// Purpose: to place pacman on the board
// Arguments: a 2d char board array
// Returns: none
void Pacman::place_on_board(char board[][COLS])
{
	if(board[row][col] != GHOST){
                board[row][col] = head;
        }
}

// Purpose: to get the number of moves made
// Arguments: none
// Returns: int
int Pacman::get_num_moves()
{
        return num_moves;
}

// Purpose: to set the col of pacman
// Arguments: an int i
// Returns: none
void Pacman::set_col(int i)
{
	col = i;
}

// Purpose: to set the row of pacman
// Arguments: an int i
// Returns: none
void Pacman::set_row(int i)
{
	row = i;
}
// Purpose: to get pacman's col
// Arguments: none
// Returns: int
int Pacman::get_col()
{
	return col;
}

// Purpose: to get pacman's row
// Arguments: none
// Returns: int
int Pacman::get_row()
{
	return row;
}

// Purpose: to get pacman's head     ;)
// Arguments: none
// Returns: char
char Pacman::get_head()
{
	return head;
}

// Purpose: to say whether pacman is at a specific location
// Arguments: an int r, an int c
// Returns: bool
bool Pacman::is_at(int r, int c)
{
        if(r == row and c == col){
                return true;
        }else{
                return false;
        }
}

// Purpose: to add to pacman's score
// Arguments: an int n
// Returns: none
void Pacman::add_to_score(int n)
{
        score += n;
}

// Purpose: to get pacman's score
// Arguments: none
// Returns: int
int Pacman::get_score()
{
        return score;
}

// Purpose: to return whether or not pacman is alive
// Arguments: none
// Returns: bool
bool Pacman::is_alive()
{
        return alive;
}

// Purpose: to check if pacman has eaten a dot
// Arguments: a 2D char board array
// Returns: bool
bool Pacman::check_if_eaten(char board[][COLS])
{
        if(board[row][col] == DOT){
                return true;
        }
        return false;
}

// Purpose: to delete the previous pacman character from the board
// Arguments: a 2D char board array
// Returns: none
void Pacman::clear_pacman(char board[][COLS])
{
        board[row][col] = ' ';
}
