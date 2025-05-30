#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QList>
#include <QTime>

class LogoRenderer : protected QOpenGLFunctions
{
public:
    LogoRenderer();
    ~LogoRenderer();

    void render();
    void initialize();

private:
    qreal m_fAngle;
    qreal m_fScale;

    void paintQtLogo();
    void createGeometry();
    void quad(qreal x1, qreal y1, qreal x2, qreal y2, qreal x3, qreal y3, qreal x4, qreal y4);
    void extrude(qreal x1, qreal y1, qreal x2, qreal y2);

    QList<QVector3D> vertices;
    QList<QVector3D> normals;
    QOpenGLShaderProgram program1;
    int vertexAttr1;
    int normalAttr1;
    int matrixUniform1;
};
