#pragma once
#ifndef IA_UI_ELEMENT_H
#define IA_UI_ELEMENT_H

#include <string>

#include <common/macros.h>
#include <ianium/ianium.h>

class IANIUM_EXPORT UIElement {
public:
    UIElement(const Ianium::UIType type, const int id, const int posX, const int posY, const int w, const int h, const bool active, const char* menu)
        : id(id), posX(posX), posY(posY), width(w), height(h), isActive(active), menu(menu)
    { Ianium::Instance()->addTestableUIElem(type, this); }

    // Devuelve la ID del elemento
    uint64_t getID() const { return id; }
    // Devuelve la posición (X, Y) del elemento
    std::pair<uint32_t, uint32_t> getPosition() const { return std::make_pair(posX, posY); }
    // Devuelve el tamaño (ancho, alto) del elemento
    std::pair<uint32_t, uint32_t> getSize() const { return std::make_pair(width, height); }
    // Devuelve el estado del elemento
    bool getEnable() const { return isActive; }
    // Devuelve el menú al que pertenece el elemento
    const char* getMenu() const { return menu; }

private:
    uint64_t id;            // ID único del elemento
    uint32_t posX, posY;    // Posición X e Y del elemento
    uint32_t width, height; // Ancho y alto del elemento                
    bool isActive;          // Estado del elemento (Activado o desactivado)             
    const char* menu;       // Menú al que pertenece el elemento     
};
#endif // IA_UI_ELEMENT_H