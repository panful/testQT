#include "GLWidget.h"
#include <QDebug>

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.5, 0.5, 0.5, 0); // 设置背景色
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void GLWidget::resizeGL()
{
}
