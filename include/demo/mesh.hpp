#ifndef DEMO_MESH_HPP
#define DEMO_MESH_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <demo/shader.hpp>
#include <demo/texture.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec3 tangent;
};

class Mesh 
{
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures): vertices(vertices), indices(indices), textures(textures)
    {
        setupMesh();
    }

    void Draw(Shader shader) 
    {
        unsigned int diffuse_counter  = 1;
        unsigned int specular_counter = 1;
        unsigned int normal_counter   = 1;
        unsigned int height_counter   = 1;

        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            TextureType texture_type = textures[i].type;
            if(texture_type == TextureType::NONE)
            {
                continue;
            }

            switch(texture_type)
            {
                case (TextureType::DIFFUSE):
                {
                    number = std::to_string(diffuse_counter++);
                    break;
                }
                case (TextureType::SPECULAR):
                {
                    number = std::to_string(specular_counter++);
                    break;
                }
                case (TextureType::NORMAL):
                {
                    number = std::to_string(normal_counter++);
                    break;
                }
                case (TextureType::HEIGHT):
                {
                    number = std::to_string(height_counter++);
                    break;
                }
            }

            glUniform1i(glGetUniformLocation(shader.ID, (texture_type.to_string() + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
    }

private:
    unsigned int VBO, EBO;

    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);	
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);	
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)std::offsetof(Vertex, Normal));
        // vertex uvs
        glEnableVertexAttribArray(2);	
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)std::offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};

#endif
