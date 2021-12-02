#include "QLineEditNumPad.h"

#include "SVCMNumPad.h"
#include "QFocusEvent"
#include <iostream>
using namespace std;
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
    m_num_pad->closeWindow();
    //e->accept();
}


void QLineEditNumPad::focusInEvent(QFocusEvent *e)
{
    //QLineEdit::focusInEvent(e);
    if (true)
    {
        this->setFocus();

        m_num_pad->show(text().toDouble());
        //e->ignore();

        m_has_focus=true;
    }
}

void QLineEditNumPad::focusOutEvent(QFocusEvent *e)
{

    if (true)
    {
        m_has_focus=false;
        tryClose(false);
    }
}

void QLineEditNumPad::tryClose(bool externalClose)
{

    if (!m_num_pad->hasFocus() && !m_has_focus )
    {
        if (externalClose)
        {
            cout<<"se cierra el focus"<<endl;
            clearFocus();
        }
        cout<<"Se fuerza el cierre de la ventana"<<endl;
        forceClose();
    }
    else
    {
        cout<<"no se cierra el focus"<<endl;
    }

}

void QLineEditNumPad::updateText(const QString &value)
{
    setText(value);
}


