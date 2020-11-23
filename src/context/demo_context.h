#ifndef DEMO_DEMO_CONTEXT_H
#define DEMO_DEMO_CONTEXT_H

#include <import/model_importer.h>
#include <memory>
#include <resources/material_factory.h>
#include <resources/mesh_factory.h>
#include <resources/resource_manager.h>
#include <resources/shader_factory.h>
#include <resources/texture_factory.h>

class DemoContext
{
public:
    explicit DemoContext(std::shared_ptr<World> world);

    inline std::shared_ptr<ResourceManager> get_resource_manager() const
    {
        return resource_manager;
    }

    inline std::shared_ptr<ModelImporter> get_model_importer() const
    {
        return model_importer;
    }

private:
    std::shared_ptr<ResourceManager> resource_manager;
    std::shared_ptr<ModelImporter> model_importer;
};

#endif //DEMO_DEMO_CONTEXT_H
