#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "lib/fEngine/src/Fengine.h"
#include <QLineEdit>
QT_BEGIN_NAMESPACE
class QSlider;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(MainWindow *mw);

signals:

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void dockUndock();

private:
    QSlider *createSlider();
    QSlider *createSliderZoom();
    QLineEdit *createLineEdit();
    Fengine *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *zoomSlider;
    QLineEdit *lneDistance;
    MainWindow *mainWindow;
};

#endif // WINDOW_H
