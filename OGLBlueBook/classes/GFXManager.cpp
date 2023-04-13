#include "GFXManager.h"

GFXManager::GFXManager():
m_rendering_program(0),
m_vertex_array_object(0),
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
        m_shaders.GetShaderSource("shaders/vs.shader");
        m_shaders.GetShaderSource("shaders/fs.shader");
        m_shaders.GetShaderSource("shaders/tcs.shader-n");
        m_shaders.GetShaderSource("shaders/tes.shader-n");
        m_shaders.GetShaderSource("shaders/geo.shader-n");

        m_rendering_program = CompileShaders();
        glCreateVertexArrays(1, &m_vertex_array_object);
        glBindVertexArray(m_vertex_array_object);

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

// Rework this function to return void and have a separate "CreateProgram" function
GLuint GFXManager::CompileShaders() {
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint tessc_shader;
    GLuint tesse_shader;
    GLuint geo_shader;
    GLuint program;

    m_shaders.CompileShaders();

    program = glCreateProgram();

    vertex_shader = m_shaders.GetShaderID(ShaderType::VERTEX);
    glAttachShader(program, vertex_shader);

    /*if (activeShaders["Tess Control"]) {
        tessc_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tessc_shader, 1, &tcs_shader_source, NULL);
        glCompileShader(tessc_shader);
        //CheckShaderCompilation(tessc_shader);
        glAttachShader(program, tessc_shader);
    }

    if (activeShaders["Tess"]) {
        tesse_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tesse_shader, 1, &tes_shader_source, NULL);
        glCompileShader(tesse_shader);
        //CheckShaderCompilation(tesse_shader);
        glAttachShader(program, tesse_shader);
    }

    if (activeShaders["Geo"]) {
        geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geo_shader, 1, &geo_shader_source, NULL);
        glCompileShader(geo_shader);
        //CheckShaderCompilation(geo_shader);
        glAttachShader(program, geo_shader);
    }*/

    fragment_shader = m_shaders.GetShaderID(ShaderType::FRAGMENT);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    /*if (activeShaders["Tess Control"]) {
        glDeleteShader(tessc_shader);
    }
    if (activeShaders["Tess"]) {
        glDeleteShader(tesse_shader);
    }
    if (activeShaders["Geo"]) {
        glDeleteShader(geo_shader);
    }*/

    return program;
}

// Might rename the function to something like GetGLLog or something
void GFXManager::CheckShaderCompilation(GLuint& shader) {
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
        for (int i = 0; i < maxLength; i++) {
            std::cout << errorLog[i];
        }
    }
    else {
        std::cout << "Success!!!\n\n";
    }
}

void GFXManager::Renderer(float dt) {
    const GLfloat BGcolor[] = { (float)sin(dt) * 0.5f + 0.5f, (float)cos(dt) * 0.5f + 0.5f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, BGcolor);
    glUseProgram(m_rendering_program);

    GLfloat attrib[] = { (float)sin(dt) * 0.5f , (float)cos(dt) * 0.6f, 0.0f, 0.0f };
    glVertexAttrib4fv(0, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
