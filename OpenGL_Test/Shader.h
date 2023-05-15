#pragma once
#include <glad/glad.h>

#include <string> // std::string
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <iostream> // std::cout

class Shader {
public:
    Shader( const char* pVertexPath, const char* pFragmentPath );

    void Use();

    GLuint GetProgramID();

    void SetBool( const std::string& name, GLboolean value ) const;
    void SetInt( const std::string& name, GLint value ) const;
    void SetFloat( const std::string& name, GLfloat value ) const;

private:
    GLuint CompileVertexShader( const char* pVertexShaderCode );
    GLuint CompileFragmentShader( const char* pFragmentShaderCode );
    void CreateShaderProgram( GLuint vertexShader, GLuint fragmentShader );

    GLuint mProgramID;
};
