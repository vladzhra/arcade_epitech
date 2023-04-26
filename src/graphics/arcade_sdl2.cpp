/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** arcade_sdl2.cpp
*/

#include "arcade_sdl2.hpp"

void Sdl2Module::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        exit(EXIT_FAILURE);
    }
    _window = SDL_CreateWindow("Arcade - SDL2 graphics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
    if (!_window)
    {
        exit(EXIT_FAILURE);
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
    {
        exit(EXIT_FAILURE);
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1)
    {
        exit(EXIT_FAILURE);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        exit(EXIT_FAILURE);
    }
    _isOpen = true;
}

void Sdl2Module::loadBackground()
{
    loadTexture("resources/bg.png", 0);
}

void Sdl2Module::loadFont()
{
    _font = TTF_OpenFont("resources/Vintage.ttf", 80);
    if (!_font)
    {
        exit(EXIT_FAILURE);
    }
    _fontScore = TTF_OpenFont("resources/Betty.ttf", 38);
    if (!_fontScore)
    {
        exit(EXIT_FAILURE);
    }
}

void Sdl2Module::loadMusicAndSound()
{
    _music = Mix_LoadMUS("resources/sounds/music.ogg");
    if (!_music)
    {
        exit(EXIT_FAILURE);
    }
    Mix_VolumeMusic(40);
    Mix_PlayMusic(_music, -1);

    _sound = Mix_LoadWAV("resources/sounds/eating_apple1.ogg");
    if (!_sound)
    {
        exit(EXIT_FAILURE);
    }
}

void Sdl2Module::loadTextures()
{
    loadTexture("resources/arcade.jpg", 1);
    loadTexture("resources/snake/wall.jpeg", 2);
    loadTexture("resources/snake/empty.png", 3);
    loadTexture("resources/snake/head_LEFT.png", 4);
    loadTexture("resources/snake/body_horizontal.png", 5);
    loadTexture("resources/snake/tail_right.png", 6);
    loadTexture("resources/snake/apple.png", 7);
}

Sdl2Module::Sdl2Module()
{
    createWindow();
    loadBackground();
    loadFont();
    loadMusicAndSound();
    loadTextures();
}

void Sdl2Module::drawMenu(const std::vector<std::string> &gameNames, int selectedIndex)
{
    SDL_Color whiteColor = {255, 255, 255, 255};
    SDL_Color redColor = {255, 0, 0, 255};

    SDL_RenderClear(_renderer);
    drawTexture(0, 0, -100, 1.19f, 1.19f);
    drawText("Arcade", 790, 100, _font, whiteColor);

    for (size_t i = 0; i < gameNames.size(); i++)
    {
        if ((int)i == selectedIndex)
        {
            drawText(gameNames[i], 800, 300 + 100 * i, _font, redColor);
        }
        else
        {
            drawText(gameNames[i], 800, 300 + 100 * i, _font, whiteColor);
        }
    }

    drawText(_rules, 100, 994, _fontScore, whiteColor);

    SDL_RenderPresent(_renderer);
}


void Sdl2Module::playSound()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 3);
    int random_number = distrib(gen);

    std::string file_path = "resources/sounds/eating_apple" + std::to_string(random_number) + ".ogg";

    Mix_FreeChunk(_sound);
    _sound = Mix_LoadWAV(file_path.c_str());
    if (!_sound)
    {
        exit(EXIT_FAILURE);
    }

    Mix_PlayChannel(-1, _sound, 0);
}

void Sdl2Module::updateScoreText(const std::string &score)
{
    _scoreText = "Score: " + score;
}

void Sdl2Module::display(const std::vector<std::string> &game_map, const std::string &score)
{
    SDL_Color whiteColor = {255, 255, 255, 255};

    SDL_RenderClear(_renderer);
    drawTexture(0, 0, -100, 1.19f, 1.19f);
    drawTexture(1, 430, 190, 2.25f, 2.25f);
    draw_game_map(game_map);
    drawText("Arcade", 790, 100, _font, whiteColor);
    updateScoreText(score);
    drawText(_scoreText, 1620, 425, _fontScore, whiteColor);
    drawText(_rules, 100, 994, _fontScore, whiteColor);
    displayGraphicName();
    SDL_RenderPresent(_renderer);
}

void Sdl2Module::run()
{
    handle_events();
}

void Sdl2Module::updateTexture(const std::string &direction)
{
    std::string head_texture_path = "resources/snake/head_" + direction + ".png";
    loadTexture(head_texture_path, 4);
}

