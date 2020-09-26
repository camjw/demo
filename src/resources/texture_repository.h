#ifndef DEMO_RENDERING_TEXTURE_REPOSITORY_HPP
#define DEMO_RENDERING_TEXTURE_REPOSITORY_HPP

#include <rendering/texture.h>

#include <unordered_map>

class TextureRepository
{
public:
    std::shared_ptr<Texture> get_texture(TextureID texture_id);
    TextureID get_texture_id(const std::string& texture_name);
    TextureID create_texture(const std::string& texture_name, const std::string& filename);
    TextureID create_texture(const std::string& texture_name, const aiTexture* assimp_texture);

    void delete_texture(TextureID texture_id);
    void clear();

private:
    std::unordered_map<std::string, TextureID> texture_names_to_ids;
    std::unordered_map<TextureID, std::shared_ptr<Texture>> textures;
    TextureID current_texture_id = 0;
};

#endif