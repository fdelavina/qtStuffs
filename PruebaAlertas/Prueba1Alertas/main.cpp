#include <iostream>
#include <QSettings>
using namespace std;
#include <QDebug>
#include <QtWidgets>
#include <QTranslator>

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
int main()
{
    int isTruncated;
    const QString K_SVCM_USV_FILENAME = QString("../MensajesDisponibilidad.ini");

    QSettings m_qsettings(K_SVCM_USV_FILENAME, QSettings::IniFormat);
    //m_qsettings.setIniCodec("UTF-8"); //para las tildes
    QStringList keys = m_qsettings.allKeys();

    QMap<uint, QString> mapCodigosTexto;

    cout<<keys[keys.length()-1].toStdString()<<endl;
    for(int i=0;i<keys.length();++i)
    {
        std::string codigo = keys[i].toStdString();

        std::size_t pos = codigo.find("/");

        std::string numero = codigo.substr (pos+1);

        if ( is_number(numero))
        {
            int number = stoi(numero);
            mapCodigosTexto[number]=  m_qsettings.value( QString::fromUtf8( codigo.c_str() ) ).toString().toUtf8();
        }
        else
        {
            isTruncated = m_qsettings.value( QString::fromUtf8( codigo.c_str() ) ).toInt();

            cout<<numero<<endl;
            cout<<isTruncated<<endl;
        }



       // cout << a.toStdString() <<endl;
    }
    string a = mapCodigosTexto[111].toStdString();
    if (mapCodigosTexto[101]==NULL)
    {
        cout<<"No hay nadie"<<endl;
    }
    else
    {
        cout<<"Si hay nadie"<<endl;
    }

    return 0;
}
