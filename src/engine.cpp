#include <demo/engine.hpp>

Engine::Engine()
{
    window = new Window("Estuary King");
    camera = new Camera();
    input = new InputProcessor(window);

    simple_shader.init("./assets/shaders/simple_shader.vert", "./assets/shaders/simple_shader.frag");
    light_shader.init("./assets/shaders/lighting_shader.vert", "./assets/shaders/lighting_shader.frag");
    lamp_shader.init("./assets/shaders/lamp_shader.vert", "./assets/shaders/lamp_shader.frag");
    skybox_shader.init("./assets/shaders/skybox_shader.vert", "./assets/shaders/skybox_shader.frag");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    float skyboxVertices[] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f
    };

    glGenVertexArrays(1, &skybox_VAO);
    glGenBuffers(1, &skybox_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, skybox_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindVertexArray(skybox_VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glGenVertexArrays(1, &cube_VAO);
    glGenBuffers(1, &cube_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(cube_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glGenVertexArrays(1, &light_VAO);
    glBindVertexArray(light_VAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    texture1.build("assets/textures/sopranos_challenge.png");
    texture2.build("assets/textures/primal_scream.png");

    simple_shader.use();
    simple_shader.setInt("texture1", 0);
    simple_shader.setInt("texture2", 1);

    // seedn rng;
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < 100; i++)
    {
        cubes.push_back(glm::vec3(random_float(), random_float(), random_float()));
    }

    for (int i = 0; i < 4; i++)
    {
        lights.push_back(glm::vec3(random_float(), random_float(), random_float()));
    }

    std::vector<std::string> faces = {
        "assets/textures/skybox/right.png",
        "assets/textures/skybox/left.png",
        "assets/textures/skybox/top.png",
        "assets/textures/skybox/bottom.png",
        "assets/textures/skybox/front.png",
        "assets/textures/skybox/back.png",
    };

    skybox.build(faces);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window->get_glfw_window(), true);
    const char* glsl_version = "#version 330 core";
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

float Engine::random_float(float low, float high)
{
    return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

Engine::~Engine()
{
    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteBuffers(1, &cube_VBO);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete input;
    delete camera;
    delete window;
}

void Engine::update(Time time)
{
    window->update(time, input);
    camera->update(time, input);
}

void Engine::late_update(Time time)
{
}

void Engine::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    glActiveTexture(GL_TEXTURE0);
    texture1.bind();
    glActiveTexture(GL_TEXTURE1);
    texture2.bind();

    light_shader.use();
    light_shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);

    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);

    // directional light
    light_shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    light_shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    light_shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
    light_shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
    // point light 1
    light_shader.setVec3("pointLights[0].position", lights[0]);
    light_shader.setVec3("pointLights[0].colour", lightColor);
    light_shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    light_shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    light_shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    light_shader.setFloat("pointLights[0].constant", 1.0f);
    light_shader.setFloat("pointLights[0].linear", 0.09);
    light_shader.setFloat("pointLights[0].quadratic", 0.032);
    // point light 2
    light_shader.setVec3("pointLights[1].position", lights[1]);
    light_shader.setVec3("pointLights[1].colour", lightColor);
    light_shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    light_shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    light_shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    light_shader.setFloat("pointLights[1].constant", 1.0f);
    light_shader.setFloat("pointLights[1].linear", 0.09);
    light_shader.setFloat("pointLights[1].quadratic", 0.032);
    // point light 3
    light_shader.setVec3("pointLights[2].position", lights[2]);
    light_shader.setVec3("pointLights[2].colour", lightColor);
    light_shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    light_shader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    light_shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    light_shader.setFloat("pointLights[2].constant", 1.0f);
    light_shader.setFloat("pointLights[2].linear", 0.09);
    light_shader.setFloat("pointLights[2].quadratic", 0.032);
    // point light 4
    light_shader.setVec3("pointLights[3].position", lights[3]);
    light_shader.setVec3("pointLights[3].colour", lightColor);
    light_shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    light_shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    light_shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    light_shader.setFloat("pointLights[3].constant", 1.0f);
    light_shader.setFloat("pointLights[3].linear", 0.09);
    light_shader.setFloat("pointLights[3].quadratic", 0.032);
    // spotLight
    light_shader.setVec3("spotLight.position", camera->get_position());
    light_shader.setVec3("spotLight.direction", camera->get_forward_direction());
    light_shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    light_shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    light_shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    light_shader.setFloat("spotLight.constant", 1.0f);
    light_shader.setFloat("spotLight.linear", 0.09);
    light_shader.setFloat("spotLight.quadratic", 0.032);
    light_shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    light_shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    light_shader.setMat4("projection", window->get_projection_matrix());
    light_shader.setMat4("view", camera->get_view_matrix());
    light_shader.setVec3("viewPos", camera->get_position());

    light_shader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(cube_VAO);
    for (unsigned int i = 0; i < cubes.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubes[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        light_shader.setMat4("model", model);
        light_shader.setMat3("normalModel", glm::mat3(glm::transpose(glm::inverse(model))));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    lamp_shader.use();

    lamp_shader.setMat4("projection", window->get_projection_matrix());
    lamp_shader.setMat4("view", camera->get_view_matrix());

    lamp_shader.setVec3("lightColour", lightColor);

    glBindVertexArray(light_VAO);
    for (int i = 0; i < lights.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lights[i]);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lamp_shader.setMat4("model", model);
        lamp_shader.setMat3("normalModel", glm::mat3(glm::transpose(glm::inverse(model))));
        lamp_shader.setVec3("viewPos", camera->get_position());

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // draw skybox
    glDepthFunc(GL_LEQUAL);
    skybox_shader.use();
    skybox_shader.setMat4("view", glm::mat4(glm::mat3(camera->get_view_matrix())));
    skybox_shader.setMat4("projection", window->get_projection_matrix());

    glBindVertexArray(skybox_VAO);
    skybox.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

    // render your GUI
    ImGui::Begin("Demo window");
    ImGui::Button("Hello!");
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    int display_w, display_h;
    glfwGetFramebufferSize(window->get_glfw_window(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glfwSwapBuffers(window->get_glfw_window());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
