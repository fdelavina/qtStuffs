#include "SVCMNumPadControlWindow.h"
#include "ThirdParty/NCQMLSymbols/ncqmlsymbols/quickwidget.h"
#include "libLog/Logit.h"
#include "libTutorial/TutorialDisplay.h"
#include "libUserInputAPI/UserInputAPI.h"
#include "ui_SVCMNumPadControlWindow.h"
#include <QQmlContext>
#include <QQmlEngine>
#include <QSettings>
#include <QWidget>

#include <QLineEdit>



namespace cms
{
    SVCMNumPadControlWindow::SVCMNumPadControlWindow(SVCMNumPad *manager, QWidget *parent) :
          Window(parent),
          m_numpad(manager),
          m_numpad_ui(new Ui::SVCMNumPadControlWindow),
          m_split_line_edit_text(false),
          m_p_line_edit_to_modify(nullptr),
          m_p_table_widget_to_modify(nullptr),
          m_p_table_widget_item_to_modify(nullptr)

    {
        m_numpad_ui->setupUi(this);
        m_rest_line_edit_text = "0";
        setStyle(new CMSStyle);
        init();
        hide();
        m_has_focus=false;
        emit getData();

    }

    SVCMNumPadControlWindow::~SVCMNumPadControlWindow()
    {
        delete m_numpad_ui;
        finish();
    }

    void SVCMNumPadControlWindow::init()
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::init()");

        setConfigurationWindow();
        setConnects();
    }

    void SVCMNumPadControlWindow::setConfigurationWindow()
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::setConfigurationWindow()");

    }

    void SVCMNumPadControlWindow::setConnects()
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::setConnects()");
        //General
        connect(m_numpad_ui->pbt_virt_keyb_ok, SIGNAL(clicked()), this, SLOT(okBtn()));
        connect(m_numpad_ui->pbt_virt_keyb_cancel, SIGNAL(clicked()), this, SLOT(cancelBtn()));

        connect(m_numpad_ui->pbt_num_key_0, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("0");
        });
        connect(m_numpad_ui->pbt_num_key_1, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("1");
        });
        connect(m_numpad_ui->pbt_num_key_2, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("2");
        });
        connect(m_numpad_ui->pbt_num_key_3, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("3");
        });
        connect(m_numpad_ui->pbt_num_key_4, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("4");
        });
        connect(m_numpad_ui->pbt_num_key_5, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("5");
        });
        connect(m_numpad_ui->pbt_num_key_6, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("6");
        });
        connect(m_numpad_ui->pbt_num_key_7, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("7");
        });
        connect(m_numpad_ui->pbt_num_key_8, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("8");
        });
        connect(m_numpad_ui->pbt_num_key_9, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked("9");
        });
        connect(m_numpad_ui->pbt_num_key_dot, &QPushButton::clicked, [this]() {
          onPbtNumVirtKeyClicked(".");
        });

        connect(m_numpad_ui->pbt_num_key_rm, SIGNAL(clicked()), this, SLOT(onPbtNumKeyRmClicked()));

        connect(m_numpad_ui->pbt_add, SIGNAL(clicked()), this, SLOT(onPbtAdd()));
        connect(m_numpad_ui->pbt_rest, SIGNAL(clicked()), this, SLOT(onPbtRest()));

    }
