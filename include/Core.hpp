/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** core.hpp
*/

#ifndef Core_HPP
    #define Core_HPP

#include "IGameModule.hpp"
#include "IGraphicModule.hpp"
#include "DLLoader.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <dlfcn.h>
#include <dirent.h>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <future>

class Core {
public:
    Core() {
        loadLibraries();
    }
    ~Core() {}
    void start(DLLoader<IGraphicModule> &loader1, std::string firstLibraryPath);
    IGameModule *loadMenu(DLLoader<IGameModule> &game, DLLoader<IGraphicModule> &loader1, IGraphicModule* graphicModule);
    int handleMovement(IGameModule *gameModule, IGraphicModule* graphicModule);
    int handleDirection(IGameModule *gameModule, IGraphicModule* graphicModule, DLLoader<IGraphicModule> &loader1);
    void gameCore(DLLoader<IGraphicModule> &loader1);
    std::unordered_map<std::string, int> event_map = {
        {"L", 1},
        {"UP", 2},
        {"DOWN", 3},
        {"LEFT", 4},
        {"RIGHT", 5},
        {"SPACE", 6},
        {"ESCAPE", 7},
        {"ENTER", 8},
        {"G", 9},
        {"R", 10},
    };
protected:
    void loadLibraries(void);
    void AttributeCurrentLibIndex(std::string &currentLib);
    // void handleEscape(DLLoader<IGraphicModule> &loader1);
    void handleEscape(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule);
    void handleSpace();
    void handleMove(const std::string &direction);
    void handleLKey(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule);
    void handleGKey(DLLoader<IGameModule> &loader1, IGameModule* &gameModule);
    int handleEventSwitch(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule, int event_code);
    int handleEventGame(DLLoader<IGameModule> &loader1, IGameModule* &gameModule, int event_code);
    void handleGameOver(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule, int score);
    bool isGameOver(IGameModule* gameModule);
    IGameModule* loadGameInstance(DLLoader<IGameModule> &game);
    IGraphicModule* loadGraphicModule(DLLoader<IGraphicModule> &loader1);
    void loadGameModule(DLLoader<IGameModule> &game, const std::string &filename);
    int handleMenu(IGraphicModule* &graphicModule, DLLoader<IGraphicModule> &loader1);
    void setGraphic(DLLoader<IGraphicModule> &loader1, IGraphicModule* &graphicModule);
private:
    std::vector<std::string> _libraryPaths = {};
    std::vector<std::pair<std::string, std::string>> _gamePaths = {};
    size_t _selectedGameIndex = 0;
    size_t _currentLibraryIndex = 0;
    std::string _direction = "LEFT";
    bool _isBoosted = false;
};

#endif