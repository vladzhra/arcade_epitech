/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley
** File description:
** arcade_ncurses
*/

#ifndef arcade_ncurses_HPP
#define arcade_ncurses_HPP
#include "IGraphicModule.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

class NcursesModule : public IGraphicModule {
public:
    NcursesModule();
    ~NcursesModule();
    void display(const std::vector<std::string>& game_map, const std::string &score) override;
    void run(void) override;
    void playSound(void) override {}
    std::string handle_events() override;
    const std::string& getName() const override { return moduleName; }
    void updateTexture(const std::string& direction) override;
    void drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) override;
    void displayGameName(std::string name) override;
protected:
    void displayGraphicName();
private:
    const std::string moduleName{"Ncurses"};
    int _key;
};

extern "C" IGraphicModule* entryPoint() { return new NcursesModule(); }

#endif