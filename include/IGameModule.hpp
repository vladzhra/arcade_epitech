/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** IGameModule.hpp
*/

#include <string>
#include <vector>
class IGameModule {
public:
    virtual ~IGameModule() = default;
    virtual void run() = 0;
    virtual int move(std::string direction) = 0;
    virtual std::vector<std::string> getMap() = 0;
    virtual void getPosition(int& x, int& y) const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual int getLife() const = 0;
    virtual int getScore() const = 0;
    virtual std::string getScoreAsString(void) const = 0;
    virtual std::vector<std::string> getValidDirections(void) const = 0;
    virtual void setLife(int life) = 0;
    virtual void handle_anim() = 0;
    virtual void generate_apple() = 0;
    virtual void restart() = 0;
    virtual const std::string& getName() const = 0;
protected:
    std::vector<std::string> _game_map;
};
