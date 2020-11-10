#ifndef DEMO_MENU_BAR_H
#define DEMO_MENU_BAR_H

#include "ui_widget.h"

class MenuBar : public UIWidget
{
public:
    MenuBar();
    virtual ~MenuBar() { }

    virtual void draw() override;
};

#endif //DEMO_MENU_BAR_H
