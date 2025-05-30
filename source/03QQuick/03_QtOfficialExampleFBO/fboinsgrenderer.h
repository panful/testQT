#pragma once

#include <QtQuick/QQuickFramebufferObject>

class LogoRenderer;

class FboInSGRenderer : public QQuickFramebufferObject
{
    Q_OBJECT
    // QML_NAMED_ELEMENT(MyRenderer)
public:
    Renderer* createRenderer() const;
};
