#include <libLog/Logit.h>
#include "libPubSubComm/RemoteComm.h"
#include "libUserInputAPI/UserInputAPI.h"
#include "libUserInputAPI/UserInputActions.h"
#include "libActionHandler/ActionHandler.h"
#include "libDataManagerDB/NotifyDB.h"
#include <libLowLevel/StrHash.h>
#include <libRoleAPI/RoleAPI.h>
#include <libCMSStyle/CMSStyle.h>
#include <QApplication>
#include <libApplicationUtil/PathInfo.h>
#include "SVCMNumPad.h"
#include <QDateTime>
#include <QApplication>
#include <QFocusEvent>

namespace cms
{
    const std::string K_DEFAULT_CONFIG_FILENAME = "NumPad/Config.ini";
    const QString K_ACTIVATE_NUMPAD = "USV_PAD/ActivateNumPad";

    SVCMNumPad::SVCMNumPad()
         :ptr_svcm_numpad_controlwindow(nullptr),
          m_style(new CMSStyle())
    {
        dataToQLine="";
        readConfig();
        if(m_activateNumPad)
        {
            initialize();
        }
    }

    SVCMNumPad::~SVCMNumPad()
    {
        closeWindow();
    }

    void SVCMNumPad::initialize()
    {
        if (ptr_svcm_numpad_controlwindow == nullptr)
        {
            ptr_svcm_numpad_controlwindow.reset(new SVCMNumPadControlWindow(this));
        }

        if (ptr_svcm_numpad_controlwindow)
        {
            ptr_svcm_numpad_controlwindow->showWindow(0);
            ptr_svcm_numpad_controlwindow->focusInEvent(new QFocusEvent(QEvent::FocusIn));
            connect(ptr_svcm_numpad_controlwindow.get(), SIGNAL(tryClose()), this, SIGNAL(tryClose()));
        }
    }

    void SVCMNumPad::closeWindow()
    {
        SLog << Q_FUNC_INFO << "Cerrar Ventana teclado " << LogPriority::INFO;

        connect(ptr_svcm_numpad_controlwindow.get(), SIGNAL(sendDataToQLine(QString)),
                this, SIGNAL(sendDataToQLine(QString)));
        ptr_svcm_numpad_controlwindow->closeWindow();
    }

    void SVCMNumPad::show(const double &value)
    {
        SLog << Q_FUNC_INFO << "Abrir Ventana teclado" << LogPriority::INFO;
        if (m_activateNumPad)
        {
            ptr_svcm_numpad_controlwindow->showWindow(value);
        }
    }

    bool SVCMNumPad::isHidden()
    {
        return ptr_svcm_numpad_controlwindow->isHidden();
    }

    bool SVCMNumPad::hasFocus()
    {
        return ptr_svcm_numpad_controlwindow->hasFocus();
    }

    void SVCMNumPad::readConfig(std::string config_filepath)
    {
        SLog << Q_FUNC_INFO << " - enter " << LogPriority::LOG_DEBUG;
        m_activateNumPad = false;
        if (config_filepath.empty())
        {
            config_filepath = PathInfo::shipConfigDir() + "/" + K_DEFAULT_CONFIG_FILENAME;
        }

        QFile ini_file(QString::fromStdString(config_filepath));
        if (!ini_file.exists())
        {
            SLog << Q_FUNC_INFO << " Configuration file '" << config_filepath
                 << "' does not exist, setting configuration to default..."
                 << LogPriority::CRITICAL;
        }
        else
        {
            QSettings settings(ini_file.fileName(), QSettings::IniFormat);

            if (!settings.contains(K_ACTIVATE_NUMPAD))
            {
                SLog << Q_FUNC_INFO << " Configuration file '" << config_filepath
                     << "' does not contains timer_timeout, setting configuration to default..."
                     << LogPriority::CRITICAL;
            }
            else
            {
                // Read ActivateNumPad
                m_activateNumPad = settings.value(K_ACTIVATE_NUMPAD).toBool();
                SLog << Q_FUNC_INFO << "ActivateNumPad = " << m_activateNumPad << LogPriority::INFO;
            }
        }
    }
}
