#ifndef FLOG_H
#define FLOG_H

#include <string>
#include <QLoggingCategory>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QString>

/*
 * ******Logger*******
 */


Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
QScopedPointer<QFile>   m_logFile;
class FLog
{
    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */
protected:
    FLog()
    {
        // Set the logging file
        // check which a path to file you use
        m_logFile.reset(new QFile("C:/example/logFile.txt"));
        // Open the file logging
        m_logFile.data()->open(QFile::Append | QFile::Text);

        // Set handler
        qInstallMessageHandler(messageHandler);

        qDebug(logDebug()) << "Debug Button";
    }

    static FLog* singleton_;




public:

    /**
     * Singletons should not be cloneable.
     */
    FLog(FLog &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const FLog &) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static FLog *GetInstance();
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */

private:


public:
    //FLog();
};



#endif // FLOG_H
