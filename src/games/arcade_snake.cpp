/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_snake.cpp
*/

#include "arcade_snake.hpp"
#include <iostream>

Snake::Snake()
{
    this->_x = 7;
    this->_y = 7;
    this->_x_apple = 2;
    this->_y_apple = 7;
    this->_life = 1;
    this->_score = 0;
    this->_current_direction = "LEFT";
    this->_game_map = {
        "###############",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "###############"
    };
    this->body.push_back({_x + 1, _y});
    this->body.push_back({_x + 2, _y});
    this->body.push_back({_x + 3, _y});

    _game_map[_x][_y] = 'S';
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    generate_apple();
}

Snake::~Snake()
{
}

void Snake::restart()
{
    this->body.clear();
    this->_x = 7;
    this->_y = 7;
    this->_x_apple = 2;
    this->_y_apple = 7;
    this->_life = 1;
    this->_score = 0;
    this->_current_direction = "LEFT";
    this->_game_map = {
        "###############",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "###############"
    };
    this->body.push_back({_x + 1, _y});
    this->body.push_back({_x + 2, _y});
    this->body.push_back({_x + 3, _y});

    _game_map[_x][_y] = 'S';
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    generate_apple();
}

void Snake::run()
{
}

std::vector<std::string> Snake::getMap()
{
    return _game_map;
}

void Snake::updateCoordinates(size_t &new_x, size_t &new_y, const std::string &direction) {
    if (direction == "UP") {
        new_y -= 1;
    } else if (direction == "DOWN") {
        new_y += 1;
    } else if (direction == "LEFT") {
        new_x -= 1;
    } else if (direction == "RIGHT") {
        new_x += 1;
    }
}

std::vector<std::string> Snake::getValidDirections(void) const
{
    std::vector<std::string> valid_directions;

    if (_current_direction != "DOWN") {
        valid_directions.push_back("UP");
    }
    if (_current_direction != "UP") {
        valid_directions.push_back("DOWN");
    }
    if (_current_direction != "RIGHT") {
        valid_directions.push_back("LEFT");
    }
    if (_current_direction != "LEFT") {
        valid_directions.push_back("RIGHT");
    }
    return valid_directions;
}

std::string Snake::getScoreAsString() const {
    return std::to_string(_score);
}

bool Snake::isOutOfBounds(size_t new_x, size_t new_y) {
    return (int)new_x < 0 || new_x >= _game_map[0].size() || (int)new_y < 0 || new_y >= _game_map.size();
}

bool Snake::isCollision(size_t new_x, size_t new_y) {
    if (_game_map[new_y][new_x] == 'o' || _game_map[new_y][new_x] == '#') {
        return true;
    } else {
        return false;
    }
}

bool Snake::isApple(size_t new_x, size_t new_y) {
    return _game_map[new_y][new_x] == 'A';
}

void Snake::updateBody(bool apple_eaten) {
    if (!apple_eaten) {
        if (body.back().first != _x || body.back().second != _y) {
            _game_map[body.back().second][body.back().first] = ' ';
            body.pop_back();
        }
    }
    body.push_front({_x, _y});
}

void Snake::updateMap(size_t new_x, size_t new_y) {
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    _game_map[new_y][new_x] = 'S';
}

int Snake::move(std::string direction) {
    size_t new_x = _x;
    size_t new_y = _y;

    _current_direction = direction;

    updateCoordinates(new_x, new_y, direction);

    bool apple_eaten = isApple(new_x, new_y);
    updateBody(apple_eaten);
    if (isOutOfBounds(new_x, new_y) || isCollision(new_x, new_y) ||  direction == "ESC") {
        setLife(0);
        return 0;
    }
    updateMap(new_x, new_y);

    _x = new_x;
    _y = new_y;

    if (apple_eaten) {
        _score += 1;
        generate_apple();
        return 1;
    }
    return 0;
}

void Snake::generate_apple() {
    int new_x = rand() % (_game_map[0].size() - 2) + 1;
    int new_y = rand() % (_game_map.size() - 2) + 1;

    while (_game_map[new_y][new_x] != ' ') {
        new_x = rand() % (_game_map[0].size() - 2) + 1;
        new_y = rand() % (_game_map.size() - 2) + 1;
    }

    _game_map[new_y][new_x] = 'A';
}

void Snake::getPosition(int& x, int& y) const
{
    x = this->_x;
    y = this->_y;
}

void Snake::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

int Snake::getLife() const
{
    return this->_life;
}

int Snake::getScore() const
{
    return this->_score;
}

void Snake::setLife(int life)
{
    this->_life = life;
}

void Snake::handle_anim()
{
}
