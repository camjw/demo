#include "cube_map_factory.h"

std::vector<std::string> CubeMapFactory::get_cube_map_files(const std::string& cube_map_directory) const
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