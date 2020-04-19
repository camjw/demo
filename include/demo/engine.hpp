#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <demo/input_processor.hpp>
#include <demo/timer.hpp>
#include <demo/window.hpp>
#include <demo/shader.hpp>
#include <demo/texture.hpp>
#include <demo/camera.hpp>

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
    float random_float(float low = -5, float high = 15);

	Window *window = nullptr;
	InputProcessor *input = nullptr;
    Camera *camera = nullptr;

	Shader simple_shader;
	Shader light_shader;
	Shader lamp_shader;
	unsigned int cube_VBO, cube_VAO, light_VAO;
    Texture texture1, texture2;

    std::vector<glm::vec3> cubes;
    std::vector<glm::vec3> lights;
};
#endif
