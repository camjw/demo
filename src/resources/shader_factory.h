#ifndef DEMO_SHADER_FACTORY_H
#define DEMO_SHADER_FACTORY_H

#include "resource_factory.h"
#include <rendering/data/shader.h>
#include <utils/opengl_helpers.h>

class ShaderFactory : public ResourceFactory<Shader>
{
public:
    explicit ShaderFactory()
        : ResourceFactory("assets/shaders")
    {
    }

protected:
    inline virtual std::shared_ptr<Shader> build(const std::string& name) override
    {
        const std::string& shader_directory = get_full_path(name);
        std::shared_ptr<Shader> output = std::make_shared<Shader>(
            shader_directory + "/shader.vert",
            shader_directory + "/shader.frag");
        
        glCheckError();
        return output;
    }
};
#endif // DEMO_SHADER_FACTORY_H
