#ifndef DEMO_OPEN_SCENE_HIERARCHY_EVENT_H
#define DEMO_OPEN_SCENE_HIERARCHY_EVENT_H

#include <ui/event.h>
#include <ui/event_processors/event_processor.h>

class SetSceneHierarchyViewerVisibleEvent : public Event
{
public:
    SetSceneHierarchyViewerVisibleEvent(bool is_visible)
        : Event()
        , is_visible(is_visible)
    {
    }

    virtual ~SetSceneHierarchyViewerVisibleEvent() { }

    static constexpr const char* type = "SetSceneHierarchyViewerVisible";

    bool is_visible;

    virtual const char* get_type() const override
    {
        return type;
    }
};

class SceneHierarchyViewer;
class SetSceneHierarchyViewerVisibleEventProcessor : public EventProcessor
{
public:
    SetSceneHierarchyViewerVisibleEventProcessor(SceneHierarchyViewer* scene_hierarchy_viewer)
        : scene_hierarchy_viewer(scene_hierarchy_viewer)
    {
    }

    virtual void process_event(const Event* event) override;

private:
    SceneHierarchyViewer* scene_hierarchy_viewer;
};
#endif // DEMO_OPEN_SCENE_HIERARCHY_EVENT_H
