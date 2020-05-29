#include <demo/rendering/rendering_system.h>

void RenderingSystem::init(std::shared_ptr<DemoContext> context, Window* window, Coordinator* coordinator)
{
    glEnable(GL_CULL_FACE);

    printf("Getting repositories");
    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    shader_repository = context->get_shader_repository();

    printf("Getting window and coordinator");
    this->window = window;
    this->coordinator = coordinator;

//    std::vector<std::string> faces = {
//        "assets/textures/skybox/right.png",
//        "assets/textures/skybox/left.png",
//        "assets/textures/skybox/top.png",
//        "assets/textures/skybox/bottom.png",
//        "assets/textures/skybox/front.png",
//        "assets/textures/skybox/back.png",
//    };
//
//    skybox.build(faces);
}

void RenderingSystem::begin_draw(Time time)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    shader_repository->for_all(new SetShaderTime(time));
    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));
}

void RenderingSystem::draw_entities()
{

}

//void RenderingSystem::draw_skybox(Skybox* skybox)
//{
//    //draw skybox
//    glDepthFunc(GL_LEQUAL);
//    skybox_shader.use();
//    skybox_shader.setMat4("view", glm::mat4(glm::mat3(camera->get_view_matrix())));
//    skybox_shader.setMat4("projection", window->get_projection_matrix());
//
//    glBindVertexArray(skybox_VAO);
//    skybox.bind();
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
//    glBindVertexArray(0);
//    glDepthFunc(GL_LESS);
//}

void RenderingSystem::end_draw()
{
//    draw_skybox();
    glfwSwapBuffers(window->get_glfw_window());
}

void RenderingSystem::set_camera(Scene* scene)
{
    std::shared_ptr<Camera> camera = scene->get_active_camera();

    shader_repository->for_all(new SetShaderCamera(
        camera->get_position(),
        camera->get_forward_direction(),
        camera->get_view_matrix()));
}

void RenderingSystem::draw(Time time, Scene* scene)
{
    set_camera(scene);
    begin_draw(time);
    draw_entities();
    end_draw();
}
