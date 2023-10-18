#include <iostream>
#include "RasterizationEngine.hpp"
#include "OpenGL/OpenGLRenderer.hpp"

using namespace std;

RasterizationEngine::~RasterizationEngine()
{
    Release();
}

void RasterizationEngine::Initialize(const RenderingEngineInfo &renderingEngineInfo)
{
    if (initialized)
        Release();

    switch (renderingEngineInfo.rendererInfo->rendererType)
    {
    case OPENGL:
        renderer = new OpenGLRenderer();
        break;
    case VULKAN:
        throw runtime_error("Vulkan renderer not implemented");
        break;
    case DIRECTX:
        throw runtime_error("DirectX renderer not implemented");
        break;
    }

    if (!renderer)
        throw bad_alloc();

    renderer->Initialize(*renderingEngineInfo.rendererInfo);

// Load Shaders
#ifdef _DEBUG
    shader.LoadVertexShader("Sources/Shaders/vertex.glsl");
    shader.LoadFragmentShader("Sources/Shaders/fragment.glsl");
    shader.Initialize();
#else
    shader.LoadVertexShader("vertex.glsl");
    shader.LoadFragmentShader("fragment.glsl");
    shader.Initialize();
#endif

    // Apply Pink Texture
    GenerateTexture();

    initialized = true;
    cout << "RasterizationEngine initialize" << endl;
}

void RasterizationEngine::Release()
{
    if (initialized)
    {
        if (renderer)
        {
            renderer->Release();
            delete renderer;
            renderer = nullptr;
        }

        initialized = false;
        cout << "RasterizationEngine release" << endl;
    }
}

void RasterizationEngine::Render(float lag)
{
    GLFWwindow *glfwWindow = renderer->GetWindow()->GetHandle();
    camera.Inputs(glfwWindow);
    Draw(glfwWindow);
    glfwSwapBuffers(glfwWindow);
}

// Draw rectangle with 2 triangles
void RasterizationEngine::Draw(GLFWwindow *window)
{
    GLfloat vertices[] = {-0.5f, -0.5f,
                          0.5f, -0.5f,
                          0.5f, 0.5f,
                          -0.5f, 0.5f};

    GLuint indices[] = {0, 1, 2,
                        2, 3, 0};
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint program = shader.GetProgram();
    glUseProgram(program);

    float zNear = 0.1f, zFar = 1000.0f, fov = 45.0f;
    camera.Matrix(fov, zNear, zFar, &shader, "u_projection");

    int positionLocation = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(positionLocation);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void RasterizationEngine::GenerateTexture() const
{
    GLuint textureId;
    uint8_t *data = new uint8_t[4]{255, 0, 255, 255};

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glActiveTexture(GL_TEXTURE0);

    delete[] data;
}
