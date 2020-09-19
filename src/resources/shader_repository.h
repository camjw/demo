#ifndef DEMO_SHADER_REPOSITORY_H
#define DEMO_SHADER_REPOSITORY_H

#include <rendering/shader.h>

#include <templates/action.h>
#include <unordered_map>

class ShaderRepository
{
public:
    std::shared_ptr<Shader> get_shader(ShaderID shader_id);
    std::shared_ptr<Shader> get_shader(const std::string& shader_name);
    ShaderID get_shader_id(const std::string& shader_name);
    const std::string&  get_shader_name(ShaderID shader_id);
    ShaderID create_shader(const std::string& shader_name, const std::string& vertex_filename, const std::string& fragment_filename);

    void delete_shader(ShaderID mesh_id);
    void clear();
    void for_each(Action<Shader>* action);

    std::vector<std::shared_ptr<Shader>> get_all();

    ShaderComponent get_shader_component(const std::string& shader_name);

private:
    std::unordered_map<std::string, ShaderID> shader_name_to_shader_id;
    std::unordered_map<ShaderID, std::string> shader_id_to_shader_name;
    std::unordered_map<ShaderID, std::shared_ptr<Shader>> shaders;
    ShaderID current_shader_id = 0;
};

#endif //DEMO_SHADER_REPOSITORY_H
