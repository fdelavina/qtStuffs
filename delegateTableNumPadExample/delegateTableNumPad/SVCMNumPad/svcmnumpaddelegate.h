#ifndef SVCMNUMPADDELEGATE_H
#define SVCMNUMPADDELEGATE_H

#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include "SVCM/SVCMNumPad/QLineEditNumPad.h"
#include "SVCM/SVCMNumPad/SVCMNumPad.h"
class SVCMNumPadDelegate :public QStyledItemDelegate
{
    Q_OBJECT
public:
    SVCMNumPadDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                        const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const override;

private:


};

#endif // SVCMNUMPADDELEGATE_H
