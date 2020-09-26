#include "shader_repository.h"

std::shared_ptr<Shader> ShaderRepository::get_shader(ShaderID shader_id)
{
    assert(shaders.find(shader_id) != shaders.end() && "No such shader.");

    return shaders[shader_id];
}

std::shared_ptr<Shader> ShaderRepository::get_shader(const std::string& shader_name)
{
    assert(shader_name_to_shader_id.find(shader_name) != shader_name_to_shader_id.end() && "No such shader.");

    return shaders[shader_name_to_shader_id[shader_name]];
}

ShaderID ShaderRepository::get_shader_id(const std::string& shader_name)
{
    assert(shader_name_to_shader_id.find(shader_name) != shader_name_to_shader_id.end() && "No shader with that name");

    return shader_name_to_shader_id[shader_name];
}

const std::string& ShaderRepository::get_shader_name(ShaderID shader_id)
{
    assert(shaders.find(shader_id) != shaders.end() && "No shader with that ID");

    return shader_id_to_shader_name[shader_id];
}

ShaderID ShaderRepository::create_shader(const std::string& shader_name)
{
    const std::string& vertex_filename = DEMO_CONSTANTS_SHADERS_FOLDER + shader_name + "_shader.vert";
    const std::string& fragment_filename = DEMO_CONSTANTS_SHADERS_FOLDER + shader_name + "_shader.frag";

    return create_shader(shader_name, vertex_filename, fragment_filename);
}

ShaderID ShaderRepository::create_shader(
    const std::string& shader_name,
    const std::string& vertex_filename,
    const std::string& fragment_filename)
{
    std::shared_ptr<Shader> new_shader = std::make_shared<Shader>();
    new_shader->init(vertex_filename, fragment_filename);

    shader_name_to_shader_id.insert(std::pair<std::string, ShaderID>(shader_name, ++current_shader_id));
    shader_id_to_shader_name.insert(std::pair<ShaderID, std::string>(current_shader_id, shader_name));
    shaders.insert(std::pair<ShaderID, std::shared_ptr<Shader>>(current_shader_id, new_shader));
    glCheckError();

    return current_shader_id;
}

void ShaderRepository::delete_shader(ShaderID shader_id)
{
    assert(shaders.find(shader_id) != shaders.end() && "Removing non-existent shader.");

    std::shared_ptr<Shader> shader_to_delete = shaders[shader_id];
    shader_to_delete->destroy();
    shaders.erase(shader_id);
    std::string shader_name = shader_id_to_shader_name[shader_id];
    shader_id_to_shader_name.erase(shader_id);
    shader_name_to_shader_id.erase(shader_name);
}

void ShaderRepository::clear()
{
    for (const auto& shader : shaders)
    {
        delete_shader(shader.first);
    }
}

void ShaderRepository::for_each(std::function<void(std::shared_ptr<Shader>)> action)
{
    for (const auto& shader : shaders)
    {
        action(shader.second);
    }
}

ShaderComponent ShaderRepository::get_shader_component(const std::string& shader_name)
{
    assert(shader_name_to_shader_id.find(shader_name) != shader_name_to_shader_id.end() && "No shader with that name");

    return ShaderComponent(shader_name_to_shader_id[shader_name]);
}

std::vector<std::shared_ptr<Shader>> ShaderRepository::get_all()
{
    std::vector<std::shared_ptr<Shader>> output;

    for (const auto& shader: shaders)
    {
        output.push_back(shader.second);
    }

    return output;
}
