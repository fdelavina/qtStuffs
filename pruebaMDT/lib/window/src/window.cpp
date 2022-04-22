
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new Fengine;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();

    zoomSlider = createSliderZoom();

    //lneDistance = createLineEdit();

    connect(xSlider, &QSlider::valueChanged, glWidget, &Fengine::setXRotation);
    connect(glWidget, &Fengine::xRotationChanged, xSlider, &QSlider::setValue);
    connect(ySlider, &QSlider::valueChanged, glWidget, &Fengine::setYRotation);
    connect(glWidget, &Fengine::yRotationChanged, ySlider, &QSlider::setValue);
    connect(zSlider, &QSlider::valueChanged, glWidget, &Fengine::setZRotation);
    connect(glWidget, &Fengine::zRotationChanged, zSlider, &QSlider::setValue);

    connect(zoomSlider, &QSlider::valueChanged, glWidget, &Fengine::setZoom);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xSlider);
    container->addWidget(ySlider);
    container->addWidget(zSlider);
    container->addWidget(zoomSlider);
    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    zoomSlider->setValue(0 * 16);
    setWindowTitle(tr("Hello GL"));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSlider *Window::createSliderZoom()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 1000);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QLineEdit *Window::createLineEdit()
{
    QLineEdit *line = new QLineEdit();
    return line;

}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::dockUndock()
{
    if (parent()) {
        setParent(nullptr);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(nullptr, tr("Cannot dock"),
                                         tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(nullptr, tr("Cannot dock"),
                                     tr("Main window already occupied"));
        }
    }
}

