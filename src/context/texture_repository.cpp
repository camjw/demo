#include <demo/context/texture_repository.h>
#include <demo/utils/opengl_helpers.h>

std::shared_ptr<Texture> TextureRepository::get_texture(TextureID texture_id)
{
    assert(textures.find(texture_id) != textures.end() && "No such texture.");

    return textures[texture_id];
}

TextureID TextureRepository::get_texture_id(const std::string& texture_name)
{
    assert(texture_names_to_ids.find(texture_name) != texture_names_to_ids.end() && "No such texture.");

    return texture_names_to_ids[texture_name];
}

TextureID TextureRepository::create_texture(const std::string& texture_name, const std::string& filename)
{
    std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(filename);

    texture_names_to_ids.insert(std::make_pair(texture_name, current_texture_id));
    textures.insert(std::make_pair(current_texture_id++, new_texture));
    glCheckError();

    return current_texture_id;
}

void TextureRepository::delete_texture(TextureID texture_id)
{
    assert(textures.find(texture_id) != textures.end() && "Removing non-existent texture.");

    std::shared_ptr<Texture> texture_to_delete = textures[texture_id];
    texture_to_delete->destroy();
    textures.erase(texture_id);
}

void TextureRepository::clear()
{
    for (auto texture : textures)
    {
        delete_texture(texture.first);
    }
}
