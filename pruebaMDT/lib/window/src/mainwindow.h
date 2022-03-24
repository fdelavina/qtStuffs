#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalLib/Global/globalLib.h"

class WINDOW_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void onAddNew();
};

#endif // MAINWINDOW_H
