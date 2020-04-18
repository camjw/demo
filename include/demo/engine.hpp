#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <demo/input_processor.hpp>
#include <demo/timer.hpp>
#include <demo/window.hpp>
#include <demo/shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <vector>

class Engine
{

  public:
	Engine();
	~Engine();

	void process_input();

	void update(Time time);
	void late_update(Time time);
	void draw();

	bool is_running();

  private:
	Window *window = nullptr;
	InputProcessor *input = nullptr;

	Shader simple_shader;
	unsigned int VBO, VAO;
	unsigned int texture1, texture2;

    std::vector<float> vertices;
    std::vector<glm::vec3> cubePositions;
};
#endif
