#ifndef SPHEREWINDOW_H
#define SPHEREWINDOW_H

#include <QGuiApplication>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QtMath>
#include "globalLib/Global/globalLib.h"
#include "EngineWindow.h"
#include "shaders.h"

class FENGINE_EXPORT SphereWindow : public EngineWindow
{
public:
    using EngineWindow::EngineWindow;

    void initialize() override;
    void render() override;

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
};
#endif // SPHEREWINDOW_H
