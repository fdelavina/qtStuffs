#ifndef FLOGSINGLETON_H
#define FLOGSINGLETON_H



#include "FransiLog/FLog2/flog.h"

//#include "globalLib/Global/globalLib.h"

class FRANSILOG_EXPORT MyLoggerSingleton
{
public:
    MyLoggerSingleton(MyLoggerSingleton const&) = delete;             // Copy construct
    MyLoggerSingleton(MyLoggerSingleton&&) = delete;                  // Move construct
    MyLoggerSingleton& operator=(MyLoggerSingleton const&) = delete;  // Copy assign
    MyLoggerSingleton& operator=(MyLoggerSingleton &&) = delete;      // Move assign

    static FLog2& Instance()
    {
        static FLog2 myInstance;
        return myInstance;
    }


protected:
    MyLoggerSingleton() {}
    ~MyLoggerSingleton() {}


};

#endif // FLOGSINGLETON_H
