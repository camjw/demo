#ifndef DEMO_SCENE_HIERARCHY_VIEWER_H
#define DEMO_SCENE_HIERARCHY_VIEWER_H

#include "ui_widget.h"
#include <scene/scene_manager.h>

class SceneHierarchyViewer : public UIWidget
{
public:
    SceneHierarchyViewer(std::shared_ptr<SceneManager> scene_manager, std::shared_ptr<World> world)
        : UIWidget()
        , scene_manager(scene_manager)
        , world(world)
    {
    }

    virtual void draw() override;

private:
    void draw_scene_node_inspector(SceneNode* node);
    std::shared_ptr<SceneManager> scene_manager;
    std::shared_ptr<World> world;
};

#endif //DEMO_SCENE_HIERARCHY_VIEWER_H
