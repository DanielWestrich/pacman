/*
 * Name: Daniel Westrich
 * Title: game.cpp
 * Purpose: to define the Pacman game
 */

#include <iostream>
#include "game.h"
#include "termfuncs.h"

using namespace std;

/* Constructor */
// Arguments: none
// Returns: none
Game::Game()
{
        level = 1;
        level_changes = true;  // this is true only if the level is changed
        initialize_board();  // clears the board
}

// Purpose: to initialize the board with all spaces
// Arguments: a 2D char board array
// Returns: none
void Game::initialize_board()
{
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			board[i][j] = ' ';
		}
	}
}

/* print_manual()
 * Purpose:   Prints the manual and stalls until the user types a character
 * Arguments: None
 * Returns:   None
 */
void Game::print_manual()
{
        screen_clear();
        cout << "PACMAN GAME\n"
                "            \n"
                " Move left:    " << CMD_LFT << "\n"
                " Move right:   " << CMD_RGT << "\n"
                " Move up:      " << CMD_UP  << "\n"
                " Move down:    " << CMD_DWN << "\n"
                "\n"
                " Collect all the dots. They look like: " << DOT << "\n"
                " Avoid the ghosts.     They look like: " << GHOST << "\n"
                "\n"
                " Difficulty: "  // displays the difficulty settings
                "\n"
                " Press 1 for Easy "
                "\n"
                " Press 2 for Medium "
                "\n"
                " Press 3 for Hard "
                "\n"
                " Good luck!\n"
                "\n";
//                " Press any key to continue...\n";

        do{  // input is used to set the difficulty of the game
                input = getachar();
        }while(input != '1' and input != '2' and input != '3');
}

// Purpose: to set the difficulty of the game
// Arguments: none
// Returns: none
void Game::set_difficulty() // sets the difficulty of the game using "input"
{
	if(input == '1'){  // sets "difficulty" using "input"
		difficulty = 3;
	}
	if(input == '2'){
		difficulty = 2;
	}
	if(input == '3'){
		difficulty = 1;
	}
}

/*
 * Purpose: runs the game
 * Arguments: none
 * Returns: none
 */
void Game::run()
{
	set_difficulty();
	while(level <= NUM_LEVELS and p.is_alive()){
                level_change();
                char command = getacharnow(SPEED * difficulty); 
						      // gets a new command
                if(p.move(board, command)){ // moves p, checks if eats dot
                        check_which_eaten(); // checks which dot was eaten
                }
                if(p.get_num_moves() % difficulty == 0){  // moves ghosts
                        if(eats_pacman(p.get_row(), p.get_col())){ // if p eaten
                                p.alive = false; // if eats p, kills p man
                        }
                }
                print_all();  // prints everything (p, ghosts, boulders, etc.)
                if(all_eaten()){ // checks if all dots have been eaten
			p.add_to_score(LEVEL_REWARD);
			level_changes = true;
			print_all();
			level++;
		}
	}
        if(p.is_alive() == false){
                cout << "Game Over." << endl;
        }else{  // if game ends and pacman is still alive, then the user won
                cout << "You won!!" << endl;
        }
}

// Purpose: to change the level
// Arguments: a 2D char board array
// Returns: none
void Game::level_change()
{
        if(level_changes){
                initialize_board();
                p.center();
		print_boulders();
                initialize_ghosts();
		print_ghosts();
                p.place_on_board(board);
                initialize_dots();
                place_dots();
                print_board();
                level_changes = false;
                cout << "Level " << level << ": Press any key to start" << endl;
                getachar();
        }
}

// Purpose: to print everything on the board
// Arguments: a 2D char board array
// Returns: none
void Game::print_all()
{
        screen_clear();
        initialize_board();
        print_boulders();
	p.place_on_board(board);
        place_dots();
	print_ghosts();
        print_board();
        cout << "Score: " << p.get_score() << endl;
}

/*
 * Purpose: to set all the dots as not eaten
 * Arguments: none
 * Returns: none
 */
bool Game::all_eaten()
{	
	int num_eaten = 0;  // counter for the number of dots eaten
	for(int i = 0; i < level * DOTS_PER_LEVEL; i++){
		if(dots[i].was_eaten()){
			num_eaten++;  // increment for each dot eaten per level
		}
	}
	if(num_eaten == level * DOTS_PER_LEVEL){
		return true;  // if all dots are eaten, return true
        }
        return false;
}

// Purpose: to initialize the dots
// Arguments: none
// Returns: none
void Game::initialize_dots()
{
	for(int i = 0; i < level * DOTS_PER_LEVEL; i++){
		dots[i].set_eaten(false);
		dots[i].set_random_location(board);
	}
}

/*
 * Purpose: to set and place each dot
 * Arguments: a 2D char board used as an input in two included functions
 * Returns: none
 */
void Game::place_dots()
{
	for(int i = 0; i < level * DOTS_PER_LEVEL; i++){
		if(dots[i].was_eaten() == false){
			dots[i].place_on_board(board);  // places dots
		}
	}
}

/*
 * Purpose: to print each boulder on the board
 * Arguments: none
 * Returns: none
 */
void Game::print_boulders()
{
	for(int i = 0; i < level; i++){
		boulders[i].place_on_board(board);
	}
}

/*
 * Purpose: to print the edges of the board itself
 * Arguments: none
 * Returns: none
 */
void Game::print_board()
{
        screen_home();
	print_horiz_boarder();
	for(int i = 0; i < ROWS; i++){
		cout << BORD_SIDE;
		for(int j = 0; j < COLS; j++){
			cout << board[i][j];
		}
	cout << BORD_SIDE << endl;
	}
	print_horiz_boarder();
}

// Purpose: to print the lateral portions of the board
// Arguments: none
// Returns: none
void Game::print_horiz_boarder()
{
	cout << BORD_CORN;
	for(int i = 0; i < COLS; i++){
		cout << BORD_TOP;
	}
	cout << BORD_CORN << endl;
}

// Purpose: to check if a dot has been eaten
// Arguments: Pacman p, and an int i
// Returns: none
void Game::check_which_eaten()
{
        for(int i = 0; i < level * 5; i++){  // checks which dot has been eaten
                if(dots[i].is_at(p.get_row(), p.get_col()) == true){
                        dots[i].set_eaten(true);
                        p.add_to_score(DOT_REWARD);
                }
        }
}

// Purpose: to set the location of each ghost
// Arguments: none
// Returns: none
void Game::initialize_ghosts()
{
	ghosts[0].set_location(0,0);
	ghosts[1].set_location(0, COLS-1);
	ghosts[2].set_location(ROWS-1, 0);
	ghosts[3].set_location(ROWS-1, COLS-1);
}

// Purpose: to print each ghost
// Arguments: a 2D char board array
// Returns: none
void Game::print_ghosts()
{
	ghosts[0].place_on_board(board);
	ghosts[1].place_on_board(board);
	ghosts[2].place_on_board(board);
	ghosts[3].place_on_board(board);
}

// Purpose: to check if a ghost has eaten pacman
// Arguments: a 2D char board array, int r, int c
// Returns: bool
bool Game::eats_pacman(int r, int c)
{
        for(int i = 0; i < NUM_GHOSTS; i++){
                if(ghosts[i].move(board, r, c)){  // checks if ghost eats pacman
                        board[p.get_row()][p.get_col()] = GHOST;
                        return true;
                }
        }
        return false;
}
