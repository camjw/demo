#include "first_scene.h"

FirstScene::FirstScene()
{
    camera = std::make_shared<Camera>();
}

void FirstScene::on_create()
{
    // Need to load up textures, meshes, entities, shaders here
}

void FirstScene::on_destroy()
{
    // Dump all of those here
}

std::shared_ptr<Camera> FirstScene::get_active_camera()
{
    return camera;
}
