/*******************************************************************************
 * Name: Daniel Westrich
 * Title: main.cpp
 * Purpose: to run a Pacman game
 ******************************************************************************/

#include <iostream>
using namespace std;

#include "game.h"

int main()
{
        Game g;
        g.print_manual();
        g.run();
}

