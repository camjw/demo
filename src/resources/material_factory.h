#ifndef DEMO_MATERIAL_FACTORY_H
#define DEMO_MATERIAL_FACTORY_H

#include "resource_factory.h"
#include "resource_handle.h"
#include "resource_manager.h"
#include <maths/colour.h>
#include <nlohmann/json.hpp>
#include <rendering/data/material.h>

class MaterialFactory : public ResourceFactory<Material>
{
public:
    explicit MaterialFactory(std::shared_ptr<ResourceManager> resource_manager)
        : ResourceFactory("assets/materials")
        , resource_manager(resource_manager)
    {
    }

    inline virtual std::shared_ptr<Material> build(const std::string& name) override
    {
        nlohmann::json material_data;

        std::ifstream material_stream(get_full_path(name));
        material_stream >> material_data;

        colour ambient_colour = get_colour(material_data, "ambient_colour");
        colour diffuse_colour = get_colour(material_data, "diffuse_colour");
        colour specular_colour = get_colour(material_data, "specular_colour");

        RenderMode render_mode = render_mode_from_string(material_data["render_mode"]);

        ResourceHandle shader = resource_manager->load<Shader>(material_data["shader"]);

        ResourceHandle diffuse_texture = resource_manager->load<Texture>(material_data["diffuse_texture"]["source"]);
        ResourceHandle specular_texture = resource_manager->load<Texture>(material_data["specular_texture"]["source"]);

        bool is_using_texture = diffuse_texture != ResourceHandle::invalid_handle<Texture>();

        float shininess = material_data["shininess"];

        Material material = Material {
            .ambient_colour = ambient_colour,
            .diffuse_colour = diffuse_colour,
            .specular_colour = specular_colour,

            .diffuse_texture = diffuse_texture,
            .specular_texture = specular_texture,

            .diffuse_texture_properties = DEFAULT_TEXTURE_PROPERTIES,
            .specular_texture_properties = DEFAULT_TEXTURE_PROPERTIES,

            .shader = shader,

            .shininess = shininess,

            .is_using_texture = is_using_texture,

            .render_mode = render_mode,
        };

        return std::make_shared<Material>(material);
    }

private:
    std::shared_ptr<ResourceManager> resource_manager;

    colour get_colour(nlohmann::json material_data, const std::string& colour_name)
    {
        colour colour;
        colour.r = material_data[colour_name]["r"];
        colour.g = material_data[colour_name]["g"];
        colour.b = material_data[colour_name]["b"];
        colour.a = material_data[colour_name]["a"];
        return colour;
    }
};

#endif // DEMO_MATERIAL_FACTORY_H
