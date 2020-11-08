#ifndef DEMO_MATERIAL_EDITOR_H
#define DEMO_MATERIAL_EDITOR_H

#include "ui_widget.h"
#include <ecs/world.h>
#include <memory>

class MaterialEditor : public UIWidget
{
    MaterialEditor(std::shared_ptr<World> world)
        : UIWidget()
        , world(world)
    {
    }
    virtual void draw() override;

private:
    std::shared_ptr<World> world;
};

#endif //DEMO_MATERIAL_EDITOR_H
