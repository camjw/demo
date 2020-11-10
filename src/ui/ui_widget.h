#ifndef DEMO_UI_WIDGET_H
#define DEMO_UI_WIDGET_H

#include <imgui/imgui.h>

class UIWidget
{
public:
    inline void draw_if_active()
    {
        if (is_active)
        {
            draw();
        }
    }

    bool is_active = false;

private:
    virtual void draw() = 0;
};

#endif // DEMO_UI_WIDGET_H
