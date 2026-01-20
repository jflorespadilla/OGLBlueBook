#include "GFXManager.h"

GFXManager::GFXManager():
m_verticies(0),
m_rendering_program(0),
m_vertex_array_object(0),
m_buffer {0, 0},
m_window(NULL),
m_glfwFlag(false),
m_projection(glm::mat4(1.0f)),
m_camera(glm::mat4(1.0f))
{
    if (!glfwInit()) {
        m_glfwFlag = true;
    }

    // Adding window hints for clarity
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int width = 850;
    int hight = 620;
    m_window = glfwCreateWindow(width, hight, "Test window of depression", NULL, NULL);
    
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

// Going to need some extra time to reorganize startup.
// Working on differnt programs setting for easy sanity checks is needed.
void GFXManager::Start() {
    if (!m_glfwFlag) {
        std::cout << "Select Program to render:\n\n1) Triangle\n2) Square\n\n";
        char input;
        std::cin >> input;

        switch (input) {
        case '1':
            m_shaders.GetShaderSource("shaders/triangle_vs.shader");
            m_shaders.GetShaderSource("shaders/triangle_fs.shader");
            m_rendering_program = CreateProgram();
            m_verticies = 3;
            glUseProgram(m_rendering_program);
            BasicTriangle();
            break;
        case '2':
            m_shaders.GetShaderSource("shaders/square_vs.shader");
            m_shaders.GetShaderSource("shaders/square_fs.shader");
            m_rendering_program = CreateProgram();
            m_verticies = 6;
            glUseProgram(m_rendering_program);
            BasicSquare();
            break;
        }
    }
    else {
        std::cout << "Error in creating window!";
    }
    return;
}

void GFXManager::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        Renderer(glfwGetTime());

        // Disabling each vao attribute
        glDisableVertexArrayAttrib(m_vertex_array_object, 0);
        glDisableVertexArrayAttrib(m_vertex_array_object, 1);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void GFXManager::BasicTriangle() {
    const unsigned int vertexCount = 3;
    // Setting positional and color data
    glm::vec4 positions[vertexCount] = { glm::vec4(-0.25f, 0.25f, 0.5f, 1.0f),
                                             glm::vec4(-0.25f, -0.25f, 0.5f, 1.0f),
                                             glm::vec4(0.25f, 0.25f, 0.5f, 1.0f) };
    
    glm::vec4 colors[vertexCount] = { glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                                        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) };

    glCreateBuffers(2, &m_buffer[0]);
    glNamedBufferStorage(m_buffer[0], sizeof(GLfloat) * 4 * vertexCount, positions, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    // Formats the first element of the buffer to contain position info - used in SoA approach
    glVertexArrayVertexBuffer(m_vertex_array_object, // Vertex array object
        0,                                      // First vertex buffer binding
        m_buffer[0],                    // Buffer object
        0,                                     // Buffer offset
        sizeof(GLfloat) * 4);       // Stride

    glVertexArrayAttribFormat(m_vertex_array_object, // Vertex array object
        0,                                      // First attribute
        4,                                      // Component count, in this case 4
        GL_FLOAT,                    // Component data type, in this case float
        GL_FALSE,                    // Is normalized
        0);                                    // Location of first element of the vertex

    glNamedBufferStorage(m_buffer[1], sizeof(GLfloat) * 4 * vertexCount, colors, GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayVertexBuffer(m_vertex_array_object, 1, m_buffer[1], 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(m_vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(m_vertex_array_object, 1, 1);
}

void GFXManager::BasicSquare() {
    // Brute force. Next iteration should use IBO
    const unsigned int vertexCount = 6;
    // Setting positional and color data
    glm::vec4 positions[vertexCount] = { glm::vec4(-0.25f, 0.25f, 0.5f, 1.0f),
                                             glm::vec4(-0.25f, -0.25f, 0.5f, 1.0f),
                                             glm::vec4(0.25f, 0.25f, 0.5f, 1.0f),

                                             glm::vec4(0.25f, -0.25f, 0.5f, 1.0f),
                                             glm::vec4(0.25f, 0.25f, 0.5f, 1.0f),
                                             glm::vec4(-0.25f, -0.25f, 0.5f, 1.0f) };

    glm::vec4 colors[vertexCount] = { glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                                          glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                          glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),

                                          glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                                          glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                          glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) };

    glCreateBuffers(2, &m_buffer[0]);
    glNamedBufferStorage(m_buffer[0], sizeof(GLfloat) * 4 * vertexCount, positions, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &m_vertex_array_object);
    glBindVertexArray(m_vertex_array_object);

    // Finish position buffer
    glVertexArrayVertexBuffer(m_vertex_array_object, 0, m_buffer[0], 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(m_vertex_array_object, 0, 4, GL_FLOAT, GL_FALSE, 0);

    // Finish color buffer
    glNamedBufferStorage(m_buffer[1], sizeof(GLfloat) * 4 * vertexCount, colors, GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayVertexBuffer(m_vertex_array_object, 1, m_buffer[1], 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(m_vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(m_vertex_array_object, 1, 1);
}

GLuint GFXManager::CreateProgram() {
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

// This should be the default render that I use in a general application.
void GFXManager::Renderer(float dt) {
    const GLfloat BGcolor[] = {0.3f, 0.1f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, BGcolor);

    // Enabling each attribue in vao
    glEnableVertexArrayAttrib(m_vertex_array_object, 0);
    glEnableVertexArrayAttrib(m_vertex_array_object, 1);

    glDrawArrays(GL_TRIANGLES, 0, m_verticies);
}
