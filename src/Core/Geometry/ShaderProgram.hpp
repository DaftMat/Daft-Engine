//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <string>

namespace daft::core::geometry {
/**
 * Shader object base class.
 */
class ENGINE_API ShaderProgram : public utils::NonCopyable {
   public:
    /**
     * Constructor.
     * @param vertexPath - file path of the vertex shader.
     * @param fragmentPath - file path of the fragment shader.
     */
    ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

    /**
     * Destructor.
     * calls glDeleteProgram.
     */
    ~ShaderProgram() noexcept;

    /**
     * Move constructor.
     * @param other - Shader to be moved into this.
     */
    inline ShaderProgram(ShaderProgram &&other) noexcept;

    /**
     * Move assignment operator.
     * @param other - Shader to be moved into this.
     * @return this shader after the other is moved.
     */
    inline ShaderProgram &operator=(ShaderProgram &&other) noexcept;

    /**
     * Activates the shaders.
     * call OpenGL's glUseShader().
     */
    void use() const noexcept;

    /**
     * Deactivates the shaders.
     */
    void stop() const noexcept;

    /**
     * ID getter.
     * @return shader program's OpenGL's ID.
     */
    [[nodiscard]] GLuint id() const noexcept { return m_id; }

    /**
     * Boolean uniform setter.
     * @param name - name of the uniform variable.
     * @param value - boolean value to assign.
     */
    void setBool(const std::string &name, bool value) const noexcept;

    /**
     * Integer uniform setter.
     * @param name - name of the uniform variable.
     * @param value - integer value to assign.
     */
    void setInt(const std::string &name, int value) const noexcept;

    /**
     * Float uniform setter.
     * @param name - name of the uniform variable.
     * @param value - float value to assign.
     */
    void setFloat(const std::string &name, float value) const noexcept;

    /**
     * 2D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector2 value to assign.
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const noexcept;

    /**
     * 3D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector3 value to assign.
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const noexcept;

    /**
     * 4D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector4 to assign.
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const noexcept;

    /**
     * 2D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix2 to assign.
     */
    void setMat2(const std::string &name, const glm::mat2 &value) const noexcept;

    /**
     * 3D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix3 to assign.
     */
    void setMat3(const std::string &name, const glm::mat3 &value) const noexcept;

    /**
     * 4D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix4 to assign.
     */
    void setMat4(const std::string &name, const glm::mat4 &value) const noexcept;

   private:
    static void checkCompileError(GLuint shader, const std::string &type);
    static void checkLinkError(GLuint program);

    GLuint m_id;
    bool m_isValid;
};
}  // namespace daft::core::geometry