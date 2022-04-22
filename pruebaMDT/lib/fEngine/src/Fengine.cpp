
#include "Fengine.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <QDebug>
bool Fengine::m_transparent = false;

Fengine::Fengine(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
    setFocusPolicy(Qt::StrongFocus); // its a must for keyboard events
    m_sphere = new IcoSphere(1.0f);
    m_sphere->runOriginalIco(1.0f);
    latlon_ref.lat = 0.0;
    latlon_ref.lon = 0.0;
    float radius = 0.5;
    m_sphere->getNearTriangle(latlon_ref, radius, TypeMesh::OriginalIco);

    m_ico_ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_triangle_ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

}

Fengine::~Fengine()
{
    cleanup();
}

QSize Fengine::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize Fengine::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void Fengine::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void Fengine::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void Fengine::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void Fengine::setZoom(int zoom)
{
    int zoom_normalize = + zoom /100 -2.0;
    if (zoom_normalize != m_zoom) {
        m_zoom = zoom_normalize;
        emit zoomChanged(zoom);
        update();
    }
}


void Fengine::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_ico_vbo.destroy();
    m_triangle_vbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

static const char *vertexShaderSourceCore =
    "#version 330 core\n"
        "uniform mat4 projMatrix;\n"
        "uniform mat4 mvMatrix;\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projMatrix * mvMatrix* vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

static const char *fragmentShaderSourceCore =
    "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "void main() {\n"
    "   highp vec3 color = vec3(0.0, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(color, 1.0);\n"
    "}\n";

void Fengine::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Fengine::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    m_program->bindAttributeLocation("aPos", 0);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");


    setVaoIco();
    setVaoTriangle(true);
    setVaoPoint(true);
    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -4);

    // Light position is fixed.
    //m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void Fengine::setupVertexAttribsIco()
{
    m_ico_vbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    m_ico_vbo.release();

}

void Fengine::setupVertexAttribsTriangle()
{
    m_triangle_vbo.bind();
    QOpenGLFunctions *f2 = QOpenGLContext::currentContext()->functions();
    f2->glEnableVertexAttribArray(0);
    f2->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    m_triangle_vbo.release();
}

void Fengine::setupVertexAttribsPoint()
{
    m_point_vbo.bind();
    QOpenGLFunctions *f3 = QOpenGLContext::currentContext()->functions();
    f3->glEnableVertexAttribArray(0);
    f3->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    m_point_vbo.release();
}

void Fengine::setVaoIco()
{
    m_ico_vao.create();
    m_ico_vbo.create();
    m_ico_ebo.create();

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_ico_vao);
    m_ico_vao.bind();
        m_ico_vbo.bind();
        m_ico_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_ico_vbo.allocate(m_sphere->getOriginalvertices().vertices_cartesianas.data(),
                           m_sphere->getOriginalvertices().vertices_cartesianas.size() * sizeof(GLfloat));
        m_ico_ebo.bind();
        m_ico_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_ico_ebo.allocate(m_sphere->getOriginalvertices().indices.data(),
                           m_sphere->getOriginalvertices().indices.size() * sizeof(GLint));

        setupVertexAttribsIco();
}

void Fengine::setVaoTriangle(bool ini)
{
    if (ini)
    {
        m_triangle_vao.create();
        m_triangle_vbo.create();
        m_triangle_ebo.create();
    }


    QOpenGLVertexArrayObject::Binder vaoBinder2(&m_triangle_vao);
    m_triangle_vao.bind();
        m_triangle_vbo.bind();
        m_triangle_vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_triangle_vbo.allocate(m_sphere->getWorkingvertices().vertices_cartesianas.data(),
                                m_sphere->getWorkingvertices().vertices_cartesianas.size() * sizeof(GLfloat));
        m_triangle_ebo.bind();
        m_triangle_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_triangle_ebo.allocate(m_sphere->getWorkingvertices().indices.data(),
                                m_sphere->getWorkingvertices().indices.size() * sizeof(GLint));

        setupVertexAttribsTriangle();
}

