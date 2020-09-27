#include "material_repository.h"

std::shared_ptr<Material> MaterialRepository::get_material(MaterialID material_id)
{
    assert(materials.find(material_id) != materials.end() && "No such material.");

    return materials[material_id];
}

std::shared_ptr<Material> MaterialRepository::get_material(const std::string& material_name)
{
    assert(material_names_to_ids.find(material_name) != material_names_to_ids.end() && "No such material.");

    return materials[material_names_to_ids[material_name]];
}

MaterialID MaterialRepository::get_material_id(const std::string & material_name)
{
    assert(material_names_to_ids.find(material_name) != material_names_to_ids.end() && "No such material.");

    return material_names_to_ids[material_name];
}

MaterialID MaterialRepository::insert_material(const Material material, const std::string& material_name)
{
    std::shared_ptr<Material> new_material = std::make_shared<Material>(material);

    material_names_to_ids.insert(std::make_pair(material_name, ++current_material_id));
    materials.insert(std::make_pair(current_material_id, new_material));

    return current_material_id;
}

void MaterialRepository::delete_material(MaterialID material_id)
{
    assert(materials.find(material_id) != materials.end() && "Removing non-existent material.");

    std::shared_ptr<Material> material_to_delete = materials[material_id];
    materials.erase(material_id);
}

void MaterialRepository::clear()
{
    for (const auto& material : materials)
    {
        delete_material(material.first);
    }
}
