#pragma once

#include <iostream>

class UIElement {
private:

    // ID único del elemento
    long id;

    // Posición X e Y del elemento
    float positionX, positionY;

    // Ancho y alto del elemento
    float width, height;                  

    // Estado del elemento (Activado o desactivado)
    bool isActive;              

    // Menú al que pertenece el elemento
    std::string menu;           

public:
    UIElement(int id, int posX, int posY, int w, int h, bool active, const std::string& menu)
        : id(id), positionX(posX), positionY(posY), width(w), height(h), isActive(active), menu(menu) {
    }

    // Devuelve el estado del elemento
    bool getEnable() const {
        return isActive;
    }

    // Devuelve la posición (X, Y) del elemento
    std::pair<int, int> getPosition() const {
        return std::make_pair(positionX, positionY);
    }

    // Devuelve el tamaño (ancho, alto) del elemento
    std::pair<int, int> getSize() const {
        return std::make_pair(width, height);
    }

    // Devuelve el menú al que pertenece el elemento
    std::string getMenu() const {
        return menu;
    }
};