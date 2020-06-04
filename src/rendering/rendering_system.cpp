#include <demo/rendering/rendering_system.hpp>
#include <random>

RenderingSystem::RenderingSystem()
{
    mesh_repository = new MeshRepository();
    texture_repository = new TextureRepository();

    glEnable(GL_CULL_FACE);
}

RenderingSystem::~RenderingSystem()
{
    delete mesh_repository;
    delete texture_repository;
}

void RenderingSystem::destroy()
{
    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteBuffers(1, &cube_VBO);
}

void RenderingSystem::init(Window* window, Camera* camera, Coordinator* coordinator)
{
    this->window = window;
    this->camera = camera;
    this->coordinator = coordinator;

    simple_shader.init("./assets/shaders/simple_shader.vert", "./assets/shaders/simple_shader.frag");

    MeshID cube_mesh_id = mesh_repository->create_cube();
    std::shared_ptr<Mesh> cube_mesh = mesh_repository->get_mesh(cube_mesh_id);
    cube_VAO = cube_mesh->VAO;
    cube_EBO = cube_mesh->EBO;

    // seed rng;
    srand(static_cast<unsigned>(time(0)));
	std::default_random_engine generator;
	std::uniform_real_distribution<float> rand_position(-10.0f, 10.0f);

    for (int i = 0; i < 100; i++)
    {
        cubes.push_back(glm::vec3(rand_position(generator), rand_position(generator), rand_position(generator)));
    }
}

void RenderingSystem::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    simple_shader.use();
    simple_shader.setMat4("projection", window->get_projection_matrix());
    simple_shader.setMat4("view", camera->get_view_matrix());
    glBindVertexArray(cube_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);
    for (unsigned int i = 0; i < cubes.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubes[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        simple_shader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);    
    }
    
    glBindVertexArray(0);

    glfwSwapBuffers(window->get_glfw_window());
}
