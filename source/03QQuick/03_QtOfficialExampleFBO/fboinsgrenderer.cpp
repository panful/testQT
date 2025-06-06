#include "fboinsgrenderer.h"
#include "logorenderer.h"
#include <QDebug>
#include <QOpenGLFramebufferObject>
#include <QQuickWindow>
#include <QSGSimpleTextureNode>

class LogoInFboRenderer : public QQuickFramebufferObject::Renderer
{
public:
    LogoInFboRenderer()
    {
        logo.initialize();
    }

    void render() override
    {
        logo.render();
        update();
    }

    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override
    {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }

    LogoRenderer logo;
};

QQuickFramebufferObject::Renderer* FboInSGRenderer::createRenderer() const
{
    qDebug() << " create Renderer ";
    return new LogoInFboRenderer();
}
