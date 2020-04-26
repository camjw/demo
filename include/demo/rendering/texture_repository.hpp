#ifndef DEMO_RENDERING_TEXTURE_REPOSITORY_HPP
#define DEMO_RENDERING_TEXTURE_REPOSITORY_HPP

#include <demo/rendering/texture.hpp>

#include <unordered_map>

class TextureRepository
{
    public:
        std::shared_ptr<Texture> get_texture(TextureID texture_id);
        TextureID create_texture();
        TextureID create_texture(std::string filename);

        void delete_texture(TextureID mesh_id);

    private:
        std::unordered_map<TextureID, std::shared_ptr<Texture>> textures;
        TextureID current_texture_id = 0;
};

#endif