#include "FransiLog/FLog2/flog.h"

QString LOGFOLDERNAME = "logs";
QString LOGFILENAME   = "LOG_";

FLog2::FLog2()
{
    mStream.open(setLogPath());

    if (mStream.fail())
    {
        throw std::iostream::failure("Cannot open file: " + setLogPath());
    }
}

void FLog2::WriteLine(std::string content)
{
    std::lock_guard<std::mutex> lock(mMutex);

    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timestamp[26];
    ctime_s(timestamp, sizeof timestamp, &now);

    std::string timestampWithoutEndl(timestamp);
    timestampWithoutEndl = timestampWithoutEndl.substr(0, 24);

    mStream << timestampWithoutEndl << ": " << content << std::endl;

}

std::string FLog2::setLogPath()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char timestamp[26];
    ctime_s(timestamp, sizeof timestamp, &now);

    std::string timestampWithoutEndl(timestamp);
    timestampWithoutEndl = timestampWithoutEndl.substr(0, 24);

    if(!QDir(LOGFOLDERNAME).exists())
    {
        QDir().mkdir(LOGFOLDERNAME);
    }

    QString currentPath = QDir::currentPath();
    QString logPath = currentPath + "/" + LOGFOLDERNAME;

    QString logfilenamewithdate = LOGFILENAME + QString::fromStdString(timestampWithoutEndl) + ".txt";
    QString logPathFile = logPath + "/" + logfilenamewithdate.replace(" ","_").replace(":","-");

    return logPathFile.toStdString();
}
