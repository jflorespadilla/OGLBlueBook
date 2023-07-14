#include "GFXManager.h"

GFXManager::GFXManager():
m_rendering_program(0),
m_vertex_array_object(0),
m_buffer (0),
m_window(NULL),
m_glfwFlag(false)
{
    if (!glfwInit()) {
        m_glfwFlag = true;
    }

    // Adding window hints for clarity
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(640, 480, "Hola", NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        m_glfwFlag = true;
    }
    else {
        glfwMakeContextCurrent(m_window);
        gl3wInit();
    }
}

GFXManager::~GFXManager() {
    if (!m_glfwFlag) {
        glDeleteVertexArrays(1, &m_vertex_array_object);
        glDeleteProgram(m_rendering_program);

        glfwTerminate();
    }
}

void GFXManager::Start() {
    if (!m_glfwFlag) {
        m_rendering_program = CreateDefaultProgram();

        /*static const float positions[] = {
        0.25f, -0.25f, 0.5f, 1.0f,
       -0.25f, -0.25f, 0.5f, 1.0f,
        0.25f,  0.25f, 0.5f, 1.0f
        };

        static const float color[] = {
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f
        }; -Used this data set to implement a structure-of-arrays approach*/

        vertex vertecies[] = {
            {
                0.25f, -0.25f, 0.5f, 1.0f, // Position
                0.0f, 0.0f, 1.0f, 1.0f // Color
            },
            {
                 -0.25f, -0.25f, 0.5f, 1.0f,
                 0.0f, 1.0f, 0.0f, 1.0f
            },
            {
                0.25f,  0.25f, 0.5f, 1.0f,
                1.0f, 0.0f, 0.0f, 1.0f
            } // I can't believe I can get away with this bullsit in C++. wtf
        };

        // Using GL Docs to *correctly* use the glCreate* functions.
        glCreateBuffers(1, &m_buffer);
        glNamedBufferStorage(m_buffer, sizeof(GLfloat) * 4 * 2, vertecies, 0);

        glCreateVertexArrays(1, &m_vertex_array_object);
        //glBindVertexArray(m_vertex_array_object); -- Immediately bounded VBO. I'm binding whole arrays this way.
                                                                                   //  No need to inform VBO on seperate data segments, they all go to the same thing.

        //////  I'm going to be informing VBO of different data segments inside of the buffer                             //////////
        //////  It's necessary because now that the info is clumped together in our vertex struct                         //////////
        //////  we need to tell our graphix card what the data means based on where it is in the buffer               //////////
        //////  in this case <ppppccccppppcccc> for position and color. All floats, but where they are matters //////////

        glVertexArrayAttribBinding(m_vertex_array_object, 0, 0); // Setting up position data

        // Formats the first element of the buffer to contain position info - used in SoA approach
        /*glVertexArrayVertexBuffer(m_vertex_array_object, // Vertex array object
                                                    0,                                      // First vertex buffer binding
                                                    m_buffer,                    // Buffer object
                                                    0,                                     // Buffer offset
                                                    sizeof(GLfloat) * 4);       // Stride */

        glVertexArrayAttribFormat(m_vertex_array_object, // Vertex array object
                                                    0,                                      // First attribute
                                                    4,                                      // Component count, in this case 4
                                                    GL_FLOAT,                    // Component data type, in this case float
                                                    GL_FALSE,                    // Is normalized
                                                    offsetof(vertex, x));                                    // Location of first element of the vertex
        glEnableVertexArrayAttrib(m_vertex_array_object, 0);

        /* Formats the second element of the buffer to contain color info
        glNamedBufferStorage(m_buffer[1], sizeof(GLfloat) * 4 * 3, color, 0);
        glVertexArrayVertexBuffer(m_vertex_array_object, 1, m_buffer[1], 0, sizeof(GLfloat) * 4);
        glVertexArrayAttribFormat(m_vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vertex_array_object, 1, 1);
        */

        glVertexArrayAttribBinding(m_vertex_array_object, 1, 0);
        glVertexArrayAttribFormat(m_vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, offsetof(vertex, r));
        glEnableVertexArrayAttrib(m_vertex_array_object, 1);

        glVertexArrayVertexBuffer(m_vertex_array_object, 0, m_buffer, 0, sizeof(GLfloat) * 4 * 2);

        // to be used a little later
        m_projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        m_camera = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));
    }
    else {
        std::cout << "Error in creating window!";
    }
    return;
}

void GFXManager::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        Renderer(glfwGetTime());

        /*glDisableVertexArrayAttrib(m_vertex_array_object, 0);
        glDisableVertexAttribArray(1);*/
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

GLuint GFXManager::CreateDefaultProgram() {
    m_shaders.GetShaderSource("shaders/vs.shader");
    m_shaders.GetShaderSource("shaders/fs.shader");

    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    m_shaders.CompileShaders();

    program = glCreateProgram();

    vertex_shader = m_shaders.GetShaderID(ShaderType::VERTEX);
    if (vertex_shader) {
        glAttachShader(program, vertex_shader);
    }

    fragment_shader = m_shaders.GetShaderID(ShaderType::FRAGMENT);
    if (fragment_shader) {
        glAttachShader(program, fragment_shader);
    }
    glLinkProgram(program);

    if (vertex_shader) {
        glDeleteShader(vertex_shader);
    }

    if (fragment_shader) {
        glDeleteShader(fragment_shader);
    }

    return program;
}

/*
    Other shader programs will be loaded later. Some ideas:

    GLuint GFXManager::CreateCellShadeProgram() {

    }

    GLuint GFXManager::CreateTeaPot() {
    
    }
*/

void GFXManager::Renderer(float dt) {
    const GLfloat BGcolor[] = {0.5f, 0.1f, 0.3f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, BGcolor);
    glUseProgram(m_rendering_program);
    
    // I need to run some sort of check here. Info is going missing somewhere, but I'm not sure where.

    /*glEnableVertexArrayAttrib(m_vertex_array_object, 0);
    glEnableVertexAttribArray(1); - SoA setup*/ 

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
