#ifndef SVCMNUMPADCONTROLWINDOW_H
#define SVCMNUMPADCONTROLWINDOW_H

#include "SVCMNumPad.h"

#include <QItemSelection>
#include <QMap>
#include <QWidget>

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QObject>

namespace Ui
{
    class SVCMNumPadControlWindow;
}

class QuickWidget;
class QSettings;

namespace cms
{
    class SVCMNumPadControlWindow;
    class SVCMNumPad;

    class SVCMNumPadControlWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit SVCMNumPadControlWindow(SVCMNumPad *manager ,QWidget *parent = nullptr);
        ~SVCMNumPadControlWindow();

        void finish();
        void showWindow(const double &value);
        void init();

        QString editingField() const;
        void setEditingField(QString editingField);
        QLineEdit *lineEditToModify() const;
        void setLineEditToModify(QLineEdit *lineEditToModify);
        QTableWidgetItem *tableWidgetItemToModify() const;
        void setTableWidgetToModify(QTableWidget *tbwToModify, int row, int col);
        void setSplitLineEditText (bool splitLineEditText);
        void setRestLineEditText(const QString &restLineEditText);

    private slots:

       // void closeCB();



    private:
        void setConfigurationWindow();

        void setConnects();
        void closeWindowByTime();

        Ui::SVCMNumPadControlWindow *m_numpad_ui;
        SVCMNumPad *m_numpad;
        QSettings *paletteIni;
        QPalette dayPalette;
        QPalette nightPalette;
        QString m_p_editing_field;
        QLineEdit *m_p_line_edit_to_modify;
        QTableWidget *m_p_table_widget_to_modify;
        QTableWidgetItem *m_p_table_widget_item_to_modify;
        QString m_old_edit_text;
        bool m_first_edition;
        bool m_split_line_edit_text;
        QString m_rest_line_edit_text;
        bool m_has_focus;

     public slots:
        void cancelBtn();
        void closeWindow();

        void onPbtNumVirtKeyClicked(QString input);
        void onPbtNumKeyRmClicked();
        void okBtn();
        bool hasFocus();
        void focusInEvent(QFocusEvent *event);
        void focusOutEvent(QFocusEvent *event);

        void onPbtAdd();
        void onPbtRest();

    signals:
        void tryClose();
        double getData();
        void sendDataToQLine(const QString &value);
    };
}

#endif
