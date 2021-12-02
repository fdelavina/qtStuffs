#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QLineEdit>
class mylineedit : public QStyledItemDelegate
{
    Q_OBJECT
public:
    mylineedit(QObject* parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // MYLINEEDIT_H

