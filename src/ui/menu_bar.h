#ifndef DEMO_MENU_BAR_H
#define DEMO_MENU_BAR_H

#include "event_repository.h"
#include "ui_widget.h"

class MenuBar : public UIWidget
{
public:
    MenuBar(EventRepository* event_repository);
    virtual ~MenuBar() { }

    virtual void draw() override;

private:
    EventRepository* event_repository;
};

#endif //DEMO_MENU_BAR_H
