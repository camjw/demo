#ifndef DEMO_CUBE_MAP_REPOSITORY_H
#define DEMO_CUBE_MAP_REPOSITORY_H

#include <rendering/cube_map.h>
#include <string>
#include <unordered_map>
class CubeMapRepository
{
public:
    explicit CubeMapRepository();

    std::shared_ptr<CubeMap> get_cube_map(CubeMapID cube_map_id);
    CubeMapID get_cube_map_id(const std::string& cube_map_name);
    CubeMapID create_cube_map(const std::string& cube_map_name, const std::string& cube_map_directory);

    void delete_cube_map(CubeMapID cube_map_id);
    void clear();

private:
    std::unordered_map<std::string, CubeMapID> cube_map_names_to_ids;
    std::unordered_map<CubeMapID, std::shared_ptr<CubeMap>> cube_maps;
    CubeMapID current_cube_map_id = 0;
    std::vector<std::string> get_cube_map_files(const std::string& basicString);
};

#endif //DEMO_CUBE_MAP_REPOSITORY_H
