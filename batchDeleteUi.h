#ifndef BATCHDELETEUI_H
#define BATCHDELETEUI_H

#include <QDialog>
#include "./ui_batchDeleteDialog.h"

#endif // BATCHDELETEUI_H


class batchDeleteUi : public QDialog, public Ui::batchDeleteDialog {
    Q_OBJECT

public:
    batchDeleteUi( QWidget * parent = 0);
};
