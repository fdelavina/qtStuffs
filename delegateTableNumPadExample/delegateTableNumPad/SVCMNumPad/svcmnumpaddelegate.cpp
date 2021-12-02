#include "svcmnumpaddelegate.h"

#include <QFileDialog>
SVCMNumPadDelegate::SVCMNumPadDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget *SVCMNumPadDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEditNumPad *editor = new QLineEditNumPad();
    return editor;
}

void SVCMNumPadDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QLineEditNumPad *NumPadDelegate = static_cast<QLineEditNumPad*>(editor);
    //NumPadDelegate->setValue(value);
    NumPadDelegate->updateText("0.1234");
}
//#include <unistd.h>
void SVCMNumPadDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
   QLineEditNumPad *NumPadDelegate = static_cast<QLineEditNumPad*>(editor);
   //NumPadDelegate->interpretText();

    //int value = NumPadDelegate->value();
   //sleep(10000);
   int value = 11;

   model->setData(index,value,Qt::EditRole);

}

void SVCMNumPadDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //editor->setGeometry(option.rect);
}
