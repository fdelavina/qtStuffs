#ifndef QLINEEDITNUMPAD_H
#define QLINEEDITNUMPAD_H

#include <QLineEdit>
#include <SVCMNumPad/SVCMNumPad.h>

class QLineEditNumPad : public QLineEdit
{
    Q_OBJECT
public:
    QLineEditNumPad(QWidget *parent =nullptr);
    ~QLineEditNumPad();

private:
    cms::SVCMNumPad *m_num_pad;
    bool m_has_focus;
    void forceClose();


protected:
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);

signals:

public slots:
    void tryClose(bool externalClose = true);
    void updateText(const QString &value);

};

#endif
