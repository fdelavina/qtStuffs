#include "svcmnumpaddelegate.h"


SVCMNumPadDelegate::SVCMNumPadDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *SVCMNumPadDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const
{

    QLineEditNumPad *editor = new QLineEditNumPad(parent);
    editor->setFrame(false);
    //editor->raise();

    editor->setDisabled(false);

    return editor;
}

void SVCMNumPadDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEditNumPad* spinBox = static_cast<QLineEditNumPad*>(editor);
    spinBox->setText(value);
}
#include <chrono>
#include <thread>
void SVCMNumPadDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    QLineEditNumPad* spinBox = static_cast<QLineEditNumPad*>(editor);
    QString value = spinBox->text();
    model->setData(index, value, Qt::EditRole);


}

void SVCMNumPadDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   // editor->setGeometry(option.rect);
}
