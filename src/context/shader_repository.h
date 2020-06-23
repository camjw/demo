#ifndef DEMO_SHADER_REPOSITORY_H
#define DEMO_SHADER_REPOSITORY_H

#include <rendering/shader.h>

#include <unordered_map>
#include <templates/action.h>

class ShaderRepository
{
public:
    std::shared_ptr<Shader> get_shader(ShaderID shader_id);
    std::shared_ptr<Shader> get_shader(const std::string& shader_name);
    ShaderID get_shader_id(const std::string& shader_name);
    ShaderID create_shader(const std::string& shader_name);
    ShaderID create_shader(const std::string& shader_name, const std::string& vertex_filename, const std::string& fragment_filename);

    void delete_shader(ShaderID mesh_id);
    void clear();
    void for_all(Action<Shader>* action);

private:
    std::unordered_map<std::string, ShaderID> shader_name_to_shader_id;
    std::unordered_map<ShaderID, std::shared_ptr<Shader>> shaders;
    ShaderID current_shader_id = 0;
};

#endif //DEMO_SHADER_REPOSITORY_H
