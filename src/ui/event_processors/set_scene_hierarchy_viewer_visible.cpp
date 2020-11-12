#include <ui/scene_hierarchy_viewer.h>
#include "set_scene_hierarchy_viewer_visible.h"

void SetSceneHierarchyViewerVisibleEventProcessor::process_event(const Event* event)
{
    const SetSceneHierarchyViewerVisibleEvent* set_scene_hierarchy_viewer_visible_event = static_cast<const SetSceneHierarchyViewerVisibleEvent*>(event);
    scene_hierarchy_viewer->is_active = set_scene_hierarchy_viewer_visible_event->is_visible;
}