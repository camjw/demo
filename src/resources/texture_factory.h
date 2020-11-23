#ifndef DEMO_TEXTURE_FACTORY_HPP
#define DEMO_TEXTURE_FACTORY_HPP

#include "resource_factory.h"
#include <rendering/data/texture.h>
#include <utils/opengl_helpers.h>

class TextureFactory : public ResourceFactory<Texture>
{
public:
    explicit TextureFactory()
        : ResourceFactory("assets/textures") {};

protected:
    inline virtual std::shared_ptr<Texture> build(const std::string& name) override
    {
        std::shared_ptr<Texture> output = std::make_shared<Texture>(get_full_path(name));
        glCheckError();
        return output;
    }
};

#endif // DEMO_TEXTURE_FACTORY_HPP