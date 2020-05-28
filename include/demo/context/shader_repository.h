#ifndef DEMO_SHADER_REPOSITORY_H
#define DEMO_SHADER_REPOSITORY_H

#include <demo/rendering/shader.h>

#include <unordered_map>
#include <demo/templates/action.h>

struct PairHash
{
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const
    {
        auto hash_1 = std::hash<T1>{}(p.first);
        auto hash_2 = std::hash<T2>{}(p.second);
        return hash_1 ^ hash_2;
    }
};

class ShaderRepository
{
public:
    std::shared_ptr<Shader> get_shader(ShaderID shader_id);
    ShaderID create_shader();
    ShaderID create_shader(const std::string& vertex_filename, const std::string& fragment_filename);

    void delete_shader(ShaderID mesh_id);
    void clear();
    void for_all(Action<Shader>* action);

private:
    std::unordered_map<std::pair<std::string, std::string>, ShaderID, PairHash> filename_to_shader_id;
    std::unordered_map<ShaderID, std::shared_ptr<Shader>> shaders;
    ShaderID current_shader_id = 0;
};

#endif //DEMO_SHADER_REPOSITORY_H