void Sdl2Module::draw_game_map(const std::vector<std::string> &game_map)
{
    for (size_t y = 0; y < game_map.size(); ++y)
    {
        for (size_t x = 0; x < game_map[y].length(); ++x)
        {
            int textureIndex = -1;

            switch (game_map[y][x])
            {
            case '#':
                textureIndex = 2;
                break;
            case ' ':
                textureIndex = 3;
                break;
            case 'A':
                textureIndex = 7;
                break;
            case 'S':
                textureIndex = 4;
                break;
            case 'o':
                textureIndex = 5;
                break;
            case '.':
                textureIndex = 6;
                break;
            default:
                break;
            }

            if (textureIndex != -1)
            {
                drawTexture(textureIndex, x * 40 + 670, y * 40 + 290);
            }
        }
    }
}

Sdl2Module::~Sdl2Module()
{
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
    destroyLib();
}

void Sdl2Module::destroyLib(void)
{
    Mix_FreeChunk(_sound);
    Mix_FreeMusic(_music);
    TTF_CloseFont(_font);
    TTF_CloseFont(_fontScore);
    for (auto &texture : _textures)
    {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Sdl2Module::displayGameName(std::string name)
{
    _textColor = {255, 255, 255, 255};
    _textSurface = TTF_RenderText_Solid(_fontScore, name.c_str(), _textColor);
    _textTexture = SDL_CreateTextureFromSurface(_renderer, _textSurface);
    _textRect.x = 10;
    _textRect.y = 50;
    _textRect.w = _textSurface->w;
    _textRect.h = _textSurface->h;

    SDL_RenderCopy(_renderer, _textTexture, nullptr, &_textRect);

    SDL_FreeSurface(_textSurface);
    SDL_DestroyTexture(_textTexture);
}

void Sdl2Module::displayGraphicName(void)
{
    std::string graphicName = getName();
    _textColor = {255, 255, 255, 255};
    _textSurface2 = TTF_RenderText_Solid(_fontScore, graphicName.c_str(), _textColor);
    _textTexture2 = SDL_CreateTextureFromSurface(_renderer, _textSurface2);
    _textRect2.x = 10;
    _textRect2.y = 10;
    _textRect2.w = _textSurface2->w;
    _textRect2.h = _textSurface2->h;

    SDL_RenderCopy(_renderer, _textTexture2, nullptr, &_textRect2);

    SDL_FreeSurface(_textSurface2);
    SDL_DestroyTexture(_textTexture2);
}

std::string Sdl2Module::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            _isOpen = false;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                _isOpen = false;
                return "ESCAPE";
            case SDLK_RETURN:
                return "ENTER";
            case SDLK_l:
                return "L";
            case SDLK_LEFT:
                return "LEFT";
            case SDLK_RIGHT:
                return "RIGHT";
            case SDLK_UP:
                return "UP";
            case SDLK_DOWN:
                return "DOWN";
            case SDLK_SPACE:
                return "SPACE";
            case SDLK_g:
                return "G";
            case SDLK_r:
                return "R";
            default:
                break;
            }
        }
    }
    return "";
}

void Sdl2Module::loadTexture(const std::string &filename, size_t index)
{
    SDL_Texture *texture = IMG_LoadTexture(_renderer, filename.c_str());
    if (!texture)
    {
        std::cerr << "Error: Could not load texture: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    if (index < _textures.size())
    {
        SDL_DestroyTexture(_textures[index]);
        _textures[index] = texture;
    }
    else
    {
        _textures.push_back(texture);
    }
}

void Sdl2Module::drawTexture(size_t index, int x, int y, float scaleX, float scaleY)
{
    if (index >= _textures.size())
    {
        std::cerr << "Error: Invalid texture index." << std::endl;
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    SDL_QueryTexture(_textures[index], nullptr, nullptr, &dstRect.w, &dstRect.h);
    dstRect.w = static_cast<int>(dstRect.w * scaleX);
    dstRect.h = static_cast<int>(dstRect.h * scaleY);

    SDL_RenderCopy(_renderer, _textures[index], nullptr, &dstRect);
}

void Sdl2Module::drawText(const std::string &text, int x, int y, TTF_Font *font, SDL_Color color)
{
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!textSurface)
    {
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
    if (!textTexture)
    {
        std::cerr << "Error: Unable to create texture from surface. SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = textSurface->w;
    dstRect.h = textSurface->h;
    SDL_RenderCopy(_renderer, textTexture, nullptr, &dstRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
