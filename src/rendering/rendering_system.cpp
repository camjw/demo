#include <demo/rendering/rendering_system.h>
#include <demo/utils/opengl_helpers.h>

void RendererSystem::init(std::shared_ptr<DemoContext> context,
    Window* _window, std::shared_ptr<Coordinator> _coordinator)
{
    glEnable(GL_CULL_FACE);

    glCheckError();

    this->window = _window;
    this->coordinator = _coordinator;

    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    shader_repository = context->get_shader_repository();
}

void RendererSystem::begin_draw(Time time)
{
    glCheckError();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCheckError();

    // Set common variables for shaders
//    shader_repository->for_all(new SetShaderTime(time));
//    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));
    glCheckError();

}

void RendererSystem::draw_entities()
{
    for (Entity const& entity: entities)
    {
        draw_entity(entity);
        glCheckError();
    }
}

void RendererSystem::draw_entity(Entity entity)
{
    if (coordinator->has_component<TextureComponent>(entity))
    {
        TextureComponent texture = coordinator->get_component<TextureComponent>(entity);
        texture_repository->get_texture(texture.id)->bind(texture.binding_index);
        glCheckError();
    }

    ShaderComponent shader = coordinator->get_component<ShaderComponent>(entity);
    auto shader_ptr = shader_repository->get_shader(shader.id);
    shader_ptr->bind();
    glCheckError();

    glCheckError();
    MeshComponent mesh = coordinator->get_component<MeshComponent>(entity);
    std::shared_ptr<Mesh> render_mesh = mesh_repository->get_mesh(mesh.id);
    render_mesh->bind();
    glCheckError();
    render_mesh->draw();
    glCheckError();
}

void RendererSystem::debug_screen_space_rendering()
{

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

        // build and compile our shader program
        // ------------------------------------
        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        // link shaders
        int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//void RendererSystem::draw_skybox(Skybox* skybox)
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

void RendererSystem::end_draw()
{
    //    draw_skybox();
    glfwSwapBuffers(window->get_glfw_window());
    glfwPollEvents();
}

void RendererSystem::set_camera(Scene* scene)
{
    Entity camera_entity = scene->get_active_camera();

    if (!coordinator->has_component<CameraComponent>(camera_entity))
    {
        printf("Scene does not have a camera set\n");
        return;
    }

    CameraComponent& camera = coordinator->get_component<CameraComponent>(camera_entity);

//    shader_repository->for_all(new SetShaderCamera(
//        camera.position,
//        camera.forward,
//        camera.get_view_matrix()));

    glCheckError();
}

void RendererSystem::draw(Time time, Scene* scene)
{
//    set_camera(scene);
    begin_draw(time);
//    draw_entities();
    debug_screen_space_rendering();
    end_draw();
}
