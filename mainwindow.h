#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QList"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_batchDeleteButton_clicked();

    void on_timeButton_clicked();

    void timerTimeout();

private:
    Ui::MainWindow *ui;
    QList<QString> fileNames;
    QList<int> deleteAtIndex;
    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    QTimer *timer;
    int currentWallpaperIndex = -1;
    void on_wallpaperButton_clicked(int buttonId);
    void addWallpaper(bool writeLog = false);
    void save();
    void load();
    void refresh();
    bool timerStart = false;
};
#endif // MAINWINDOW_H
