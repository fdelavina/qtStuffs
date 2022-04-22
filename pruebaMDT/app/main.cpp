#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "lib/window/src/mainwindow.h"
#include "lib/fEngine/src/Fengine.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Qt Hello GL 2 Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption multipleSampleOption("multisample", "Multisampling");
    parser.addOption(multipleSampleOption);
    QCommandLineOption coreProfileOption("coreprofile", "Use core profile");
    parser.addOption(coreProfileOption);
    QCommandLineOption transparentOption("transparent", "Transparent window");
    parser.addOption(transparentOption);

    parser.process(app);

    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    if (parser.isSet(multipleSampleOption))
        fmt.setSamples(4);
    if (parser.isSet(coreProfileOption)) {
        fmt.setVersion(4, 4);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    }
    fmt.setVersion(4, 4);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow mainWindow;

    Fengine::setTransparent(parser.isSet(transparentOption));
    if (Fengine::isTransparent()) {
        mainWindow.setAttribute(Qt::WA_TranslucentBackground);
        mainWindow.setAttribute(Qt::WA_NoSystemBackground, false);
    }
    mainWindow.resize(mainWindow.sizeHint());
    int desktopArea = QApplication::desktop()->width() *
                     QApplication::desktop()->height();
    int widgetArea = mainWindow.width() * mainWindow.height();
    if (((float)widgetArea / (float)desktopArea) < 0.75f)
        mainWindow.show();
    else
        mainWindow.showMaximized();

    return app.exec();
}
