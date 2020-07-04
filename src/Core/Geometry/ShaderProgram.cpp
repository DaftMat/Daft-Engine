//
// Created by mathis on 09/05/2020.
//

#include "ShaderProgram.hpp"

#include <Core/Utils/Log.hpp>
#include <fstream>
#include <iostream>

namespace stardust::core::geometry {
ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragmentPath) : m_isValid{true} {
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        /// Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        /// close files
        vShaderFile.close();
        fShaderFile.close();
    } catch (std::ifstream::failure &e) {
        ENGINE_ERROR("ERROR:SHADER:FILE_NOT_SUCCESSFULLY_READ");
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    /// Vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileError(vertex, "VERTEX");
    /// Fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileError(fragment, "FRAGMENT");
    /// Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    checkLinkError(m_id);
    /// Release shader
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderProgram::ShaderProgram(ShaderProgram &&other) noexcept : m_id{other.m_id}, m_isValid{other.m_isValid} {
    other.m_isValid = false;
}

ShaderProgram &ShaderProgram::operator=(ShaderProgram &&other) noexcept {
    m_id = other.m_id;
    m_isValid = other.m_isValid;
    other.m_isValid = false;
    return *this;
}

ShaderProgram::~ShaderProgram() noexcept {
    if (!m_isValid) return;
    glDeleteProgram(m_id);
}

void ShaderProgram::use() const noexcept {
    if (!m_isValid) return;
    glUseProgram(m_id);
}

void ShaderProgram::stop() const noexcept { glUseProgram(0); }

void ShaderProgram::setBool(const std::string &name, bool value) const noexcept {
    if (!m_isValid) return;
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (GLuint)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const noexcept {
    if (!m_isValid) return;
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const noexcept {
    if (!m_isValid) return;
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setVec2(const std::string &name, const glm::vec2 &value) const noexcept {
    if (!m_isValid) return;
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value) const noexcept {
    if (!m_isValid) return;
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value) const noexcept {
    if (!m_isValid) return;
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setMat2(const std::string &name, const glm::mat2 &value) const noexcept {
    if (!m_isValid) return;
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setMat3(const std::string &name, const glm::mat3 &value) const noexcept {
    if (!m_isValid) return;
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &value) const noexcept {
    if (!m_isValid) return;
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::checkCompileError(GLuint shader, const std::string &type) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char *infoLog = nullptr;
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        ENGINE_ERROR("ERROR:SHADER_COMPILATION of type : {0}{1}{2}", type, "\n", infoLog);
    }
}

void ShaderProgram::checkLinkError(GLuint program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char *infoLog = nullptr;
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        ENGINE_ERROR("ERROR:PROGRAM_LINKING\n{0}", infoLog);
    }
}
}  // namespace stardust::core::geometry