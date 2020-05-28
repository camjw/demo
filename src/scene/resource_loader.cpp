#include <demo/scene/resource_loader.h>

MeshID ResourceLoader::get_or_create_mesh(const std::string& filename)
{
    // TODO: this doesn't work because the mesh repository can't load in models
    return mesh_repository->get_or_create_mesh(filename);
}

TextureID ResourceLoader::get_or_create_texture(const std::string& filename)
{
    return texture_repository->create_texture(filename);
}

ShaderID ResourceLoader::get_or_create_shader(const std::string &vertex_filename, const std::string &fragment_filename)
{
    return shader_repository->create_shader(vertex_filename, fragment_filename);
}