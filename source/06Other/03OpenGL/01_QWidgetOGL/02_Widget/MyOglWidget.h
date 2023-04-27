#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLWidget>

class MyOglWidget : public QOpenGLWidget,
                    protected QOpenGLFunctions_4_5_Core
{
public:
    void paintGL();
    void initializeGL();
    void resizeGL(int w, int h);

private:
    unsigned int m_VAO { 0 };
};
