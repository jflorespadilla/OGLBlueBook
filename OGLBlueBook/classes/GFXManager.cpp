#include "GFXManager.h"

GFXManager::GFXManager():
m_rendering_program(0),
m_vertex_array_object(0),
m_buffer(0),
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

        /* using glGen*
        glGenVertexArrays(1, &m_vertex_array_object);
        glGenBuffers(1, &m_buffer);
        
        glBindVertexArray(m_vertex_array_object);  
        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
        */

        // Using GL Docs to *correctly* use the glCreate* functions.
        //glCreateBuffers(1, &m_buffer);
        //glNamedBufferStorage(m_buffer, 4 * 3 * sizeof(GLfloat), NULL, GL_DYNAMIC_STORAGE_BIT);
        //glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

        static const float data[] = {
            0.25f, -0.25f, 0.5f, 1.0f,
           -0.25f, -0.25f, 0.5f, 1.0f,
            0.25f,  0.25f, 0.5f, 1.0f
        };

        /* Using glGen*
        glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(float), data, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)0);
        */

        //glNamedBufferSubData(m_buffer, 0, 4 * 3 * sizeof(GLfloat), data);

        /* Using glGen*
        void* ptr = glMapNamedBuffer(m_buffer, GL_WRITE_ONLY);
        memcpy(ptr, data, 4 * 3 * sizeof(float));
        glUnmapNamedBuffer(GL_ARRAY_BUFFER);*/

        //glCreateVertexArrays(1, &m_vertex_array_object);
        //glBindVertexArray(m_vertex_array_object);
        
        /*
        glEnableVertexAttribArray(0);

        glBindBuffer(m_buffer, 0);
        glBindVertexArray(m_vertex_array_object);
        */

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

    glBindVertexArray(m_vertex_array_object);

    //GLfloat attrib[] = { 0.0f , 0.0f, 0.0f, 0.0f };
    //glVertexAttrib4fv(0, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
