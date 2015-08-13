#ifndef SDL2D3_EVENTS_H
#define SDL2D3_EVENTS_H

#include <SFML/Graphics.hpp>

//Emitted when the user changes gravity via the GUI window
struct GravityChangeEvent {
    GravityChangeEvent(float nx, float ny) : x(nx), y(ny) {}
    float x, y;
};

//No data, just emitted when the light textures/shaders should be reloaded
struct LightReloadEvent { };

//Adjusting sliders on the GUI--change light color
struct LightColorEvent {
    LightColorEvent(sf::Color color) : color(color) { }
    sf::Color color;
};

//Emitted from the GUI checkboxes under "Graphics"
struct GraphicsEvent {
    //Which checkbox was checked
    enum TYPE {
        ImageRender = 0,
        RandomTextures,
        ShowAAABs,
        ShowPositions,
        WindowCollision,
    } type;

    //The new value
    bool value;

    GraphicsEvent(int type, bool value) : type((TYPE)type), value(value) { }
};

/* Emitted when a click is made outside the window, indicates
 * the entity closest to these coordinates should should be destroyed */
struct EntityRemoveEvent
{
    EntityRemoveEvent(float x, float y) : x(x), y(y) { }
    float x, y;
};

#endif
