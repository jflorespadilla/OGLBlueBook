#include "GFXManager.h"

GFXManager::GFXManager():
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
    m_window = glfwCreateWindow(850, 620, "Hola", NULL, NULL);
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
        glUseProgram(m_rendering_program);

        //BasicTriangle();
        // Need to make a basic square program
        BasicCube();
    }
    else {
        std::cout << "Error in creating window!";
    }
    return;
}

void GFXManager::Run() {
    while (!glfwWindowShouldClose(m_window)) {
        Renderer(glfwGetTime());

        glDisableVertexArrayAttrib(m_vertex_array_object, 0);
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

void GFXManager::BasicTriangle() {
    glm::vec4 positions[3] = { glm::vec4(0.25f, -0.25f, 0.5f, 1.0f),
                                             glm::vec4(-0.25f, -0.25f, 0.5f, 1.0f),
                                             glm::vec4(0.25f, 0.25f, 0.5f, 1.0f) };
    
    glm::vec4 colors[3] = { glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                                        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) };

    glCreateBuffers(2, &m_buffer[0]);
    glNamedBufferStorage(m_buffer[0], sizeof(GLfloat) * 4 * 3, positions, 0);

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
    glEnableVertexArrayAttrib(m_vertex_array_object, 0);

    glNamedBufferStorage(m_buffer[1], sizeof(GLfloat) * 4 * 3, colors, 0);
    glVertexArrayVertexBuffer(m_vertex_array_object, 1, m_buffer[1], 0, sizeof(GLfloat) * 4);
    glVertexArrayAttribFormat(m_vertex_array_object, 1, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(m_vertex_array_object, 1, 1);
}

void GFXManager::BasicCube() {
    glEnable(GL_DEPTH_TEST); // Attempting to recrate cube from the book first, might try other methods to understand what's going on.
    glm::vec4 positions[12] = { glm::vec4(-0.25f, 0.25f, -0.5f, 1.0f),
                                                 glm::vec4(-0.25f, -0.25f, -0.5f, 1.0f),
                                                 glm::vec4(0.25f, -0.25f, -0.5f, 1.0f),

                                                 glm::vec4(0.25f, -0.25f, -0.5f, 1.0f),
                                                 glm::vec4(0.25f, 0.25f, -0.5f, 1.0f),
                                                 glm::vec4(-0.25f, 0.25f, -0.5f, 1.0f),
    
                                                 glm::vec4(-0.25f, 0.25f, -0.5f, 1.0f),
                                                 glm::vec4(0.25f, 0.25f, -0.5f, 1.0f),
                                                 glm::vec4(0.25f, 0.25f, 0.5f, 1.0f),

                                                 glm::vec4(0.25f, 0.25f, 0.5f, 1.0f),
                                                 glm::vec4(-0.25f, 0.25f, 0.5f, 1.0f),
                                                 glm::vec4(-0.25f, 0.25f, -0.5f, 1.0f)};

    glm::vec4 colors[3] = { glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
                                        glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
                                        glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) };

    m_projection = glm::perspective(50.0f, 850.0f / 620.0f, 0.1f, 1.0f);

    glGenBuffers(1, &m_buffer[0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 12, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
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

// This should be the default render that I use in a general application.
void GFXManager::Renderer(float dt) {
    const GLfloat BGcolor[] = {0.3f, 0.1f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, BGcolor);
    glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);

    //float TV = dt * glm::pi<float>() * 0.1f;
    glm::mat4 mv_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(m_projection));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
