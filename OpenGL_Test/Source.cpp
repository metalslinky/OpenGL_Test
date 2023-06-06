#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iterator> // std::size

#include "Shader.h"

void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
    glViewport( 0, 0, width, height );
}

void processInput( GLFWwindow* window ) {
    if( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) {
        glfwSetWindowShouldClose( window, true );
    }
}

//GLuint Load2DTexture( int texturePos, const char* pFileName, int colourFormat ) {
//    GLuint texture;
//    glGenTextures( texturePos, &texture );
//    glBindTexture( GL_TEXTURE_2D, texture );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//    int width, height, numberOfChannels;
//    unsigned char* data = stbi_load( pFileName, &width, &height, &numberOfChannels, 0 );
//    if( data ) {
//        glTexImage2D( GL_TEXTURE_2D, 0, colourFormat, width, height, 0, colourFormat, GL_UNSIGNED_BYTE, data );
//        glGenerateMipmap( GL_TEXTURE_2D );
//    } else {
//        std::cout << "Failed to load texture" << std::to_string( texturePos ) << "\n";
//    }
//    stbi_image_free( data );
//    return texture;
//}

int main() {
    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    //glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    // Create GLFW window
    const GLuint HEIGHT{ 800 }, WIDTH{ 600 };
    const char* TITLE{ "LearnOpenGL" };
    GLFWwindow* window = glfwCreateWindow( HEIGHT, WIDTH, TITLE, nullptr, nullptr );
    if( window == nullptr ) {
        std::cout << "Failed to create GLFW window\n";
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    // Initialise GLAD
    if( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) ) {
        std::cout << "Failed to initialise GLAD\n";
        return -1;
    }

    Shader shader( "triangle.vert", "triangle.frag" );

    GLfloat vertices[] = {
        // positions          // colours          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Create VAO, VBO, and EBO
    GLuint vao, vbo, ebo;
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    // Bind VAO
    glBindVertexArray( vao );

    // Bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // Bind EBO
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    // Position attriute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( void* )0 );
    glEnableVertexAttribArray( 0 );
    // Colour attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( void* )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );
    // Texture coord attribute
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( void* )( 6 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );

    // Texture stuff
    GLuint texture1, texture2;
    stbi_set_flip_vertically_on_load( true );
    //texture1 = Load2DTexture( 0, "images/container.jpg", GL_RGB );
    //texture2 = Load2DTexture( 1, "images/awesomeface.png", GL_RGBA );
    glGenTextures( 1, &texture1 );
    glBindTexture( GL_TEXTURE_2D, texture1 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    int width, height, numberOfChannels;
    unsigned char* data = stbi_load( "images/container.jpg", &width, &height, &numberOfChannels, 0 );
    if( data ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    } else {
        std::cout << "Failed to load texture1\n";
    }
    stbi_image_free( data );

    glGenTextures( 1, &texture2 );
    glBindTexture( GL_TEXTURE_2D, texture2 );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    data = stbi_load( "images/awesomeface.png", &width, &height, &numberOfChannels, 0 );
    if( data ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    } else {
        std::cout << "Failed to load texture2\n";
    }
    stbi_image_free( data );

    shader.Use();
    shader.SetInt( "texture1", 0 );
    shader.SetInt( "texture2", 1 );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture1 );
    glActiveTexture( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_2D, texture2 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    while( !glfwWindowShouldClose( window ) ) {
        // Input
        processInput( window );

        // Render
        glClearColor( 0.1f, 0.3f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glm::mat4 trans = glm::mat4( 1.0f );
        float time = glfwGetTime();
        trans = glm::rotate( trans, time, glm::vec3( 0.0f, 0.0f, 1.0f ) );
        trans = glm::translate( trans, glm::vec3( 0.7f, 0.0f, 0.0f ) );
        trans = glm::rotate( trans, time, glm::vec3( 0.0f, 0.0f, -1.0f ) );
        trans = glm::scale( trans, glm::vec3( 0.5f, 0.5f, 0.5f ) );

        shader.Use();

        GLuint transformLoc = glGetUniformLocation( shader.GetProgramID(), "transform" );
        glUniformMatrix4fv( transformLoc, 1, GL_FALSE, glm::value_ptr( trans ) );

        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, std::size( indices ), GL_UNSIGNED_INT, 0 );

        trans = glm::translate( glm::mat4( 1.0f ), glm::vec3( -0.5f, 0.5f, 0.0f ) );
        transformLoc = glGetUniformLocation( shader.GetProgramID(), "transform" );
        glUniformMatrix4fv( transformLoc, 1, GL_FALSE, glm::value_ptr( trans ) );
        glDrawElements( GL_TRIANGLES, std::size( indices ), GL_UNSIGNED_INT, 0 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteBuffers( 1, &vao );
    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &ebo );
    glDeleteProgram( shader.GetProgramID() );

    glfwTerminate();
    return 0;
}