#ifndef DEMO_SHADER_REPOSITORY_H
#define DEMO_SHADER_REPOSITORY_H

#include <demo/rendering/shader.h>

#include <unordered_map>

class ShaderRepository
{
public:
    std::shared_ptr<Shader> get_shader(ShaderID shader_id);
    ShaderID create_shader();
    ShaderID create_shader(const std::string& vertex_filename, const std::string& fragment_filename);

    void delete_shader(ShaderID mesh_id);
    void clear();

private:
    std::unordered_map<ShaderID, std::shared_ptr<Shader>> shaders;
    ShaderID current_shader_id = 0;
};

#endif //DEMO_SHADER_REPOSITORY_H
