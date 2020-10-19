#include "cube_map_repository.h"
#include <utils/opengl_helpers.h>

CubeMapRepository::CubeMapRepository()
{
}

std::shared_ptr<CubeMap> CubeMapRepository::get_cube_map(CubeMapID cube_map_id)
{
    assert(cube_maps.find(cube_map_id) != cube_maps.end() && "No such cube_map.");

    return cube_maps[cube_map_id];
}

CubeMapID CubeMapRepository::get_cube_map_id(const std::string& cube_map_name)
{
    assert(cube_map_names_to_ids.find(cube_map_name) != cube_map_names_to_ids.end() && "No such cube_map.");

    return cube_map_names_to_ids[cube_map_name];
}

CubeMapID CubeMapRepository::create_cube_map(const std::string& cube_map_name, const std::string& cube_map_directory)
{
    std::vector<std::string> cube_map_faces = get_cube_map_files(cube_map_directory);
    std::shared_ptr<CubeMap> new_cube_map = std::make_shared<CubeMap>(cube_map_faces);

    cube_map_names_to_ids.insert(std::make_pair(cube_map_name, ++current_cube_map_id));
    cube_maps.insert(std::make_pair(current_cube_map_id, new_cube_map));
    glCheckError();

    return current_cube_map_id;
}

void CubeMapRepository::delete_cube_map(CubeMapID cube_map_id)
{
    assert(cube_maps.find(cube_map_id) != cube_maps.end() && "Removing non-existent cube_map.");

    std::shared_ptr<CubeMap> cube_map_to_delete = cube_maps[cube_map_id];
    cube_map_to_delete->release();
    cube_maps.erase(cube_map_id);
}

void CubeMapRepository::clear()
{
    for (auto cube_map : cube_maps)
    {
        delete_cube_map(cube_map.first);
    }
}
std::vector<std::string> CubeMapRepository::get_cube_map_files(const std::string& cube_map_directory)
{
    std::vector<std::string> output(6, "");

    output[0] = cube_map_directory + "/" + "right.png";
    output[1] = cube_map_directory + "/" + "left.png";
    output[2] = cube_map_directory + "/" + "top.png";
    output[3] = cube_map_directory + "/" + "bottom.png";
    output[4] = cube_map_directory + "/" + "front.png";
    output[5] = cube_map_directory + "/" + "back.png";

    return output;
}
