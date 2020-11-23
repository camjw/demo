#ifndef DEMO_CUBE_MAP_FACTORY_H
#define DEMO_CUBE_MAP_FACTORY_H

#include <rendering/data/cube_map.h>
#include <utils/opengl_helpers.h>
#include <resources/resource_factory.h>

class CubeMapFactory : public ResourceFactory<CubeMap>
{
public:
    explicit CubeMapFactory()
        : ResourceFactory<CubeMap>("assets/skyboxes")
    {
    }

protected:
    inline virtual std::shared_ptr<CubeMap> build(const std::string& name) override
    {
        std::vector<std::string> cube_map_images = get_cube_map_files(get_full_path(name));
        std::shared_ptr<CubeMap> output = std::make_shared<CubeMap>(cube_map_images);
        glCheckError();
        return output;
    }

private:
    std::vector<std::string> get_cube_map_files(const std::string& cube_map_directory) const;

};

#endif // DEMO_CUBE_MAP_FACTORY_H
