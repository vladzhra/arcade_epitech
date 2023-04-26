/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** DLLoader.hpp
*/

#ifndef DLLoader_HPP
#define DLLoader_HPP
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include <string>

template<typename T>
class DLLoader {
public:
    explicit DLLoader(const std::string& filename) {
        handle = dlopen(filename.c_str(), RTLD_LAZY);
        if (!handle) {
            throw std::invalid_argument(std::string(dlerror()));
        }
    }

    ~DLLoader() {
        if (handle) {
            dlclose(handle);
            handle = nullptr;
        }
    }

    void unload() {
        if (handle) {
            dlclose(handle);
            handle = nullptr;
        }
    }

    void load(const std::string& filename) {
        handle = dlopen(filename.c_str(), RTLD_LAZY);
        if (!handle) {
            throw std::invalid_argument(std::string(dlerror()));
        }
    }

    T* getInstance() {
        typedef T* (*entryPointPtr)();
        entryPointPtr entryPoint = reinterpret_cast<entryPointPtr>(dlsym(handle, "entryPoint"));
        if (!entryPoint) {
            throw std::runtime_error("Failed to load symbol 'entryPoint' from shared library: " + std::string(dlerror()));
        }
        return entryPoint();
    }
    void* handle{nullptr};
protected:
private:
};

#endif