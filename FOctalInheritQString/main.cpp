#include <QCoreApplication>
#include <qoctal.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FOctal b = FOctal("");
    return a.exec();
}
