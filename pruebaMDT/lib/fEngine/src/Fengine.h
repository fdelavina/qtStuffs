#ifndef FENGINE_H
#define FENGINE_H
#include <qopengl.h>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <qopengl.h>
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
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setupVertexAttribsIco();
    void setupVertexAttribsTriangle();
    void setupVertexAttribsPoint();
    void setVaoIco();
    void setVaoTriangle(bool ini);
    void setVaoPoint(bool ini);
    void runAlgorithm();

    QVector<float> test;
    QVector<int> test_indice;
    bool m_core;
    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    int m_zoom = 0;
    QPoint m_lastPos;
    IcoSphere* m_sphere ;
    QOpenGLVertexArrayObject m_ico_vao;
    QOpenGLBuffer m_ico_vbo;
    QOpenGLBuffer m_ico_ebo;

    QOpenGLVertexArrayObject m_triangle_vao;
    QOpenGLBuffer m_triangle_vbo;
    QOpenGLBuffer m_triangle_ebo;

    QOpenGLVertexArrayObject m_point_vao;
    QOpenGLBuffer m_point_vbo;
    QOpenGLBuffer m_point_ebo;

    std::vector<float> line_ref;

    QOpenGLShaderProgram *m_program = nullptr;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;

     LatLon latlon_ref;
};

#endif