void Fengine::setVaoPoint(bool ini)
{
    if (ini)
    {
    m_point_vao.create();
    m_point_vbo.create();
    m_point_ebo.create();
    }
    float x,y,z;
    float radius = 2;
    GeoMaths::getCartesianaFromLatLon(radius, latlon_ref.lat, latlon_ref.lon, x, y, z);
    line_ref.clear();
    line_ref.push_back(0.0);
    line_ref.push_back(0.0);
    line_ref.push_back(0.0);
    line_ref.push_back(x);
    line_ref.push_back(y);
    line_ref.push_back(z);

    qDebug()<<line_ref[0];
    qDebug()<<line_ref[1];
    qDebug()<<line_ref[2];
    qDebug()<<line_ref[3];
    qDebug()<<line_ref[4];
    qDebug()<<line_ref[5];

    QOpenGLVertexArrayObject::Binder vaoBinder2(&m_point_vao);
    m_point_vao.bind();
        m_point_vbo.bind();
        m_point_vbo.setUsagePattern(QOpenGLBuffer::StreamDraw);
        m_point_vbo.allocate(line_ref.data(),
                             line_ref.size() * sizeof(GLfloat));
//        m_point_ebo.bind();
//        m_point_ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
//        m_point_ebo.allocate(m_sphere->getWorkingvertices().indices.data(),
//                                m_sphere->getWorkingvertices().indices.size() * sizeof(GLint));

        setupVertexAttribsPoint();
}

void Fengine::runAlgorithm()
{
    setVaoPoint(false);
    if (m_sphere->isPointInActualTriangle(latlon_ref))
    {
        return;
    }
    else
    {
        m_sphere->getNearTriangle(latlon_ref, 0.01, TypeMesh::OriginalIco);
        setVaoTriangle(false);
    }
}


void Fengine::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    runAlgorithm();

    //qDebug()<<latlon_ref.lat;
    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);
    //m_camera.setToIdentity();
    //m_camera.translate(0, 0, m_zoom);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_triangle_vao);
    m_program->bind();
   // m_ico_vao.bind();
    m_triangle_vao.bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
   // glDrawElements(GL_TRIANGLES, m_sphere->getOriginalvertices().indices.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, m_sphere->getWorkingvertices().indices.size(), GL_UNSIGNED_INT, 0);
    m_triangle_vao.release();
 //   m_ico_vao.release();

     m_ico_vao.bind();
    // m_triangle_vao.bind();
     //m_program->setUniformValue(m_projMatrixLoc, m_proj);
     //m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     //glDrawArrays(GL_TRIANGLES, 0, 3);
     glDrawElements(GL_TRIANGLES, m_sphere->getOriginalvertices().indices.size(), GL_UNSIGNED_INT, 0);
     //glDrawElements(GL_TRIANGLES, m_sphere->getWorkingvertices().indices.size(), GL_UNSIGNED_INT, 0);
    // m_triangle_vao.release();
     m_ico_vao.release();

     m_point_vao.bind();
    // m_triangle_vao.bind();
    // m_program->setUniformValue(m_projMatrixLoc, m_proj);
     //m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
     //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
     glDrawArrays(GL_LINES, 0, 2);
     //glDrawElements(GL_TRIANGLES, m_sphere->getOriginalvertices().indices.size(), GL_UNSIGNED_INT, 0);
     //glDrawElements(GL_TRIANGLES, m_sphere->getWorkingvertices().indices.size(), GL_UNSIGNED_INT, 0);
    // m_triangle_vao.release();
     m_point_vao.release();

    m_program->release();


}

void Fengine::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void Fengine::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void Fengine::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"lat: " <<latlon_ref.lat;
    qDebug()<<"lon: " <<latlon_ref.lon;
    if( event->key() == Qt::Key_A )
    {
        latlon_ref.lat -= 0.5;
    }
    else if( event->key() == Qt::Key_D )
    {
        latlon_ref.lat += 0.5;
    }
    else if( event->key() == Qt::Key_W )
    {
        latlon_ref.lon += 0.5;
    }
    else if( event->key() == Qt::Key_S )
    {
        latlon_ref.lon -= 0.5;
    }
    else
    {
        return;
    }
}

void Fengine::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}
