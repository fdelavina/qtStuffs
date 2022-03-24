#ifndef FENGINE_H
#define FENGINE_H
#include <qopengl.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <qopengl.h>
#include "lib/fEngine/src/sphereico.h"
#include "lib/dynamicSoologic/src/icosphere.h"
#include "globalLib/Global/globalLib.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class FENGINE_EXPORT Fengine : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Fengine(QWidget *parent = nullptr);
    ~Fengine();

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setZoom(int zoom);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void zoomChanged(int value);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void setupVertexAttribs();
    QVector<float> test;
    QVector<int> test_indice;
    bool m_core;
    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    int m_zoom = 0;
    QPoint m_lastPos;
    IcoSphere* m_sphere ;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLBuffer m_logoEbo;
    QOpenGLVertexArrayObject m_vao_points;
    QOpenGLBuffer m_logoVbo_points;

    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLShaderProgram *m_program2 = nullptr;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;
};

#endif
