#pragma once
// GLAD
#include <glad/glad.h>

// GLM
#include <glm/glm.hpp>

#include <string> // std::string

class Shader {
public:
    Shader( const char* pVertexPath, const char* pFragmentPath );

    void Use();

    GLuint GetProgramID();

    void SetBool( const std::string& name, GLboolean value ) const;
    void SetInt( const std::string& name, GLint value ) const;
    void SetFloat( const std::string& name, GLfloat value ) const;

    void SetVec2( const std::string& name, const glm::vec2& value ) const;
    void SetVec2( const std::string& name, float x, float y ) const;
    void SetVec3( const std::string& name, const glm::vec3& value ) const;
    void SetVec3( const std::string& name, float x, float y, float z ) const;
    void SetVec4( const std::string& name, const glm::vec4& value ) const;
    void SetVec4( const std::string& name, float x, float y, float z, float w ) const;

    void SetMat2( const std::string& name, const glm::mat2& mat ) const;
    void SetMat3( const std::string& name, const glm::mat3& mat ) const;
    void SetMat4( const std::string& name, const glm::mat4& mat ) const;

private:
    GLuint CompileVertexShader( const char* pVertexShaderCode );
    GLuint CompileFragmentShader( const char* pFragmentShaderCode );
    void CreateShaderProgram( GLuint vertexShader, GLuint fragmentShader );

    GLuint mProgramID;
};
