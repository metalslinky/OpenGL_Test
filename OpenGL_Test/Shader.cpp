#include "Shader.h"

#include <fstream> // std::ifstream
#include <iostream> // std::cout
#include <sstream> // std::stringstream

Shader::Shader( const char* pVertexPath, const char* pFragmentPath ) {
    // Read shader files
    std::string vertexCode, fragmentCode;
    std::ifstream vertexShaderFile, fragmentShaderFile;
    vertexShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    fragmentShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    try {
        vertexShaderFile.open( pVertexPath );
        fragmentShaderFile.open( pFragmentPath );

        std::stringstream vertexStringStream, fragmentStringStream;
        vertexStringStream << vertexShaderFile.rdbuf(); // should i use rdbuf, read, or something else?
        fragmentStringStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexStringStream.str();
        fragmentCode = fragmentStringStream.str();
    } catch( std::ifstream::failure e ) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n";
    }
    const char* pVertexShaderCode = vertexCode.c_str();
    const char* pFragmentShaderCode = fragmentCode.c_str();

    // Compile shaders
    GLuint vertexShader = CompileVertexShader( pVertexShaderCode );
    GLuint fragmentShader = CompileFragmentShader( pFragmentShaderCode );

    // Create shader program
    CreateShaderProgram( vertexShader, fragmentShader );
}

GLuint Shader::GetProgramID() {
    return mProgramID;
}

void Shader::Use() {
    glUseProgram( mProgramID );
}

void Shader::SetBool( const std::string& name, GLboolean value ) const {
    glUniform1i( glGetUniformLocation( mProgramID, name.c_str() ), value );
}
void Shader::SetInt( const std::string& name, GLint value ) const {
    glUniform1i( glGetUniformLocation( mProgramID, name.c_str() ), value );
}
void Shader::SetFloat( const std::string& name, GLfloat value ) const {
    glUniform1f( glGetUniformLocation( mProgramID, name.c_str() ), value );
}

// GLM vec
void Shader::SetVec2( const std::string& name, const glm::vec2& value ) const {
    glUniform2fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, &value[ 0 ] );
}
void Shader::SetVec2( const std::string& name, float x, float y ) const {
    glUniform2f( glGetUniformLocation( mProgramID, name.c_str() ), x, y );
}
void Shader::SetVec3( const std::string& name, const glm::vec3& value ) const {
    glUniform3fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, &value[ 0 ] );
}
void Shader::SetVec3( const std::string& name, float x, float y, float z ) const {
    glUniform3f( glGetUniformLocation( mProgramID, name.c_str() ), x, y, z );
}
void Shader::SetVec4( const std::string& name, const glm::vec4& value ) const {
    glUniform4fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, &value[ 0 ] );
}
void Shader::SetVec4( const std::string& name, float x, float y, float z, float w ) const {
    glUniform4f( glGetUniformLocation( mProgramID, name.c_str() ), x, y, z, w );
}

// GLM mat
void Shader::SetMat2( const std::string& name, const glm::mat2& mat ) const {
    glUniformMatrix2fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
}
void Shader::SetMat3( const std::string& name, const glm::mat3& mat ) const {
    glUniformMatrix3fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
}
void Shader::SetMat4( const std::string& name, const glm::mat4& mat ) const {
    glUniformMatrix4fv( glGetUniformLocation( mProgramID, name.c_str() ), 1, GL_FALSE, &mat[ 0 ][ 0 ] );
}

GLuint Shader::CompileVertexShader( const char* pVertexShaderCode ) {
    GLuint vertexShader;
    GLint success;
    const unsigned int INFO_LOG_SIZE{ 512u };
    char infoLog[ INFO_LOG_SIZE ];

    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &pVertexShaderCode, nullptr );
    glCompileShader( vertexShader );
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if( !success ) {
        glGetShaderInfoLog( vertexShader, INFO_LOG_SIZE, nullptr, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
    }
    return vertexShader;
}

GLuint Shader::CompileFragmentShader( const char* pFragmentShaderCode ) {
    GLuint fragmentShader;
    GLint success;
    const unsigned int INFO_LOG_SIZE{ 512u };
    char infoLog[ INFO_LOG_SIZE ];

    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &pFragmentShaderCode, nullptr );
    glCompileShader( fragmentShader );
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if( !success ) {
        glGetShaderInfoLog( fragmentShader, INFO_LOG_SIZE, nullptr, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
    }
    return fragmentShader;
}

void Shader::CreateShaderProgram( GLuint vertexShader, GLuint fragmentShader ) {

    mProgramID = glCreateProgram();

    GLint success;
    const unsigned int INFO_LOG_SIZE{ 512u };
    char infoLog[ INFO_LOG_SIZE ];

    glAttachShader( mProgramID, vertexShader );
    glAttachShader( mProgramID, fragmentShader );
    glLinkProgram( mProgramID );
    glGetProgramiv( mProgramID, GL_LINK_STATUS, &success );
    if( !success ) {
        glGetProgramInfoLog( mProgramID, INFO_LOG_SIZE, nullptr, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
    }

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
}
