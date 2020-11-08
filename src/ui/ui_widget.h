#ifndef DEMO_UI_WIDGET_H
#define DEMO_UI_WIDGET_H

#include <imgui/imgui.h>

class UIWidget
{
public:
    virtual void draw() = 0;
    bool is_active = false;
};

#endif // DEMO_UI_WIDGET_H
