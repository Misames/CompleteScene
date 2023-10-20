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
    Texture::SetupManager();
    text = new Texture();
    mesh = new Mesh();
    mesh->LoadMesh("Sources/Assets/Mesh/lightning_obj.obj");

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
            delete renderer, mesh, text;
            renderer, mesh, text = nullptr;
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

    const GLuint STRIDE = sizeof(float) * 8;
    GLint positionLocation = glGetAttribLocation(program, "a_position");
    GLint texCoordLocation = glGetAttribLocation(program, "a_texcoords");
    GLint normalLocation = glGetAttribLocation(program, "a_normal");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(texCoordLocation);
    glEnableVertexAttribArray(normalLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, &mesh->vertex[0]);
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, STRIDE, &mesh->vertex[3]);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, STRIDE, &mesh->vertex[5]);

    glDrawArrays(GL_TRIANGLES, 0, mesh->indexVertex);

    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(texCoordLocation);
    glDisableVertexAttribArray(normalLocation);

    //--------------------------------------------------------------------------------------------------
    // GLuint VBO, EBO;
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(listData), listData, GL_STATIC_DRAW);
    //
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //
    // glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *)0);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDisableVertexAttribArray(0);
    //
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    //--------------------------------------------------------------------------------------------------
}
