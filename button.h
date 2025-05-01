#pragma once
#include <graphics.h>
#include <string>
#include <functional>

#include "util.h"
#include "camera.h"
#include "resources_manager.h"

class Button 
{
public:
    enum class State
    {
        IDLE,
        HOVER,
        PRESS
    };

public:
    Button();
    ~Button();

    void set_image(std::string button_name);

    void on_render(const Camera& camera);

    void on_input(const ExMessage& msg);
    
    void on_update(int delta);

    void set_on_click(std::function<void()> on_click)
    {
        this->on_click = on_click;
    }

    void set_pos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void set_size(int w, int h)
    {
        this->w = w;
        this->h = h;
    }

private:
    int x, y;
    int w, h;
    IMAGE idle;
    IMAGE hover;
    IMAGE press;
    State state;
    std::function<void()> on_click;

    bool isInside(int px, int py) const 
    {
        return (px >= x && px <= x + w && py >= y && py <= y + h);
    }
};