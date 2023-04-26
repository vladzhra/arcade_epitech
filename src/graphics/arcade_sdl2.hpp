/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_sdl2.hpp
*/

#ifndef ARCADE_SDL2_HPP
#define ARCADE_SDL2_HPP
#include "IGraphicModule.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <random>
#include <iostream>
#include <vector>
#include <string>

class Sdl2Module : public IGraphicModule {
public:
    Sdl2Module();
    ~Sdl2Module();
    void run(void) override;
    void playSound(void) override;
    void display(const std::vector<std::string>& game_map, const std::string &score) override;
    std::string handle_events() override;
    const std::string& getName() const override { return moduleName; }
    void updateTexture(const std::string& direction) override;
    void drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) override;
    void displayGameName(std::string name) override;

protected:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    TTF_Font* _font;
    TTF_Font* _fontScore;
    Mix_Chunk* _sound;
    Mix_Music* _music;
    SDL_Texture* _texture;
    SDL_Rect _scoreRect;
    std::vector<SDL_Texture*> _textures;
    std::string _scoreText;
    SDL_Color _textColor;
    SDL_Surface* _textSurface;
    SDL_Texture* _textTexture;
    SDL_Rect _textRect;
    SDL_Surface* _textSurface2;
    SDL_Texture* _textTexture2;
    SDL_Rect _textRect2;
    void loadTexture(const std::string &filename, size_t index);
    void drawTexture(size_t index, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f);
    void draw_game_map(const std::vector<std::string>& game_map);
    void createWindow(void);
    void loadBackground(void);
    void loadFont(void);
    void loadMusicAndSound(void);
    void loadTextures(void);
    void destroyLib(void);
    void updateScoreText(const std::string &score);
    void drawText(const std::string &text, int x, int y, TTF_Font* font, SDL_Color color);
    void displayGraphicName();
private:
    const std::string moduleName{"Sdl2"};
    const std::string _rules = "Type R to restart the game          Type G to change the game        Type L to change the grafix library";
    bool _isOpen;
};

extern "C" IGraphicModule* entryPoint() { return new Sdl2Module(); }

#endif
