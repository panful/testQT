#include "MyOglWidget.h"
#include <QDebug>

static const char* VS = "#version 330 core\n"
                        "layout (location = 0) in vec3 aPos;\n"
                        "layout (location = 1) in vec3 aColor;\n"
                        "out vec3 fragmentColor;"
                        "void main()\n"
                        "{\n"
                        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                        "   fragmentColor = aColor;\n"
                        "}\0";

static const char* FS = "#version 330 core\n"
                        "in vec3 fragmentColor;\n"
                        "out vec3 FragColor;\n"
                        "void main()\n"
                        "{\n"
                        "   FragColor = fragmentColor;\n"
                        "}\n\0";

// clang-format off
static float vertices[] = {
    // 位置                  //颜色
    -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
     0.0f,  0.0f, 0.0f,     0.0f, 0.0f, 0.0f
};

static unsigned int indices[] = {
    0, 1, 4, // 第一个三角形
    2, 3, 4  // 第二个三角形
};
// clang-format on

void MyOglWidget::initializeGL()
{
    if (initializeOpenGLFunctions())
    {
        qDebug() << "init success";
    }
    else
    {
        qDebug() << "init failed";
    }

    //--------------------------------------------------------
    // shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VS, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FS, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
    glDeleteProgram(shaderProgram);

    //--------------------------------------------------------
    // Vertex
    // glCreateBuffers和glGenBuffers作用一样，前者opengl4.5才支持，后者所有版本支持
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    glBindVertexArray(0);
}

void MyOglWidget::resizeGL(int w, int h)
{
}

void MyOglWidget::paintGL()
{
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
