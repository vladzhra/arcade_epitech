/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** main.cpp
*/

#include "Core.hpp"
#include <iostream>

void displayUsage(void)
{
    std::cout << "Usage: ./arcade lib/arcade_ncurses.so\n\tUse 'L' key for switch the graphic lib" << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2 || std::string(argv[1]) == "-h") {
        displayUsage();
        if (argc != 2)
            return 84;
        if (std::string(argv[1]) == "-h")
            return 0;
    }
    try {
        DLLoader<IGraphicModule> loader1(argv[1]);
        Core core;
        core.start(loader1, std::string(argv[1]));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
