/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** libNibbler.cpp
*/

#ifndef LIBNIBBLER_HPP
    #define LIBNIBBLER_HPP
#include "IGameModule.hpp"
#include <deque>

class Nibbler : public IGameModule {
public:
    Nibbler();
    ~Nibbler() override;
    void run() override;
    int move(std::string direction) override;
    std::vector<std::string> getMap() override;
    void getPosition(int& x, int& y) const override;
    void setPosition(int x, int y) override;
    int getLife() const override;
    int getScore() const override;
    std::string getScoreAsString(void) const override;
    std::vector<std::string> getValidDirections(void) const override;
    void setLife(int life) override;
    void handle_anim() override;
    void generate_apple() override;
    void restart() override;
    const std::string& getName() const override {return moduleName;};
protected:
    struct BodySegment {
        int x;
        int y;
        std::string direction;
    };
    void updateCoordinates(size_t &new_x, size_t &new_y, const std::string &direction);
    bool isOutOfBounds(size_t new_x, size_t new_y);
    bool isCollision(size_t new_x, size_t new_y);
    bool isApple(size_t new_x, size_t new_y);
    void updateBody(bool apple_eaten);
    void updateMap(size_t new_x, size_t new_y);
    bool isBodyCollision(size_t new_x, size_t new_y);
    void updateLevel(void);
    void checkForTurns(void);
    void resetSnake(void);
    std::vector<std::string> _game_map;
    int _score;
    int _life;
    int _x;
    int _y;
    int _x_apple;
    int _y_apple;
    int level;
    std::vector<BodySegment> _body;
    std::deque<std::pair<int, int>> body;
    std::string _current_direction;
private:
    std::vector<std::string> _game_map_level1;
    std::vector<std::string> _game_map_level2;
    std::vector<std::string> _game_map_level3;
    const std::string moduleName{"Nibbler"};
};

extern "C" IGameModule* entryPoint() { return new Nibbler(); }

#endif //LIBNIBBLER_HPP