#ifndef _SVCMNUMPAD_H_
#define _SVCMNUMPAD_H_

#include <QObject>
#include <QMap>
#include <QTimer>
#include <QTranslator>


#include <memory>

#include <SVCMNumPad/SVCMNumPadControlWindow.h>

#include <QSettings>
#include <QTimer>


namespace cms
{
//    class SVCMHmiFavConnector;
//    class SVCMScpmFavConnector;
    class SVCMNumPadControlWindow;


    class SVCMNumPad : public QObject
    {
        Q_OBJECT

    public:
        SVCMNumPad();
        ~SVCMNumPad();
        std::unique_ptr<cms::SVCMNumPadControlWindow> ptr_svcm_numpad_controlwindow;
        void initialize();
        void closeWindow();
        void show(const double &value);
        bool isHidden();
        bool hasFocus();
        QString dataToQLine;
        bool m_activateNumPad;

    private:

        void readConfig(std::string config_filepath="");


    private slots:

    signals:
        void tryClose();
        void sendDataToQLine(const QString &value);

    };
}  // namespace cms

#endif  //
