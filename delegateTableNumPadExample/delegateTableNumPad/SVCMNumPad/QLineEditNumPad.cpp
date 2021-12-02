#include "QLineEditNumPad.h"
#include "libLog/Logit.h"
#include "SVCMNumPad.h"
#include "QFocusEvent"

QLineEditNumPad::QLineEditNumPad(QWidget *parent):QLineEdit(parent)
{
    m_num_pad = new cms::SVCMNumPad();
    m_has_focus=false;


    connect(m_num_pad,SIGNAL(tryClose()),this,SLOT(tryClose()));
    connect(m_num_pad, SIGNAL(sendDataToQLine(QString)), this, SLOT(updateText(QString)));
}

QLineEditNumPad::~QLineEditNumPad()
{
    delete  m_num_pad;
}

void QLineEditNumPad::forceClose()
{
    SLog << Q_FUNC_INFO << "Forzado cerrar ventana" << LogPriority::INFO;
    m_num_pad->closeWindow();
    //e->accept();
}


void QLineEditNumPad::focusInEvent(QFocusEvent *e)
{
    SLog << Q_FUNC_INFO << "FocusIn NumPad" << LogPriority::INFO;
    //QLineEdit::focusInEvent(e);
    if (m_num_pad->m_activateNumPad)
    {
        m_num_pad->show(text().toDouble());
        //e->ignore();
        m_has_focus=true;
    }
}

void QLineEditNumPad::focusOutEvent(QFocusEvent *e)
{
    SLog << Q_FUNC_INFO << "FocusOut NumPad" << LogPriority::INFO;

    if (m_num_pad->m_activateNumPad)
    {
        m_has_focus=false;
        tryClose(false);
    }
}

void QLineEditNumPad::tryClose(bool externalClose)
{
    SLog << Q_FUNC_INFO << "tryClose, num_pad focus = " << m_num_pad->hasFocus()
         << ", focus = " << m_has_focus << LogPriority::INFO;
    if (!m_num_pad->hasFocus() && !m_has_focus)
    {
        if (externalClose)
        {
            clearFocus();
        }
        forceClose();
    }
}

void QLineEditNumPad::updateText(const QString &value)
{
    SLog << Q_FUNC_INFO << " Texto actualizado, valor dato: "<< value << LogPriority::INFO;
    setText(value);
}


