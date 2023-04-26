/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_nibbler.cpp
*/

#include "arcade_nibbler.hpp"
#include <iostream>

Nibbler::Nibbler()
{
    this->_x = 7;
    this->_y = 7;
    this->_x_apple = 2;
    this->_y_apple = 7;
    this->_life = 1;
    this->_score = 0;
    this->_current_direction = "LEFT";
    this->level = 1;
    this->_game_map_level1 = {
        "###############",
        "#             #",
        "# ### # # ### #",
        "# ###     ### #",
        "# ### ### ### #",
        "#             #",
        "### ### ### ###",
        "#             #",
        "# ##### ##### #",
        "#     # #     #",
        "# ### # # ### #",
        "#   #     #   #",
        "# #   ###   # #",
        "#             #",
        "###############"
    };

    this->_game_map_level2 = {
        "###############",
        "#   #         #",
        "# #   # ###   #",
        "# ##### ### ###",
        "#       ###   #",
        "# #####       #",
        "# #   # ##### #",
        "#   #         #",
        "# ### # # ### #",
        "#   #   # ### #",
        "### #####     #",
        "#   #   # ##  #",
        "# ### # # ##  #",
        "#         ##  #",
        "###############"
    };

    this->_game_map_level3 = {
        "###############",
        "#           ###",
        "# ##### ### ###",
        "# ##### ### ###",
        "#       ###   #",
        "# #####       #",
        "# #   # # # # #",
        "#   #         #",
        "# ### ### ### #",
        "# ### ###     #",
        "# ###     # # #",
        "#       # # # #",
        "# ### # # # # #",
        "#     #   #   #",
        "###############"
    };

    this->_game_map = _game_map_level1;
    this->body.push_back({_x + 1, _y});
    this->body.push_back({_x + 2, _y});
    this->body.push_back({_x + 3, _y});

    _game_map[_x][_y] = 'S';
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    generate_apple();
}

void Nibbler::restart()
{
    this->body.clear();
    this->_x = 7;
    this->_y = 7;
    this->_x_apple = 2;
    this->_y_apple = 7;
    this->_life = 1;
    this->_score = 0;
    this->_current_direction = "LEFT";
    this->level = 1;
    this->_game_map_level1 = {
        "###############",
        "#             #",
        "# ### # # ### #",
        "# ###     ### #",
        "# ### ### ### #",
        "#             #",
        "### ### ### ###",
        "#             #",
        "# ##### ##### #",
        "#     # #     #",
        "# ### # # ### #",
        "#   #     #   #",
        "# #   ###   # #",
        "#             #",
        "###############"
    };

    this->_game_map_level2 = {
        "###############",
        "#   #         #",
        "# #   # ###   #",
        "# ##### ### ###",
        "#       ###   #",
        "# #####       #",
        "# #   # ##### #",
        "#   #         #",
        "# ### # # ### #",
        "#   #   # ### #",
        "### #####     #",
        "#   #   # ##  #",
        "# ### # # ##  #",
        "#         ##  #",
        "###############"
    };

    this->_game_map_level3 = {
        "###############",
        "#           ###",
        "# ##### ### ###",
        "# ##### ### ###",
        "#       ###   #",
        "# #####       #",
        "# #   # # # # #",
        "#   #         #",
        "# ### ### ### #",
        "# ### ###     #",
        "# ###     # # #",
        "#       # # # #",
        "# ### # # # # #",
        "#     #   #   #",
        "###############"
    };

    this->_game_map = _game_map_level1;
    this->body.push_back({_x + 1, _y});
    this->body.push_back({_x + 2, _y});
    this->body.push_back({_x + 3, _y});

    _game_map[_x][_y] = 'S';
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    generate_apple();
}

Nibbler::~Nibbler()
{
}

void Nibbler::run()
{
}

void Nibbler::resetSnake(void) {
    _x = 7;
    _y = 7;

    _current_direction = "LEFT";

    body.clear();
    body.push_back({_x + 1, _y});
    body.push_back({_x + 2, _y});
    body.push_back({_x + 3, _y});

    for (size_t y = 0; y < _game_map.size(); ++y) {
        for (size_t x = 0; x < _game_map[y].size(); ++x) {
            if (_game_map[y][x] == 'S' || _game_map[y][x] == 'o') {
                _game_map[y][x] = ' ';
            }
        }
    }

    _game_map[_y][_x] = 'S';
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
}

