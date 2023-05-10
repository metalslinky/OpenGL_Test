#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> // cout, endl

const char* vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4( aPos.x, aPos.y, aPos.z, 1.0 );\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(0.5f, 0.2f, 0.7f, 1.0f);\n"
"}\0";

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
    const unsigned int HEIGHT{ 800 }, WIDTH{ 600 };
    const char* TITLE{ "LearnOpenGL" };
    GLFWwindow* window = glfwCreateWindow( HEIGHT, WIDTH, TITLE, NULL, NULL );
    if( window == NULL ) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    // Initialise GLAD
    if( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) ) {
        std::cout << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );

    // Used with shader compilation error checking below
    int success;
    const unsigned int INFO_LOG_SIZE = 512u;
    char infoLog[ INFO_LOG_SIZE ];

    // Check if the vertex shader compiled without errors
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if( !success ) {
        glGetShaderInfoLog( vertexShader, INFO_LOG_SIZE, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );

    // Check if the fragment shader compiled without errors
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    if( !success ) {
        glGetShaderInfoLog( fragmentShader, INFO_LOG_SIZE, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    // Check that the shader program linking worked
    glGetProgramiv( shaderProgram, GL_COMPILE_STATUS, &success );
    if( !success ) {
        glGetProgramInfoLog( shaderProgram, INFO_LOG_SIZE, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );

    // Vertex array
    /*float vertices[] = { // ORIGINAL
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 2, 1
    };*/

    float vertices[] = { // EXERCISE 1
        -0.6f, -0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        0.4f, 0.2f, 0.0f,
        0.6f, -0.2f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5
    };

    /*float vertices[] = { // EXERCISE 2
        -0.6f, -0.2f, 0.0f,
        -0.4f, 0.2f, 0.0f,
        -0.2f, -0.2f, 0.0f,
        0.2f, -0.2f, 0.0f,
        0.4f, 0.2f, 0.0f,
        0.6f, -0.2f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 4, 5
    };*/

    // Create VAO, VBO, and EBO
    unsigned int vao, vbo, ebo;
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

    // Configure vertex attriutes
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
    glEnableVertexAttribArray( 0 );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    while( !glfwWindowShouldClose( window ) ) {
        // Input
        processInput( window );

        // Render
        glClearColor( 0.4f, 0.3f, 0.2f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        glUseProgram( shaderProgram );
        glBindVertexArray( vao );
        glDrawElements( GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    // De-allocate resources
    glDeleteBuffers( 1, &vao );
    glDeleteBuffers( 1, &vbo );
    glDeleteBuffers( 1, &ebo );
    glDeleteProgram( shaderProgram );

    glfwTerminate();
    return 0;
}