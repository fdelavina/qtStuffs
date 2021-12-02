#include <QCoreApplication>
#include <QDebug>

#include "FransiLog/QLogger.h"
#include "FransiComm/ClientWS.h"
#include "FransiComm/ServerWS.h"
int main(int argc, char *argv[])
{
    qInfo() << "SimulatorScomba initializing";

//    static const QString l_file1("test1.log");
//    static const QString l_module1("QLoggerTest");
//    static const QString l_module2("QLoggerTest");
//    QLogger::QLoggerManager *l_manager = QLogger::QLoggerManager::getInstance();
//    l_manager->addDestination(l_file1, l_module1, QLogger::LogLevel::Debug);

//    QLog_Debug(l_module1, QStringLiteral("This is a debug log message 0."));

//    l_manager->addDestination(l_file1, l_module2, QLogger::LogLevel::Debug, QString(), QLogger::LogMode::Full);

//    QLog_Debug(l_module2, QStringLiteral("This is a debug log message 0."));
    QCoreApplication a(argc, argv);


  //  EchoClient client(QUrl(QStringLiteral("ws://192.168.139.131:32774")), true); //debug = true
    EchoClient client(QUrl(QStringLiteral("ws://localhost:1234")), true); //debug = true
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);

   // EchoServer *server = new EchoServer(5065, true);
    //QObject::connect(server, &EchoServer::closed, &a, &QCoreApplication::quit);

    //qInfo() << "SimulatorScomba ending";
    return a.exec();
}
