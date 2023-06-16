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

#include <iostream> // std::cout
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
    const GLuint WIDTH{ 800 }, HEIGHT{ 600 };
    const char* TITLE{ "LearnOpenGL" };
    GLFWwindow* window = glfwCreateWindow( WIDTH, HEIGHT, TITLE, nullptr, nullptr );
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

    glEnable( GL_DEPTH_TEST );

    Shader shader( "triangle.vert", "triangle.frag" );

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    GLuint indices[] = {
         0,  1,  3,  2,     2,4,
         4,  5,  7,  6,     6,8,
         8,  9, 11, 10,     10,12,
        12, 13, 15, 14,     14,16,
        16, 17, 19, 18,     18,20,
        20, 21, 23, 22
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f ),
        glm::vec3( 2.0f,  5.0f, -15.0f ),
        glm::vec3( -1.5f, -2.2f, -2.5f ),
        glm::vec3( -3.8f, -2.0f, -12.3f ),
        glm::vec3( 2.4f, -0.4f, -3.5f ),
        glm::vec3( -1.7f,  3.0f, -7.5f ),
        glm::vec3( 1.3f, -2.0f, -2.5f ),
        glm::vec3( 1.5f,  2.0f, -2.5f ),
        glm::vec3( 1.5f,  0.2f, -1.5f ),
        glm::vec3( -1.3f,  1.0f, -1.5f )
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
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( void* )0 );
    glEnableVertexAttribArray( 0 );
    // Texture coord attribute
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( void* )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );

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

    // Projection matrix
    const GLfloat NEAR_CLIP = 0.1f;
    const GLfloat FAR_CLIP = 100.0f;
    //glm::mat4 projection = glm::ortho( 0.0f, static_cast< GLfloat >( WIDTH ), 0.0f, static_cast< GLfloat >( HEIGHT ), NEAR_CLIP, FAR_CLIP );
    constexpr GLfloat FOV = glm::radians( 45.0f );
    const GLfloat ASPECT_RATIO = static_cast< GLfloat >( WIDTH ) / static_cast< GLfloat >( HEIGHT );
    glm::mat4 projection = glm::perspective( FOV, ASPECT_RATIO, NEAR_CLIP, FAR_CLIP );

    shader.SetMat4( "projection", projection );

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
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        shader.Use();

        // Model matrix
        //glm::mat4 model = glm::mat4( 1.0f );
        //constexpr GLfloat ROTATION_ANGLE = glm::radians( 50.0f );
        //model = glm::rotate( model, static_cast< float > ( glfwGetTime() ) * ROTATION_ANGLE, glm::vec3( 0.5f, 1.0f, 0.0f ) );

        // View matrix
        glm::mat4 view = glm::mat4( 1.0f );
        view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );

        //shader.SetMat4( "model", model );
        shader.SetMat4( "view", view );

        glBindVertexArray( vao );
        for( GLuint i = 0u; i < 10u; ++i ) {
            glm::mat4 model = glm::mat4( 1.0f );
            model = glm::translate( model, cubePositions[ i ] );
            GLfloat angle = 20.0f * i;
            if( i % 3 == 0 ) {
                angle *= static_cast< float >( glfwGetTime() );
            }
            model = glm::rotate( model, glm::radians( angle ), glm::vec3( 1.0f, 0.3f, 0.5f ) );
            shader.SetMat4( "model", model );

            glDrawElements( GL_TRIANGLE_STRIP, std::size( indices ), GL_UNSIGNED_INT, 0 );
        }
        //glDrawElements( GL_TRIANGLE_STRIP, std::size( indices ), GL_UNSIGNED_INT, 0 );

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