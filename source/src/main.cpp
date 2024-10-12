/*  main.cpp
 *  the entry point of the program
 */

#ifdef _WIN32   
#define SDL_MAIN int SDL_main(int argc, char* argv[])
#define SEPARATOR "\\"       
#else
#define SDL_MAIN int main(int argc, char* argv[])
#define SEPARATOR "/"          
#endif


#include "game.h"

 

#include <iostream>
#include <string>


SDL_MAIN {
    
    
    globals::SLASH = SEPARATOR;
    globals::EXECUTABLE_PATH = argv[0];
    globals::WORKING_FOLDER = globals::EXECUTABLE_PATH.substr(0, globals::EXECUTABLE_PATH.find_last_of(globals::SLASH));
    


    Game game;

    return EXIT_SUCCESS;

}