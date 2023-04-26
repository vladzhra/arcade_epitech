/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley [WSL : Debian]
** File description:
** IElement.hpp
*/

#ifndef IELEMENT_H
#define IELEMENT_H

#include <SFML/Graphics.hpp>

class IElement {
public:
    virtual ~IElement() = default;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget &target) const = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setSize(const sf::Vector2f &size) = 0;
    virtual sf::Vector2f getSize() const = 0;
    virtual void setColor(const sf::Color &color) = 0;
    virtual sf::Color getColor() const = 0;
};

#endif // IELEMENT_H
