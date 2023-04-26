/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_sfml.hpp
*/

#ifndef ARCADE_SFML_HPP
#define ARCADE_SFML_HPP
#include "IGraphicModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>

class SfmlModule : public IGraphicModule {
public:
    SfmlModule();
    ~SfmlModule();
    void run(void) override;
    void playSound(void) override;
    void display(const std::vector<std::string>& game_map, const std::string &score) override;
    std::string handle_events() override;
    const std::string& getName() const override { return moduleName; }
    void updateTexture(const std::string& direction) override;
    void drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) override;
    void displayGameName(std::string name) override;

protected:
    sf::RenderWindow _window;
    sf::Texture _bgTexture;
    sf::Sprite _bgSprite;
    sf::Texture _bgScreenTexture;
    sf::Sprite _bgScreenSprite;
    sf::Font _font;
    sf::Font _fontScore;
    sf::Text _titleText;
    sf::Text _score;
    sf::SoundBuffer _soundBuffer;
    sf::Sound _sound;
    sf::Music _music;
    sf::Texture _wallTexture;
    sf::Texture _emptyTexture;
    sf::Sprite _wallSprite;
    sf::Sprite _emptySprite;
    sf::Texture _snakeHeadTexture;
    sf::Sprite _snakeHeadSprite;
    sf::Texture _snakeBodyTexture;
    sf::Sprite _snakeBodySprite;
    sf::Texture _snakeTailTexture;
    sf::Sprite _snakeTailSprite;
    sf::Texture _appleTexture;
    sf::Sprite _appleSprite;
    sf::Text _gameName;
    sf::Text _graphicName;
    void loadTexture(const std::string &filename, sf::Texture &texture);
    void drawTexture(sf::Texture &texture, float x, float y);
    void draw_game_map(const std::vector<std::string>& game_map);
    void createWindow(void);
    void loadBackground(void);
    void loadFont(void);
    void loadScreenBackground(void);
    void loadMusicAndSound(void);
    void configureTitleText(void);
    void loadTexturesAndSprites(void);
    void destroyLib(void);
    void updateScoreText(const std::string &score);
    void displayGraphicName();
private:
    const std::string moduleName{"Sfml"};
    sf::Text rulesText;
    const std::string _rules = "Type R to restart the game                   Type G to change the game                   Type L to change the grafix library";
};

extern "C" IGraphicModule* entryPoint() { return new SfmlModule(); }

#endif