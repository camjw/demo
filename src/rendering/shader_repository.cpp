#include <demo/rendering/shader_repository.h>

std::shared_ptr<Shader> ShaderRepository::get_shader(ShaderID shader_id)
{
    assert(shaders.find(shader_id) != shaders.end() && "No such shader.");

    return shaders[shader_id];
}

ShaderID ShaderRepository::create_shader()
{
    std::shared_ptr<Shader> new_shader = std::make_shared<Shader>();

    shaders.insert(std::make_pair(current_shader_id++, new_shader));
    return current_shader_id;
}

ShaderID ShaderRepository::create_shader(const std::string& vertex_filename, const std::string& fragment_filename)
{
    std::shared_ptr<Shader> new_shader = std::make_shared<Shader>();
    new_shader->init(vertex_filename, fragment_filename);

    shaders.insert(std::make_pair(current_shader_id++, new_shader));
    return current_shader_id;
}

void ShaderRepository::delete_shader(ShaderID shader_id)
{
    assert(shaders.find(shader_id) != shaders.end() && "Removing non-existent shader.");

    std::shared_ptr<Shader> shader_to_delete = shaders[shader_id];
    shader_to_delete->destroy();
    shaders.erase(shader_id);
}

void ShaderRepository::clear()
{
    for (auto shader: shaders)
    {
        delete_shader(shader.first);
    }
}

void ShaderRepository::for_all(Action<Shader>* action)
{
    for (auto shader: shaders)
    {
        action->run(shader.second);
    }
}
