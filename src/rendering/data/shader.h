#ifndef DEMO_SHADER_HPP
#define DEMO_SHADER_HPP

#include <utils/opengl_include.h>
#include <glm/glm.hpp>

#include <ecs/world.h>
#include <fstream>
#include <maths/float3.h>
#include <maths/float4.h>
#include <sstream>
#include <string>
#include <utility>

// TODO: refactor so this doesn't use streams or strings
class Shader
{
public:
    Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
    void destroy() const;

    GLuint id() const
    {
        return id_;
    }

    void bind() const
    {
        glUseProgram(id_);
    }

    void set_bool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
    }

    void set_int(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
    }

    void set_float(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    }

    void set_float2(const std::string& name, const float2& value) const
    {
        glUniform2fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
    }

    void set_float2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(id_, name.c_str()), x, y);
    }

    void set_float3(const std::string& name, const float3& value) const
    {
        glUniform3fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
    }

    void set_float3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(id_, name.c_str()), x, y, z);
    }

    void set_float4(const std::string& name, const float4& value) const
    {
        glUniform4fv(glGetUniformLocation(id_, name.c_str()), 1, &value[0]);
    }

    void set_float4(const std::string& name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(id_, name.c_str()), x, y, z, w);
    }

    void set_mat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void set_mat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    GLuint id_;

    static void check_compile_errors(GLuint shader, const std::string& type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n", type.c_str(), infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n", type.c_str(), infoLog);
            }
        }
    }
};

#endif
