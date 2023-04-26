/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_snake.cpp
*/

#ifndef ARCADE_SNAKE_HPP
    #define ARCADE_SNAKE_HPP
#include "IGameModule.hpp"
#include <deque>

class Snake : public IGameModule {
public:
    Snake();
    ~Snake() override;
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
    std::vector<std::string> _game_map;
    int _score;
    int _life;
    int _x;
    int _y;
    int _x_apple;
    int _y_apple;
    std::vector<BodySegment> _body;
    std::deque<std::pair<int, int>> body;
    std::string _current_direction;
private:
    const std::string moduleName{"Snake"};
};

extern "C" IGameModule* entryPoint() { return new Snake(); }

#endif //ARCADE_SNAKE_HPP