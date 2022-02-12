#ifndef LEARNOPENGL_MODEL_H
#define LEARNOPENGL_MODEL_H

#include "shader.h"

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb/stb_image.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <string>
#include <vector>

namespace HelloModel
{

#define MAX_BONE_INFLUENCE 4

    struct Vertex
    {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    struct Texture
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);

        void draw(Shader &shader);

    public:
        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<Texture> textures_;
        unsigned int VAO_;

    private:
        void set_up_mesh();

    private:
        unsigned int VBO_, EBO_;
    };

    class Model
    {
    public:
        explicit Model(const std::string &path, bool gamma = false);

        void draw();

    public:
        Shader *shader_;

    public:
        std::vector<Mesh>    meshes_;
        std::vector<Texture> textures_loaded_;
        bool gamma_correction_;

    private:
        bool load_model(const std::string &name);

        void process_node(aiNode *node, const aiScene *scene);

        Mesh process_mesh(aiMesh *mesh, const aiScene *scene);

    private:


    };
}

#endif //LEARNOPENGL_MODEL_H
