#ifndef BATCHDELETEDIALOG_H
#define BATCHDELETEDIALOG_H

#include <QDialog>

namespace Ui {
class BatchDeleteDialog;
}

class BatchDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BatchDeleteDialog(QWidget *parent = nullptr);
    ~BatchDeleteDialog();
    QList<int> getIndexToDelete();

private slots:
    void on_batchDeleteConfirmButton_clicked();

private:
    Ui::BatchDeleteDialog *ui;
    QList<int> deleteAtIndex;
};

#endif // BATCHDELETEDIALOG_H
