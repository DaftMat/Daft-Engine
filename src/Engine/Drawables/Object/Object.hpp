//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <Engine/Drawables/MeshObject.hpp>
#include <assimp/Importer.hpp>

namespace daft::engine {
/**
 * Base 3D object.
 */
class ENGINE_API Object : public Drawable {
   public:
    /**
     * Standard constructor.
     * @param parent - parent Composite .
     * @param name - name of the object.
     */
    explicit Object(Composite *parent = nullptr, std::string name = "Object" + std::to_string(m_nrObject++));

    /**
     * File constructor.
     * @param filepath - path of an obj file.
     * @param parent - parent Composite .
     * @param name - name of the object.
     */
    explicit Object(std::string filepath, Composite *parent = nullptr,
                    std::string name = "Object" + std::to_string(m_nrObject++));

    /**
     * Destructor.
     */
    ~Object() noexcept override;

    /**
     * Default move constructor.
     */
    Object(Object &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return reference to this.
     */
    Object &operator=(Object &&) noexcept = default;

    /**
     * Renders the mesh objects.
     */
    void render(const core::ShaderProgram &shader) override;

    /**
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Resets the object.
     */
    void reset() override;

    /**
     * Tests if this is a Composite .
     * @return false.
     */
    [[nodiscard]] bool isComposite() const override { return false; }

    /**
     * Tests if this is an Object .
     * @return true.
     */
    [[nodiscard]] bool isObject() const override { return true; }

    /**
     * Tests if this is a Light .
     * @return false.
     */
    [[nodiscard]] bool isLight() const override { return false; }

    /**
     * Gets the type of drawable.
     * @return Type::None .
     */
    [[nodiscard]] Type getType() const override { return Type::None; }

   protected:
    std::vector<MeshObject> m_meshObjects;

   private:
    struct MeshInfo {
        MeshInfo(core::AttribManager am, size_t i) : mesh{std::move(am)}, matIndex{i} {}

        core::Mesh mesh;
        size_t matIndex;
    };

    void loadFromFile(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);
    void processMaterials(const aiScene *scene);
    void loadMaterialTextures(aiMaterial *mat, size_t index);

    std::vector<MeshInfo> m_constructedMeshes{};
    std::vector<std::shared_ptr<core::Material>> m_constructedMaterial{};
    std::vector<std::string> m_loadedTextures{};

    std::string m_directory;

    static int m_nrObject;
};
}  // namespace daft::engine