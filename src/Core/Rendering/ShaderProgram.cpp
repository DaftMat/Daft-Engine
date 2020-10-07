//
// Created by mathis on 09/05/2020.
//

#include "ShaderProgram.hpp"

#include <Core/Utils/IO.hpp>
#include <Core/Utils/Logger.hpp>
#include <iostream>

namespace daft::core {
ShaderProgram::ShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) : m_isValid{true} {
    std::string vShaderCodeStr = IO::getStringFromFile(vertexPath);
    std::string fShaderCodeStr = IO::getStringFromFile(fragmentPath);
    const char *vShaderCode = vShaderCodeStr.c_str();
    const char *fShaderCode = fShaderCodeStr.c_str();

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

    std::stringstream ss;
    ss << "ShadeProgram created. ID: " << m_id << ".";
    core::Logger::info(std::move(ss));
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
    std::stringstream ss;
    ss << "ShaderProgram of ID: " << m_id << " deleted.";
    core::Logger::info(std::move(ss));
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
        char *infoLog;
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::stringstream ss;
        ss << "SHADER_COMPILATION ERROR of type : " << type << "\n\t" << infoLog;
        core::Logger::error(std::move(ss));
        exit(-1);
    }
}

void ShaderProgram::checkLinkError(GLuint program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char *infoLog;
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::stringstream ss;
        ss << "PROGRAM_LINKING ERROR \n\t" << infoLog;
        core::Logger::error(std::move(ss));
        exit(-1);
    }
}
}  // namespace daft::core