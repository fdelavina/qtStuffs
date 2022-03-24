#include <QCoreApplication>
#include <QByteArray>
#include <QDebug>
#include <QChar>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    QByteArray text = QByteArray::fromHex("f2");

    qDebug()<<" "<<text;
    qDebug()<<" "<<text.toHex();


    QString textString = QString(text);

    QString textString2 = "ff";




    bool ok = false;
    QString binary = QString::number(textString2.toInt(&ok,16),2);

    qDebug()<<ok<<binary;

    QChar b= QChar(1);
    qDebug()<<b;
    qDebug()<<b.digitValue();

    int variable =20;
    QString variableBase2 = QString::number(variable,2);
    qDebug()<<variableBase2<<variable;

    QString variableBase16 = QString::number(variableBase2.toInt(&ok,2),16);
    qDebug()<<variableBase16;


    //decimal
    float variablef =0.1241;
    QString variableBase22 = QString::number(variablef,2);
    qDebug()<<variableBase2<<variable;

    return a.exec();


}
