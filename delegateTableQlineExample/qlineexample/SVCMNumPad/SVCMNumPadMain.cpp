#include "SVCMNumPad.h"
#include <QObject>
#include <QTranslator>
#include <libLog/Logit.h>
#include <libSignalHandler/TermSignalHandler.h>
#include <libUSSBase/USSApplication.h>


int main(int argc, char *argv[])
{
    cms::USSApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);

    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString(":/lang/lang/") + locale);
    app.installTranslator(&translator);

    cms::SVCMNumPad svcm_numpad ;

    TermSignalHandler::registerSignals();

    QObject::connect(&app                  ,
                     SIGNAL(aboutToQuit()) ,
                     &svcm_numpad  ,
                     SLOT( deleteLater() ));


    return app.exec();
}
