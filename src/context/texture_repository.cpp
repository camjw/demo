#include <demo/context/texture_repository.h>

std::shared_ptr<Texture> TextureRepository::get_texture(TextureID texture_id)
{
    assert(textures.find(texture_id) != textures.end() && "No such texture.");

    return textures[texture_id];
}

TextureID TextureRepository::create_texture()
{
    std::shared_ptr<Texture> new_texture = std::make_shared<Texture>();

    textures.insert(std::make_pair(current_texture_id++, new_texture));
    return current_texture_id;
}

TextureID TextureRepository::create_texture(std::string filename)
{
    std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(filename);

    textures.insert(std::make_pair(current_texture_id++, new_texture));
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