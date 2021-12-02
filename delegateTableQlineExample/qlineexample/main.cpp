#include <QCoreApplication>
#include <QApplication>
#include <QStandardItemModel>
#include <QTableView>

#include "mylineedit.h"
#include "SVCMNumPad/svcmnumpaddelegate.h"
#include "SVCMNumPad/SVCMNumPad.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QStandardItemModel model(4, 2);
    QTableView tableView;
    tableView.setModel(&model);

   // mylineedit delegate;
    SVCMNumPadDelegate delegate;

//    cms::SVCMNumPad HOLA;
//    HOLA.ptr_svcm_numpad_controlwindow->show();
    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 2; ++column)
        {
            QModelIndex index = model.index(row, column, QModelIndex());
            model.setData(index, QVariant((row + 1) * (column + 1)));
        }
    }
    tableView.setItemDelegateForColumn(0,new SVCMNumPadDelegate());

    tableView.setWindowTitle(QObject::tr("Spin Box Delegate"));
    tableView.show();
    return app.exec();
}
