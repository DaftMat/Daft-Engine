//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <API.hpp>
#include <Core/NonCopyable.hpp>
#include <Core/OpenGL.hpp>
#include <string>

/** Shader object base class.
 *
 */
class ENGINE_API ShaderProgram : public ProjName::Core::NonCopyable {
   public:
    /**
     * Constructor.
     * @param vertexPath - file path of the vertex shader.
     * @param fragmentPath - file path of the fragment shader.
     */
    ShaderProgram(const char *vertexPath, const char *fragmentPath);

    /**
     * Destructor.
     * calls glDeleteProgram.
     */
    ~ShaderProgram() { glDeleteProgram(m_id); }

    /**
     * Move constructor.
     * @param other - Shader to be moved into this.
     */
    ShaderProgram(ShaderProgram &&other) = default;

    /**
     * Mose assignment operator.
     * @param other - Shader to be moved into this.
     * @return this shader after the other is moved.
     */
    ShaderProgram &operator=(ShaderProgram &&other) = default;

    /**
     * Activates the shaders.
     * call OpenGL's glUseShader().
     */
    void use() const { glUseProgram(m_id); }

    /**
     * Desactivates the shaders.
     */
    void stop() const { glUseProgram(0); }

    /**
     * ID getter.
     * @return shader program's OpenGL's ID.
     */
    [[nodiscard]] GLuint id() const { return m_id; }

    /**
     * Boolean uniform setter.
     * @param name - name of the uniform variable.
     * @param value - boolean value to assign.
     */
    void setBool(const std::string &name, bool value) const;

    /**
     * Integer uniform setter.
     * @param name - name of the uniform variable.
     * @param value - integer value to assign.
     */
    void setInt(const std::string &name, int value) const;

    /**
     * Float uniform setter.
     * @param name - name of the uniform variable.
     * @param value - float value to assign.
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * 2D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector2 value to assign.
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    /**
     * 3D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector3 value to assign.
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const;

    /**
     * 4D Vector uniform setter.
     * @param name - name of the uniform variable.
     * @param value - vector4 to assign.
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    /**
     * 2D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix2 to assign.
     */
    void setMat2(const std::string &name, const glm::mat2 &value) const;

    /**
     * 3D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix3 to assign.
     */
    void setMat3(const std::string &name, const glm::mat3 &value) const;

    /**
     * 4D Matrix uniform setter.
     * @param name - name of the uniform variable.
     * @param value - matrix4 to assign.
     */
    void setMat4(const std::string &name, const glm::mat4 &value) const;

   private:
    void checkCompileError(GLuint shader, const std::string &type);
    void checkLinkError(GLuint program);

    GLuint m_id;
};
