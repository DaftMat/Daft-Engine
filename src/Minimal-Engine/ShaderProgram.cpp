//
// Created by mathis on 09/05/2020.
//

#include "ShaderProgram.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram( const char* vertexPath, const char* fragmentPath ) {
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    fShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

    try
    {
        /// Open files
        vShaderFile.open( vertexPath );
        fShaderFile.open( fragmentPath );
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        /// close files
        vShaderFile.close();
        fShaderFile.close();
    }
    catch ( std::ifstream::failure& e )
    { std::cerr << "ERROR:SHADER:FILE_NOT_SUCCESSFULLY_READ" << std::endl; }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    /// Vertex
    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vShaderCode, nullptr );
    glCompileShader( vertex );
    checkCompileError( vertex, "VERTEX" );
    /// Fragment
    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fShaderCode, nullptr );
    glCompileShader( fragment );
    checkCompileError( fragment, "FRAGMENT" );
    /// Program
    m_id = glCreateProgram();
    glAttachShader( m_id, vertex );
    glAttachShader( m_id, fragment );
    glLinkProgram( m_id );
    checkLinkError( m_id );
    /// Release shader
    glDeleteShader( vertex );
    glDeleteShader( fragment );
}

void ShaderProgram::setBool( const std::string& name, bool value ) const {
    glUniform1i( glGetUniformLocation( m_id, name.c_str() ), (GLuint)value );
}

void ShaderProgram::setInt( const std::string& name, int value ) const {
    glUniform1i( glGetUniformLocation( m_id, name.c_str() ), value );
}

void ShaderProgram::setFloat( const std::string& name, float value ) const {
    glUniform1f( glGetUniformLocation( m_id, name.c_str() ), value );
}

void ShaderProgram::setVec2( const std::string& name, const glm::vec2& value ) const {
    glUniform2fv( glGetUniformLocation( m_id, name.c_str() ), 1, glm::value_ptr( value ) );
}

void ShaderProgram::setVec3( const std::string& name, const glm::vec3& value ) const {
    glUniform3fv( glGetUniformLocation( m_id, name.c_str() ), 1, glm::value_ptr( value ) );
}

void ShaderProgram::setVec4( const std::string& name, const glm::vec4& value ) const {
    glUniform4fv( glGetUniformLocation( m_id, name.c_str() ), 1, glm::value_ptr( value ) );
}

void ShaderProgram::setMat2( const std::string& name, const glm::mat2& value ) const {
    glUniformMatrix2fv(
        glGetUniformLocation( m_id, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}

void ShaderProgram::setMat3( const std::string& name, const glm::mat3& value ) const {
    glUniformMatrix3fv(
        glGetUniformLocation( m_id, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}

void ShaderProgram::setMat4( const std::string& name, const glm::mat4& value ) const {
    glUniformMatrix4fv(
        glGetUniformLocation( m_id, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
}

void ShaderProgram::checkCompileError( GLuint shader, const std::string& type ) {
    int success;
    char infoLog[1024];
    glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( shader, 1024, NULL, infoLog );
        std::cerr << "ERROR:SHADER_COMPILATION of type : " << type << "\n" << infoLog << std::endl;
    }
}

void ShaderProgram::checkLinkError( GLuint program ) {
    int success;
    char infoLog[1024];
    glGetProgramiv( program, GL_LINK_STATUS, &success );
    if ( !success )
    {
        glGetProgramInfoLog( program, 1024, NULL, infoLog );
        std::cerr << "ERROR:PROGRAM_LINKING\n" << infoLog << std::endl;
    }
}