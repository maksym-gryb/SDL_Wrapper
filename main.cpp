/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: interloper
 *
 * Created on February 2, 2016, 10:13 AM
 */

#include <iostream>

#include "Game.h"

int main(int argc, char *argv[])
{
    return Game::getInstance()->run(NULL);
}