void Nibbler::updateLevel() {
    if (_score >= 10 && _score < 20 && level == 1) {
        level = 2;
        _game_map = _game_map_level2;
        resetSnake();
    } else if (_score >= 20 && level == 2) {
        level = 3;
        _game_map = _game_map_level3;
        resetSnake();
    } else if (_score >= 30 && level == 3) {
        _life = 0;
    }
}

std::vector<std::string> Nibbler::getMap()
{
    return _game_map;
}

std::string Nibbler::getScoreAsString() const {
    return std::to_string(_score);
}

void Nibbler::updateCoordinates(size_t &new_x, size_t &new_y, const std::string &direction) {
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

bool Nibbler::isOutOfBounds(size_t new_x, size_t new_y) {
    return (int)new_x < 0 || new_x >= _game_map[0].size() || (int)new_y < 0 || new_y >= _game_map.size();
}

bool Nibbler::isCollision(size_t new_x, size_t new_y) {
    return _game_map[new_y][new_x] == 'o';
}

bool Nibbler::isApple(size_t new_x, size_t new_y) {
    return _game_map[new_y][new_x] == 'A';
}

void Nibbler::updateBody(bool apple_eaten) {
    if (!apple_eaten) {
        if (body.back().first != _x || body.back().second != _y) {
            _game_map[body.back().second][body.back().first] = ' ';
            body.pop_back();
        }
    }
    body.push_front({_x, _y});
}

void Nibbler::updateMap(size_t new_x, size_t new_y) {
    for (const auto& segment : body) {
        _game_map[segment.second][segment.first] = 'o';
    }
    _game_map[new_y][new_x] = 'S';
}

std::vector<std::string> Nibbler::getValidDirections() const {
    std::vector<std::string> validDirections;
    std::vector<std::pair<int, int>> directions = {
        {0, -1}, {-1, 0}, {0, 1}, {1, 0}
    };
    std::vector<std::string> directionNames = {"UP", "LEFT", "DOWN", "RIGHT"};

    for (size_t i = 0; i < directions.size(); ++i) {
        size_t new_x = _x + directions[i].first;
        size_t new_y = _y + directions[i].second;
        if (_game_map[new_y][new_x] == ' ' || _game_map[new_y][new_x] == 'A') {
            validDirections.push_back(directionNames[i]);
        }
    }

    return validDirections;
}

int Nibbler::move(std::string direction) {
    size_t new_x = _x;
    size_t new_y = _y;

    _current_direction = direction;

    updateCoordinates(new_x, new_y, direction);
    if (_game_map[new_y][new_x] == '#') {
        return 2;
    }
    if (isOutOfBounds(new_x, new_y) || isCollision(new_x, new_y) || direction == "ESC") {
        setLife(0);
        return 0;
    }

    bool apple_eaten = isApple(new_x, new_y);
    updateBody(apple_eaten);

    updateMap(new_x, new_y);

    _x = new_x;
    _y = new_y;

    if (apple_eaten) {
        _score += 1;
        updateLevel();
        generate_apple();
        return 1;
    }
    return 0;
}

void Nibbler::generate_apple() {
    int new_x = rand() % (_game_map[0].size() - 2) + 1;
    int new_y = rand() % (_game_map.size() - 2) + 1;

    while (_game_map[new_y][new_x] != ' ') {
        new_x = rand() % (_game_map[0].size() - 2) + 1;
        new_y = rand() % (_game_map.size() - 2) + 1;
    }

    _game_map[new_y][new_x] = 'A';
}

void Nibbler::getPosition(int& x, int& y) const
{
    x = this->_x;
    y = this->_y;
}

void Nibbler::setPosition(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

int Nibbler::getLife() const
{
    return this->_life;
}

int Nibbler::getScore() const
{
    return this->_score;
}

void Nibbler::setLife(int life)
{
    this->_life = life;
}

void Nibbler::handle_anim()
{
}