//--------------------------

    void SVCMNumPadControlWindow::setRestLineEditText(const QString &restLineEditText)
    {
        m_rest_line_edit_text = restLineEditText;
    }

    QString SVCMNumPadControlWindow::editingField() const
    {
        return m_p_editing_field;
    }

    void SVCMNumPadControlWindow::setEditingField(QString editingField)
    {
        m_p_editing_field = editingField;
    }

    QTableWidgetItem *SVCMNumPadControlWindow::tableWidgetItemToModify() const
    {
        return m_p_table_widget_item_to_modify;
    }

    void SVCMNumPadControlWindow::setTableWidgetToModify(QTableWidget *tbwToModify, int row, int col)
    {
        m_p_table_widget_to_modify = tbwToModify;
        m_p_table_widget_item_to_modify = tbwToModify->item(row, col);
    }

    void SVCMNumPadControlWindow::setSplitLineEditText(bool splitLineEditText)
    {
        m_split_line_edit_text = splitLineEditText;
    }

    QLineEdit *SVCMNumPadControlWindow::lineEditToModify() const
    {
        return m_p_line_edit_to_modify;
    }

    void SVCMNumPadControlWindow::setLineEditToModify(QLineEdit *p_line_edit_to_modify)
    {
        m_p_line_edit_to_modify = p_line_edit_to_modify;
    }

    void SVCMNumPadControlWindow::onPbtNumVirtKeyClicked(QString input)
    {
        QString newText = "";
        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            QString currentText = m_numpad_ui->lne_editing_field->text();
            QString oldText = currentText;
            QString splitText0;
            QString splitText1;
            if (m_split_line_edit_text)
            {
                QStringList textList = currentText.split(" ");
                splitText0 = textList[0];

                if (textList.size() > 1)
                {
                    splitText1 = textList[1];
                }
                else
                {
                    splitText1 = m_rest_line_edit_text;
                }

                currentText = splitText0;
            }

            if(currentText.contains(".", Qt::CaseInsensitive) && input == ".")//it is not possible to add 2 points
            {
                newText = currentText;
            }
            else
            {
                newText = currentText + input;
            }

            if (m_first_edition)
            {
                newText = input;
            }

            if (m_split_line_edit_text)
            {
                newText.append(" ");
                newText.append(splitText1);
            }
            m_numpad_ui->lne_editing_field->setText(newText);
            if (!m_numpad_ui->lne_editing_field->hasAcceptableInput())
            {
                m_numpad_ui->lne_editing_field->setText(oldText);
            }
            else
            {
                m_first_edition = false;
            }
        }
        else if (m_p_table_widget_item_to_modify != nullptr)
        {
            QString oldText = m_p_table_widget_item_to_modify->text();
            if(oldText.contains(".", Qt::CaseInsensitive) && input == ".")//it is not possible to add 2 points
            {
                newText = oldText;
            }
            else
            {
                newText = oldText + input;
            }

            if (m_first_edition)
            {
                newText = input;
            }
            m_p_table_widget_item_to_modify->setText(newText);
            m_first_edition = false;
        }
    }

    void SVCMNumPadControlWindow::onPbtNumKeyRmClicked()
    {
        m_first_edition = false;
        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            QString text = m_numpad_ui->lne_editing_field->text();
            QString splitText1;
            if (m_split_line_edit_text)
            {
                QStringList textList = text.split(" ");
                text = textList[0];

                if (textList.size() > 1)
                {
                    splitText1 = textList[1];
                }
                else
                {
                    splitText1 = m_rest_line_edit_text;
                }
            }

            if(text.size()>1)
            {
                text.chop(1);
            }
            else
            {
                text.setNum(0);
            }

            if (m_split_line_edit_text)
            {
                text.append(" ");
                text.append(splitText1);
            }

            m_numpad_ui->lne_editing_field->setText(text);
        }
        else if (m_p_table_widget_item_to_modify != nullptr)
        {
            QString text = m_p_table_widget_item_to_modify->text();
            text.chop(1);
            m_p_table_widget_item_to_modify->setText(text);
        }
    }
    void SVCMNumPadControlWindow::onPbtAdd()
    {
        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            QString newText = "";
            QString currentText = m_numpad_ui->lne_editing_field->text();
            if(!currentText.contains(".", Qt::CaseInsensitive))
            {
                double newValue = currentText.toDouble() ;
                ++ newValue ;
                newText = QString::number(newValue);
            }
            else
            {
                double value = currentText.toDouble();
                double integer = 0;
                double decimal = modf(value, &integer);
                QString temp1 = QString::number(decimal);
                QStringList decimalList = temp1.split(".");
                int temp2 = decimalList[1].toInt() +1;
                if(QString::number(temp2).size() == QString::number(decimalList[1].toInt()).size())
                {
                    QString temp3 = "0.";
                    temp3.append(QString::number(temp2));
                    value = integer + temp3.toDouble();
                }
                else
                {
                    value = integer + 1;
                }
                newText.append(QString::number(value));
            }
            m_numpad_ui->lne_editing_field->setText(newText);
        }
    }
    void SVCMNumPadControlWindow::onPbtRest()
    {
        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            QString currentText = m_numpad_ui->lne_editing_field->text();
            QString newText = "";
            if(!currentText.contains(".", Qt::CaseInsensitive))
            {
                if(currentText.toDouble() >= 1)
                {
                    double newValue = currentText.toDouble() ;
                    -- newValue ;
                    newText = QString::number(newValue);
                }
                else
                {
                    newText.setNum(0);
                }
            }
            else
            {
                double value = currentText.toDouble();
                double integer = 0;
                double decimal = modf(value, &integer);
                QString temp1 = QString::number(decimal);
                QStringList decimalList = temp1.split(".");
                int temp2 = decimalList[1].toInt() - 1;
                if(QString::number(temp2).size() == QString::number(decimalList[1].toInt()).size() && temp2 >= 1)
                {
                    QString temp3 = "0.";
                    temp3.append(QString::number(temp2));
                    value = integer + temp3.toDouble();
                }
                else
                {
                    if(integer >= 1)
                    {
                        value = integer - 1;
                    }
                    else
                    {
                        value = 0;
                    }
                }
                newText.append(QString::number(value));
            }
            m_numpad_ui->lne_editing_field->setText(newText);
        }
    }


    void SVCMNumPadControlWindow::cancelBtn()
    {
        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            m_numpad_ui->lne_editing_field->setText(m_old_edit_text);
            m_numpad_ui->lne_editing_field->clearFocus();
        }
        else if (m_p_table_widget_item_to_modify != nullptr)
        {
            m_p_table_widget_item_to_modify->setText(m_old_edit_text);
            m_p_table_widget_to_modify->clearFocus();
        }
        clearFocus();
    }

    void SVCMNumPadControlWindow::okBtn()
    {
        m_has_focus=false;

        if (m_numpad_ui->lne_editing_field->text() != nullptr)
        {
            QString text = m_numpad_ui->lne_editing_field->text();

            QString splitText1;
            if (m_split_line_edit_text)
            {
                QStringList textList = text.split(" ");
                text = textList[0];

                if (textList.size() > 1)
                {
                    splitText1 = textList[1];
                }
                else
                {
                    splitText1 = m_rest_line_edit_text;
                }
            }

            int sizeText = text.size();
            if ((sizeText > 0) && (text.at(sizeText - 1) == '.'))
            {
                text.append("0");

                if (m_split_line_edit_text)
                {
                    text.append(" ");
                    text.append(splitText1);
                }

                m_numpad_ui->lne_editing_field->setText(text);
            }

            m_numpad_ui->lne_editing_field->clearFocus();
            emit m_numpad_ui->lne_editing_field->editingFinished();
        }
        else if (m_p_table_widget_item_to_modify != nullptr)
        {
            m_p_table_widget_to_modify->clearFocus();
        }
        emit sendDataToQLine(m_numpad_ui->lne_editing_field->text());
        clearFocus();
        closeWindow();
    }
    void SVCMNumPadControlWindow::closeWindow()
    {
        m_p_line_edit_to_modify = nullptr;
        m_p_table_widget_to_modify = nullptr;
        m_p_table_widget_item_to_modify = nullptr;
        m_has_focus=false;
        hide();
        finish();
    }


    void SVCMNumPadControlWindow::setStyle(CMSStyle *style)
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::setStyle()");
        this->setStyleSheet(style->loadStyleSheet());
    }


    void SVCMNumPadControlWindow::finish()
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::finish()");
        close();
    }

    void SVCMNumPadControlWindow::showWindow(const double &value)
    {
        SLog.msg(LogPriority::LOG_DEBUG, "SVCMNumPadControlWindow::showWindow()");
        forceOpen();
        setFocus();
        m_numpad_ui->lne_editing_field->setText(QString::number(value));
        m_has_focus = true;
    }

    void SVCMNumPadControlWindow::focusInEvent(QFocusEvent *event){
        SLog << Q_FUNC_INFO << "FocusInEvent -- enter" << LogPriority::INFO;
        event->accept();
        m_has_focus=true;
    }

    void SVCMNumPadControlWindow::focusOutEvent(QFocusEvent *event){
        SLog << Q_FUNC_INFO << "FocusOutEvent --enter" << LogPriority::INFO;
        event->accept();
        m_has_focus=false;
        emit tryClose();
    }

    bool SVCMNumPadControlWindow::hasFocus(){
        return m_has_focus;
    }
}  // namespace cms




