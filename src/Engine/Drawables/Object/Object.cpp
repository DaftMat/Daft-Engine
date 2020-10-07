//
// Created by mathis on 08/07/2020.
//
#include "Object.hpp"

#include <Core/Materials/Material.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {

int Object::m_nrObject{0};

Object::Object(Composite *parent, std::string name) : Drawable(parent, std::move_if_noexcept(name)) {}

Object::Object(std::string filepath, Composite *parent, std::string name) : Drawable(parent, std::move(name)) {
    loadFromFile(std::move(filepath));
}

Object::~Object() noexcept { Object::reset(); }

void Object::render(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        if (mo.hasMaterial()) mo.material().loadToShader(shader);
        mo.render();
        mo.unbind();
    }
}

void Object::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    if (selected()) shader.setVec3("color", {1.f, 1.f, 0.f});
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render();
        mo.unbind();
    }
    if (selected()) shader.setVec3("color", glm::vec3{0.f});
}

void Object::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Object::reset() {
    Drawable::reset();
    m_meshObjects.clear();
}

void Object::subdivide() {
    /// in the future : half-edges
}

void Object::loadFromFile(std::string path) {
    std::string filepath = std::move(path);
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::stringstream ss;
        ss << "could not load this file into assimp." << importer.GetErrorString();
        core::Logger::error(std::move(ss));
    }
    m_directory = filepath.substr(0, filepath.find_last_of('/')) + "/";

    processMaterials(scene);
    processNode(scene->mRootNode, scene);

    for (size_t i = 0; i < m_constructedMaterial.size(); ++i) {
        m_meshObjects.emplace_back(std::vector<core::Mesh>{}, std::move(m_constructedMaterial[i]));
        for (auto &meshInfo : m_constructedMeshes) {
            if (meshInfo.matIndex == i) {
                m_meshObjects[m_meshObjects.size() - 1].meshes().emplace_back(std::move(meshInfo.mesh));
            }
        }
    }
    m_constructedMeshes.clear();
    m_constructedMaterial.clear();
    m_loadedTextures.clear();
}

void Object::processNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }
    for (size_t i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

void Object::processMesh(aiMesh *mesh, const aiScene *scene) {
    /// Mesh
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> tangents;
    std::vector<GLuint> indices;
    /// Geometry
    for (size_t i = 0; i < mesh->mNumVertices; ++i) {
        auto v = mesh->mVertices[i];
        positions.emplace_back(v.x, v.y, v.z);

        if (mesh->HasNormals()) {
            auto n = mesh->mNormals[i];
            normals.emplace_back(n.x, n.y, n.z);
        }

        if (mesh->mTextureCoords[0]) {
            auto tex = mesh->mTextureCoords[0][i];
            texCoords.emplace_back(tex.x, tex.y);

            auto t = mesh->mTangents[i];
            tangents.emplace_back(t.x, t.y, t.z);
        }
    }
    /// Topology
    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    core::AttribManager am;
    am.addAttrib(positions);
    am.addAttrib(normals);
    am.addAttrib(texCoords);
    am.addAttrib(tangents);
    am.indices() = indices;
    m_constructedMeshes.emplace_back(am, mesh->mMaterialIndex);
}

void Object::processMaterials(const aiScene *scene) {
    for (size_t i = 0; i < scene->mNumMaterials; ++i) {
        m_constructedMaterial.push_back(std::make_shared<core::Material>());
        loadMaterialTextures(scene->mMaterials[i], i);
    }
}

void Object::loadMaterialTextures(aiMaterial *mat, size_t index) {
    std::vector<aiTextureType> types{aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_HEIGHT,
                                     aiTextureType_REFLECTION};

    for (auto type : types) {
        for (size_t i = 0; i < mat->GetTextureCount(type); ++i) {
            aiString str;
            mat->GetTexture(type, i, &str);
            auto skipIt = std::find(m_loadedTextures.begin(), m_loadedTextures.end(), std::string(str.C_Str()));
            bool skip = skipIt != m_loadedTextures.end();
            m_loadedTextures.emplace_back(str.C_Str());

            if (!skip) {
                std::string name;
                core::Texture::Type type1;
                switch (type) {
                    case aiTextureType_DIFFUSE: {
                        int texIndex = m_constructedMaterial[index]->getSetting<int>("nrAlbedoTex");
                        name = "albedoTex[" + std::to_string(texIndex++) + "]";
                        type1 = core::Texture::Type::ALBEDO;
                        m_constructedMaterial[index]->setSetting("nrAlbedoTex", texIndex);
                        break;
                    }
                    case aiTextureType_SPECULAR: {
                        int texIndex = m_constructedMaterial[index]->getSetting<int>("nrSpecularTex");
                        name = "specularTex[" + std::to_string(texIndex++) + "]";
                        type1 = core::Texture::Type::SPECULAR;
                        m_constructedMaterial[index]->setSetting("nrSpecularTex", texIndex);
                        break;
                    }
                    case aiTextureType_HEIGHT: {
                        int texIndex = m_constructedMaterial[index]->getSetting<int>("nrNormalTex");
                        name = "normalTex[" + std::to_string(texIndex++) + "]";
                        type1 = core::Texture::Type::NORMAL;
                        m_constructedMaterial[index]->setSetting("nrNormalTex", texIndex);
                        break;
                    }
                    case aiTextureType_REFLECTION: {
                        int texIndex = m_constructedMaterial[index]->getSetting<int>("nrReflectionTex");
                        name = "reflectionTex[" + std::to_string(texIndex++) + "]";
                        type1 = core::Texture::Type::REFLECTION;
                        m_constructedMaterial[index]->setSetting("nrReflectionTex", texIndex);
                    }
                    default:
                        /// impossible
                        break;
                }
                m_constructedMaterial[index]->addTexture(
                    core::Texture{name, type1, m_directory + std::string(str.C_Str())});
            }
        }
    }
}

}  // namespace daft::engine