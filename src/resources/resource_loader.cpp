#include <resources/resource_loader.h>

TextureID ResourceLoader::get_or_create_texture(const std::string& texture_name, const std::string& filename)
{
    return texture_repository->create_texture(texture_name, filename);
}

ShaderID ResourceLoader::get_or_create_shader(const std::string& shader_name, const std::string& vertex_filename, const std::string& fragment_filename)
{
    return shader_repository->create_shader(shader_name, vertex_filename, fragment_filename);
}

CubeMapID ResourceLoader::get_or_create_cube_map(const std::string& cube_map_name, const std::string& cube_map_directory)
{
    return cube_map_repository->create_cube_map(cube_map_name, cube_map_directory);
}
