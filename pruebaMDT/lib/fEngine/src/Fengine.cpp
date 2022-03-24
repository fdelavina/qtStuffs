
#include "Fengine.h"

#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

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

    m_sphere = new IcoSphere(1.0f);
    m_sphere->runOriginalIco(1.0f);
    m_logoEbo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

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
    m_logoVbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

static const char *vertexShaderSourceCore =
    "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &Fengine::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
    m_program->bindAttributeLocation("aPos", 0);
    m_program->link();

    m_program->bind();
    //m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    //m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_logoVbo.create();
    m_logoEbo.create();
    m_logoVbo.bind();

    std::vector<float> a = m_sphere->getOriginalVertices().vertices;
    QVector<float> b = QVector<float>(a.begin(), a.end());


    test.append( 0.5f);test.append( 0.5f);test.append(0.0f);
    test.append( 0.5f);test.append(-0.5f);test.append(0.0f);
    test.append(-0.5f);test.append(-0.5f);test.append(0.0f);
    test.append(-0.5f);test.append( 0.5f);test.append(0.0f);

    m_logoVbo.allocate(test.constData(), 12 * sizeof(GLfloat));

    m_logoEbo.bind();
    m_logoEbo.setUsagePattern(QOpenGLBuffer::StaticDraw);



    std::vector<int> a2 = m_sphere->getOriginalVertices().indices;
    QVector<int> b2 = QVector<int>(a2.begin(), a2.end());

    test_indice.append(0);test_indice.append(1);test_indice.append(3);
    test_indice.append(1);test_indice.append(2);test_indice.append(3);

    m_logoEbo.allocate(test_indice.constData(), 6 * sizeof(GLint));


    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    //m_camera.setToIdentity();
    //m_camera.translate(0, 0, -2);

    // Light position is fixed.
    //m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();


}

void Fengine::setupVertexAttribs()
{
    m_logoVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                             nullptr);

    //m_logoVbo.release();

}


void Fengine::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   // m_world.setToIdentity();
//    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
//    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
//    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);
//    //m_camera.setToIdentity();
//    m_camera.translate(0, 0, m_zoom);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_vao.bind();
//    m_program->setUniformValue(m_projMatrixLoc, m_proj);
//    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vao.release();
    m_program->release();


}

void Fengine::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
   // m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void Fengine::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
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
