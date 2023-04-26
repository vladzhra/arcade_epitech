/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_sfml.cpp
*/

#include "arcade_sfml.hpp"

void SfmlModule::createWindow() {
    _window.create(sf::VideoMode(1920, 1080, 32),
                   "Arcade - SFML graphics",
                   sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
    _window.setActive(false);
    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(false);
}

void SfmlModule::loadBackground() {
    if (!_bgTexture.loadFromFile("resources/bg.png")) {
        std::cerr << "Error: Could not load background image" << std::endl;
        exit(EXIT_FAILURE);
    }
    _bgSprite.setTexture(_bgTexture);
    _bgSprite.setPosition(0, -100);
    _bgSprite.setScale(1.19, 1.19);
}

void SfmlModule::loadFont() {
    if (!_font.loadFromFile("resources/Vintage.ttf")) {
        std::cerr << "Error: Could not load custom font" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!_fontScore.loadFromFile("resources/Betty.ttf")) {
        std::cerr << "Error: Could not load custom font" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SfmlModule::loadScreenBackground() {
    if (!_bgScreenTexture.loadFromFile("resources/arcade.jpg")) {
        std::cerr << "Error: Could not load background image" << std::endl;
        exit(EXIT_FAILURE);
    }
    _bgScreenSprite.setTexture(_bgScreenTexture);
    _bgScreenSprite.setPosition(430, 190);
    _bgScreenSprite.setScale(2.25, 2.25);
}

void SfmlModule::loadMusicAndSound() {
    _music.openFromFile("resources/sounds/music.ogg");
    _music.setVolume(40);
    _music.setLoop(true);
    _music.play();

    _soundBuffer.loadFromFile("resources/sounds/eating_apple1.ogg");
    _sound.setBuffer(_soundBuffer);
}

void SfmlModule::configureTitleText() {
    _titleText.setFont(_font);
    _titleText.setString("Arcade");
    _titleText.setCharacterSize(80);
    _titleText.setFillColor(sf::Color::White);
    _titleText.setStyle(sf::Text::Bold);
    _titleText.setPosition(790, 100);
    _score.setFont(_fontScore);
    _graphicName.setFont(_fontScore);
    _gameName.setFont(_fontScore);
    rulesText.setFont(_fontScore);
    rulesText.setCharacterSize(30);
    rulesText.setFillColor(sf::Color::White);
    rulesText.setPosition(100, 994);
    rulesText.setString(_rules);
}

void SfmlModule::loadTexturesAndSprites() {
    if (!_wallTexture.loadFromFile("resources/snake/wall.jpeg"))
        return;
    if (!_emptyTexture.loadFromFile("resources/snake/empty.png"))
        return;
    if (!_snakeHeadTexture.loadFromFile("resources/snake/head_LEFT.png"))
        return;
    if (!_snakeBodyTexture.loadFromFile("resources/snake/body_horizontal.png"))
        return;
    if (!_snakeTailTexture.loadFromFile("resources/snake/tail_right.png"))
        return;
    if (!_appleTexture.loadFromFile("resources/snake/apple.png"))
        return;
    _wallSprite.setTexture(_wallTexture);
    _emptySprite.setTexture(_emptyTexture);
    _snakeHeadSprite.setTexture(_snakeHeadTexture);
    _snakeBodySprite.setTexture(_snakeBodyTexture);
    _snakeTailSprite.setTexture(_snakeTailTexture);
    _appleSprite.setTexture(_appleTexture);
}

SfmlModule::SfmlModule() {
    createWindow();
    loadBackground();
    loadFont();
    loadScreenBackground();
    loadMusicAndSound();
    configureTitleText();
    loadTexturesAndSprites();
}

void SfmlModule::drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) {
    _window.clear();
    _window.draw(_bgSprite);
    _window.draw(_titleText);
    sf::Text text;
    text.setFont(_font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(800, 300);
    for (size_t i = 0; i < gameNames.size(); i++) {
        if ((int)i == selectedIndex) {
            text.setFillColor(sf::Color::Red);
        } else {
            text.setFillColor(sf::Color::White);
        }
        text.setString(gameNames[i]);
        _window.draw(text);
        text.move(0, 100);
    }
    _window.draw(rulesText);
    _window.display();
}

void SfmlModule::playSound()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 3);
    int random_number = distrib(gen);

    std::string file_path = "resources/sounds/eating_apple" + std::to_string(random_number) + ".ogg";

    _soundBuffer.loadFromFile(file_path);
    _sound.setBuffer(_soundBuffer);
    _sound.play();
}

void SfmlModule::updateScoreText(const std::string &score) {
    _score.setString("Score: " + score);
    _score.setCharacterSize(38);
    _score.setFillColor(sf::Color::White);
    _score.setPosition(1620, 425);
}

void SfmlModule::display(const std::vector<std::string>& game_map, const std::string &score) {
    _window.clear();
    _window.draw(_bgSprite);
    _window.draw(_bgScreenSprite);
    draw_game_map(game_map);
    _window.draw(_titleText);
    updateScoreText(score);
    _window.draw(_score);
    _window.draw(_gameName);
    displayGraphicName();
    _window.display();
}

void SfmlModule::displayGraphicName()
{
    _graphicName.setString(getName());
    _graphicName.setCharacterSize(38);
    _graphicName.setFillColor(sf::Color::White);
    _graphicName.setPosition(10, 10);
    _window.draw(_graphicName);
}

void SfmlModule::displayGameName(std::string name)
{
    _gameName.setString(name);
    _gameName.setCharacterSize(38);
    _gameName.setFillColor(sf::Color::White);
    _gameName.setPosition(10, 50);
}

void SfmlModule::run()
{
    handle_events();
}

void SfmlModule::updateTexture(const std::string& direction) {
    std::string head_texture_path = "resources/snake/head_" + direction + ".png";
    if (!_snakeHeadTexture.loadFromFile(head_texture_path)) {
        std::cerr << "Error: Could not load snake head texture for direction " << direction << std::endl;
        exit(EXIT_FAILURE);
    }
    _snakeHeadSprite.setTexture(_snakeHeadTexture);
}

void SfmlModule::draw_game_map(const std::vector<std::string>& game_map)
{
    for (size_t y = 0; y < game_map.size(); ++y) {
        for (size_t x = 0; x < game_map[y].length(); ++x) {
            sf::Sprite* currentSprite = nullptr;

            switch (game_map[y][x]) {
            case '#':
                currentSprite = &_wallSprite;
                break;
            case ' ':
                currentSprite = &_emptySprite;
                break;
            case 'A':
                currentSprite = &_appleSprite;
                break;
            case 'S':
                currentSprite = &_snakeHeadSprite;
                break;
            case 'o':
                currentSprite = &_snakeBodySprite;
                break;
            case '.':
                currentSprite = &_snakeTailSprite;
                break;
            default:
                break;
            }
            if (currentSprite) {
                currentSprite->setPosition(x * 40 + 670, y * 40 + 290);
                _window.draw(*currentSprite);
            }
        }
    }
}

SfmlModule::~SfmlModule() {
    _sound.stop();
    _window.close();
}

void SfmlModule::destroyLib(void)
{
    _sound.stop();
    _window.close();
}

std::string SfmlModule::handle_events()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _window.close();
                return "ESCAPE";
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                return "ENTER";
            }
            if (event.key.code == sf::Keyboard::L)
            {
                return "L";
            }
            if (event.key.code == sf::Keyboard::Left) {
                return "LEFT";
            }
            if (event.key.code == sf::Keyboard::Right) {
                return "RIGHT";
            }
            if (event.key.code == sf::Keyboard::Up) {
                return "UP";
            }
            if (event.key.code == sf::Keyboard::Down) {
                return "DOWN";
            }
            if (event.key.code == sf::Keyboard::Space)
                return "SPACE";
            if (event.key.code == sf::Keyboard::G)
                return "G";
            if (event.key.code == sf::Keyboard::R)
                return "R";
        }
    }
    return "";
}

void SfmlModule::loadTexture(const std::string &filename, sf::Texture &texture)
{
    if (!texture.loadFromFile(filename))
    {
        std::cerr << "Error: Could not load texture: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SfmlModule::drawTexture(sf::Texture &texture, float x, float y)
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    _window.draw(sprite);
}
