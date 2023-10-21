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

    // Init Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Init Texture Manager
    Texture::SetupManager();
    text = Texture();

    // Init Mesh
    mesh = Mesh();
    mesh.LoadMesh("Sources/Assets/Mesh/lightning_obj.obj");

#ifdef _DEBUG
    shader.LoadVertexShader("Sources/Shaders/vertex.glsl");
    shader.LoadFragmentShader("Sources/Shaders/fragment.glsl");
    shader.Initialize();
#else
    shader.LoadVertexShader("vertex.glsl");
    shader.LoadFragmentShader("fragment.glsl");
    shader.Initialize();
#endif

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
            glDeleteBuffers(1, &VAO);
            glDeleteBuffers(1, &VBO);
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

void RasterizationEngine::Draw(GLFWwindow *window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint program = shader.GetProgram();
    glUseProgram(program);

    float zNear = 0.1f, zFar = 1000.0f, fov = 45.0f;
    camera.Matrix(fov, zNear, zFar, &shader, "u_projection");

    constexpr int STRIDE = sizeof(Vertex);
    glBufferData(GL_ARRAY_BUFFER, STRIDE * mesh.vertexs.size(), mesh.vertexs.data(), GL_STATIC_DRAW);

    GLint positionLocation = glGetAttribLocation(program, "a_position");
    GLint texCoordLocation = glGetAttribLocation(program, "a_texcoords");
    GLint normalLocation = glGetAttribLocation(program, "a_normal");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glEnableVertexAttribArray(normalLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, position));
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, uv));
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, (void *)offsetof(Vertex, normal));

    glDrawArrays(GL_TRIANGLES, 0, mesh.vertexs.size());

    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(texCoordLocation);
    glDisableVertexAttribArray(normalLocation);
}
