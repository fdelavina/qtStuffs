#ifndef FLOG_H
#define FLOG_H

#include<string>
#include<QString>
#include<QDir>
#include<mutex>
#include<fstream>
#include "globalLib/Global/globalLib.h"

class FLog2
{
public:
    // parametrized ctor
    FLog2();


    // dtor
    ~FLog2()
    {
        mStream.close();
    }

    // write to log file
    void WriteLine(std::string content);

private:
    std::ofstream mStream;
    std::mutex mMutex;

    std::string setLogPath();


};

#endif // FLOGSINGLETON_H
