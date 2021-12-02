
#include <QApplication>

#include "SVCMNumPad.h"
#include <QDateTime>
#include <QApplication>
#include <QFocusEvent>
#include <iostream>
using namespace std;
namespace cms
{
    const std::string K_DEFAULT_CONFIG_FILENAME = "NumPad/Config.ini";
    const QString K_ACTIVATE_NUMPAD = "USV_PAD/ActivateNumPad";

    SVCMNumPad::SVCMNumPad()
         :ptr_svcm_numpad_controlwindow(nullptr)
    {
        dataToQLine="";
        readConfig();
        if(true)
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
            //ptr_svcm_numpad_controlwindow->show();
            ptr_svcm_numpad_controlwindow->focusInEvent(new QFocusEvent(QEvent::FocusIn));
            connect(ptr_svcm_numpad_controlwindow.get(), SIGNAL(tryClose()), this, SIGNAL(tryClose()));
        }
    }

    void SVCMNumPad::closeWindow()
    {

        connect(ptr_svcm_numpad_controlwindow.get(), SIGNAL(sendDataToQLine(QString)),
                this, SIGNAL(sendDataToQLine(QString)));
        ptr_svcm_numpad_controlwindow->closeWindow();
    }

    void SVCMNumPad::show(const double &value)
    {
        if (true)
        {
            ptr_svcm_numpad_controlwindow->showWindow(value);
        }
    }

    bool SVCMNumPad::isHidden()
    {
        return false;
    }

    bool SVCMNumPad::hasFocus()
    {
        return ptr_svcm_numpad_controlwindow->hasFocus();
    }

    void SVCMNumPad::readConfig(std::string config_filepath)
    {


    }
}
