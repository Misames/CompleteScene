#include "Mesh.hpp"
#include "GLShader.hpp"

#include "Axes.hpp"

Axes::~Axes()
{
    Release();
}

void Axes::Initialize()
{
    if (initialized)
        Release();

    shader = new GLShader();

#ifdef _DEBUG
    shader->LoadVertexShader("Sources/Shaders/axes_vertex.glsl");
    shader->LoadFragmentShader("Sources/Shaders/axes_fragment.glsl");
#else
    shader->LoadVertexShader("axes_vertex.glsl");
    shader->LoadFragmentShader("axes_fragment.glsl");
#endif

    shader->Initialize();
    program = shader->GetProgram();

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    positionLocation = glGetAttribLocation(program, "aPosition");
    colorLocation = glGetAttribLocation(program, "aColor");

    initialized = true;
    enabled = true;
    cout << "Axes initlialize" << endl;
}

void Axes::Release()
{
    if (initialized)
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);

        initialized = false;
        enabled = false;
        cout << "Axes release" << endl;
    }
}

void Axes::Render(int width, int height) const
{
    if (enabled == false)
        return;

    GLfloat axesLength = 0.1f * std::min(width, height); // 10% de la taille minimale (largeur ou hauteur)
    GLfloat axesVertices[36] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       // Origine (Rouge)
        axesLength, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Fin de l'axe X (Rouge)
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,       // Origine (Vert)
        0.0f, axesLength, 0.0f, 0.0f, 1.0f, 0.0f, // Fin de l'axe Y (Vert)
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,       // Origine (Bleu)
        0.0f, 0.0f, axesLength, 0.0f, 0.0f, 1.0f  // Fin de l'axe Z (Bleu)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));

    glUseProgram(program);
    glDrawArrays(GL_LINES, 0, 6);

    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}

GLShader *Axes::GetShader() const
{
    return shader;
}
