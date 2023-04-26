/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** IGraphicModule.hpp
*/

#include <string>
#include <vector>
// #include "IElement.hpp"

class IGraphicModule {
public:
    virtual ~IGraphicModule() = default;
    virtual void run(void) = 0;
    virtual void playSound(void) = 0;
    virtual void display(const std::vector<std::string>& game_map, const std::string &score) = 0;
    virtual void updateTexture(const std::string& direction) = 0;
    virtual void drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) = 0;
    virtual std::string handle_events() = 0;
    virtual const std::string& getName() const = 0;
    virtual void displayGameName(std::string name) = 0;
};
