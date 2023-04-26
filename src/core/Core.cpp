/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** core.cpp
*/

#include "Core.hpp"
#include <set>

void Core::loadLibraries(void) {
    DIR *dir;
    struct dirent *ent;

    _gamePaths.clear();
    _libraryPaths.clear();

    std::string libDir = "lib/";

    std::set<std::string> gameNames = {"arcade_snake.so", "arcade_nibbler.so", "arcade_pacman.so", \
    "arcade_qix.so", "arcade_centipede.so", "arcade_solarfox.so"};
    std::set<std::string> graphicNames = {"arcade_ncurses.so", "arcade_sdl2.so", "arcade_ndk++.so", \
    "arcade_aalib.so", "arcade_libcaca.so", "arcade_allegro5.so", "arcade_xlib.so", "arcade_gtk+.so", \
    "arcade_sfml.so", "arcade_irrlicht.so", "arcade_opengl.so", "arcade_vulkan.so", "arcade_qt5.so"};

    if ((dir = opendir(libDir.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename(ent->d_name);
            if (filename.find("arcade_") == 0 && filename.find(".so") != std::string::npos) {
                if (gameNames.find(filename) != gameNames.end()) {
                    std::string gameName = filename.substr(7, filename.size() - 10);
                    _gamePaths.push_back({gameName, libDir + filename});
                } else if (graphicNames.find(filename) != graphicNames.end()) {
                    _libraryPaths.push_back(libDir + filename);
                }
            }
        }
        closedir(dir);
    } else {
        perror("Could not open libraries directory");
        exit(EXIT_FAILURE);
    }
}

IGraphicModule* Core::loadGraphicModule(DLLoader<IGraphicModule> &loader1) {
    IGraphicModule* graphicModule = loader1.getInstance();
    return graphicModule;
}

IGameModule* Core::loadGameInstance(DLLoader<IGameModule> &game) {
    return game.getInstance();
}

bool Core::isGameOver(IGameModule* gameModule) {
    return gameModule->getLife() <= 0;
}

void Core::handleGameOver(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule, int score) {
    delete graphicModule;
    loader1.unload();
    if (score >= 30)
        std::cout << "You win!" << std::endl;
    else
        std::cout << "\nGame Over" << std::endl;
}

int Core::handleEventSwitch(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule, int event_code) {
    switch (event_code) {
        case 1: // L
            handleLKey(loader1, graphicModule);
            break;
        case 2: // UP
            handleMove("UP");
            break;
        case 3: // DOWN
            handleMove("DOWN");
            break;
        case 4: // LEFT
            handleMove("LEFT");
            break;
        case 5: // RIGHT
            handleMove("RIGHT");
            break;
        case 6: // SPACE
            handleSpace();
            break;
        case 7: // ESCAPE
            handleEscape(loader1, graphicModule);
            return 1;
        case 8: // ENTER
            break;
        default:
            break;
    }
    return 0;
}

int Core::handleEventGame(DLLoader<IGameModule> &loader1, IGameModule* &gameModule, int event_code) {
    switch (event_code) {
        case 9: // G
            handleGKey(loader1, gameModule);
            gameModule->restart();
            _direction = "LEFT";
            break;
        case 10: // R
            gameModule->restart();
            _direction = "LEFT";
            break;
        default:
            break;
    }
    return 0;
}

void Core::handleLKey(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule) {
    delete graphicModule;
    graphicModule = nullptr;

    loader1.unload();

    _currentLibraryIndex = (_currentLibraryIndex + 1) % _libraryPaths.size();
    loader1.load(_libraryPaths[_currentLibraryIndex]);
    graphicModule = loader1.getInstance();
}

void Core::handleGKey(DLLoader<IGameModule> &loader1, IGameModule* &gameModule) {
    delete gameModule;
    gameModule = nullptr;

    loader1.unload();

    _selectedGameIndex = (_selectedGameIndex + 1) % _gamePaths.size();
    loader1.load(_gamePaths[_selectedGameIndex].second);
    gameModule = loader1.getInstance();
}

void Core::handleMove(const std::string &direction) {
    if ((_direction == "UP" && direction == "DOWN") ||
        (_direction == "DOWN" && direction == "UP") ||
        (_direction == "LEFT" && direction == "RIGHT") ||
        (_direction == "RIGHT" && direction == "LEFT")) {
        return;
    } else {
        _direction = direction;
    }
}

void Core::handleSpace() {
    if (_isBoosted == true)
        _isBoosted = false;
    else
        _isBoosted = true;
}

void Core::handleEscape(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule) {
    delete graphicModule;
    graphicModule = nullptr;
    loader1.unload();
}

void Core::loadGameModule(DLLoader<IGameModule> &game, const std::string &filename) {
    game.load(filename);
}

int Core::handleMenu(IGraphicModule* &graphicModule, DLLoader<IGraphicModule> &loader1) {
    while (true) {
        std::vector<std::string> gameNames;
        for (const auto& gamePath : _gamePaths) {
            gameNames.push_back(gamePath.first);
        }
        graphicModule->drawMenu(gameNames, _selectedGameIndex);

        std::string event = graphicModule->handle_events();
        if (event == "UP") {
            _selectedGameIndex = (_selectedGameIndex - 1 + _gamePaths.size()) % _gamePaths.size();
        } else if (event == "DOWN") {
            _selectedGameIndex = (_selectedGameIndex + 1) % _gamePaths.size();
        } else if (event == "SPACE") {
            return _selectedGameIndex;
        } else if (event == "ENTER") {
            return _selectedGameIndex;
        } else if (event == "ESCAPE") {
            handleEscape(loader1, graphicModule);
            return -1;
        } else if (event == "L") {
            handleLKey(loader1, graphicModule);
        }
    }
    return -1;
}

int Core::handleMovement(IGameModule *gameModule, IGraphicModule *graphicModule)
{
    handleMove(_direction);
    graphicModule->updateTexture(_direction);
    return gameModule->move(_direction);
}

int Core::handleDirection(IGameModule *gameModule, IGraphicModule* graphicModule, DLLoader<IGraphicModule> &loader1)
{
    std::vector<std::string> validDirections = gameModule->getValidDirections();
    if (validDirections.size() == 1) {
        _direction = validDirections[0];
    } else if (validDirections.empty()) {
        handleGameOver(loader1, graphicModule, gameModule->getScore());
        return 1;
    }
    return 0;
}

void Core::AttributeCurrentLibIndex(std::string &currentLib)
{
    if (currentLib == "lib/arcade_ncurses.so") {
        _currentLibraryIndex = 2;
    } else if (currentLib == "lib/arcade_sfml.so") {
        _currentLibraryIndex = 0;
    } else if (currentLib == "lib/arcade_sdl2.so") {
        _currentLibraryIndex = 1;
    } else
        _currentLibraryIndex = 0;
}

void Core::setGraphic(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule) {
    delete graphicModule;
    graphicModule = nullptr;
    loader1.unload();
    loader1.load(_libraryPaths[_currentLibraryIndex]);
    graphicModule = loader1.getInstance();
}

void Core::start(DLLoader<IGraphicModule> &loader1, std::string firstLibraryPath) {
    DLLoader<IGameModule> game(_gamePaths[0].second);
    loadGameModule(game, _gamePaths[0].second);
    IGraphicModule* graphicModule = loadGraphicModule(loader1);
    IGameModule* gameModule = loadGameInstance(game);
    AttributeCurrentLibIndex(firstLibraryPath);

    int selectedIndex = handleMenu(graphicModule, loader1);

    setGraphic(loader1, graphicModule);

    if (selectedIndex == -1) {
        return;
    }
    std::string selectedGamePath = _gamePaths[selectedIndex].second;
    loadGameModule(game, selectedGamePath);
    gameModule = loadGameInstance(game);
    using namespace std::chrono;
    auto next_move_time = steady_clock::now() + milliseconds(400);
    auto move_interval = milliseconds(400);
    auto speed_increase_interval = seconds(5);
    auto last_speed_increase_time = steady_clock::now();
    while (true) {
        if (!isGameOver(gameModule)) {
            graphicModule->display(gameModule->getMap(), gameModule->getScoreAsString());
            graphicModule->displayGameName(gameModule->getName());
        } else {
            handleGameOver(loader1, graphicModule, gameModule->getScore());
            return;
        }
        std::string event = graphicModule->handle_events();
        int event_code = event_map[event];
        if (handleEventSwitch(loader1, graphicModule, event_code) == 1) {
            return;
        }
        if (handleEventGame(game, gameModule, event_code) == 1) {
            return;
        }
        if (steady_clock::now() >= next_move_time) {
            handleMove(_direction);
            graphicModule->updateTexture(_direction);
            next_move_time += move_interval;
            int moveResult = gameModule->move(_direction);
            if (moveResult == 1) {
                graphicModule->playSound();
            } else if (moveResult == 2) {
                std::vector<std::string> validDirections = gameModule->getValidDirections();
                if (validDirections.size() == 1) {
                    _direction = validDirections[0];
                } else if (validDirections.empty()) {
                    handleGameOver(loader1, graphicModule, gameModule->getScore());
                    return;
                }
            }
        }
        if (_isBoosted) {
            move_interval = milliseconds(90);
        } else {
            if (steady_clock::now() - last_speed_increase_time >= speed_increase_interval) {
                move_interval = milliseconds(static_cast<int>(move_interval.count() * 0.9));
                last_speed_increase_time = steady_clock::now();
            }
        }
        std::this_thread::sleep_for(milliseconds(1));
    }
}