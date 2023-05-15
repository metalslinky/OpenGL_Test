#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    GLfloat firstTriangleVertices[] = { // CW
        -0.6f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.4f,  0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat secondTriangleVertices[] = { // CCW
        0.2f,  0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.4f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.6f,  0.2f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint indices[] = {
        0, 1, 2
    };

    // Create VAO, VBO, and EBO
    GLuint vao[ 2 ], vbo[ 2 ], ebo;
    glGenVertexArrays( 2, vao );
    glGenBuffers( 2, vbo );
    glGenBuffers( 1, &ebo );

    // Bind VAO
    glBindVertexArray( vao[ 0 ] );

    // Bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 0 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( firstTriangleVertices ), firstTriangleVertices, GL_STATIC_DRAW );

    // Bind EBO
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    // Configure vertex attriutes
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( void* )0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( void* )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );

    // Do it all again for the second triangle
    // TODO: This looks fucking ugly. Move it somewhere else.
    glBindVertexArray( vao[ 1 ] );
    glBindBuffer( GL_ARRAY_BUFFER, vbo[ 1 ] );
    glBufferData( GL_ARRAY_BUFFER, sizeof( secondTriangleVertices ), secondTriangleVertices, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( void* )0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( void* )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    while( !glfwWindowShouldClose( window ) ) {
        // Input
        processInput( window );

        // Render
        glClearColor( 0.4f, 0.3f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        shader.Use();
        shader.setFloat( "horizontalOffset", 0.2f );

        //GLfloat timeValue = glfwGetTime();
        //GLfloat greenValue = ( sin( timeValue ) / 2.0f ) + 0.5f;
        //GLint vertexColourLocation = glGetUniformLocation( shader.GetProgramID(), "vertexColour" );
        //glUniform4f( vertexColourLocation, 0.0f, greenValue, 0.0f, 1.0f );

        glBindVertexArray( vao[ 0 ] );
        glDrawElements( GL_TRIANGLES, std::size( indices ), GL_UNSIGNED_INT, 0 );
        glBindVertexArray( vao[ 1 ] );
        glDrawElements( GL_TRIANGLES, std::size( indices ), GL_UNSIGNED_INT, 0 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteBuffers( 2, vao );
    glDeleteBuffers( 2, vbo );
    glDeleteBuffers( 1, &ebo );
    glDeleteProgram( shader.GetProgramID() );

    glfwTerminate();
    return 0;
}