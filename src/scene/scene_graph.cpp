#include "scene_graph.h"

SceneNode* SceneGraph::find_named_node(const std::string& node_name) const
{
    SceneNode* output = nullptr;
    std::function<bool(const SceneNode*)> callback = NameCheckerCallback(node_name, world);

    bool found_node = depth_first_search(root_node.get(), callback, output);
    if (!found_node)
    {
        printf("Failed to find node with name %s\n", node_name.c_str());
    }
    return output;
}

bool SceneGraph::depth_first_search(SceneNode* current_node, const std::function<bool(const SceneNode*)> searcher, SceneNode* output) const
{
    if (searcher(current_node))
    {
        *output = *current_node;
        return true;
    }

    std::vector<SceneNode*> children = current_node->get_children();
    for (int i = 0; i < children.size(); i++)
    {
        if (searcher(children[i]))
        {
            *output = *children[i];
            return true;
        }
    }

    return false;
}
