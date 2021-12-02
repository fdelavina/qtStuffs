#include "mylineedit.h"


mylineedit::mylineedit(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *mylineedit::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setFrame(false);
    //editor->setReadOnly(true);
    return editor;
}

void mylineedit::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit* spinBox = static_cast<QLineEdit*>(editor);
    spinBox->setText(value);
}

void mylineedit::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QLineEdit* spinBox = static_cast<QLineEdit*>(editor);
    QString value = spinBox->text();
    model->setData(index, value, Qt::EditRole);
}

void mylineedit::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
