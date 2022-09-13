#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QList"
#include "QFileDialog"
#include <windows.h>
#include <QFile>
#include "batchdeletedialog.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);


        ui->scrollArea->setWidget(widget);

        widget->setLayout( layout );

        load();
        addWallpaper(true);
        ui->textEdit->insertPlainText("Program started \n");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh(){
    delete widget;
    widget = new QWidget();
    ui->scrollArea->setWidget(widget);
    layout = new QGridLayout();
    widget->setLayout(layout);
}


void MainWindow::on_addButton_clicked()
{
    QString selfilter = tr("Image (*.jpg *.jpeg *.png)");
    QList tempFileNames = QFileDialog::getOpenFileNames(this, tr("Select Iamge"), QDir::homePath(),
                                              tr("All files (*.*);;Image (*.jpg *.jpeg *.png)"),
                                              &selfilter );
    foreach(QString tempFileName, tempFileNames){
        fileNames.append(tempFileName);
    }
    refresh();
    addWallpaper(true);
    save();
}

void MainWindow::addWallpaper(bool writeLog){
    int rowIndex = 0;
    int columnIndex = 0;
    int maxColumnIndex = 5;
    int buttonId = 0;
    QSize buttonSize(160,90);
    foreach(QString filename, fileNames){
        QPushButton *button = new QPushButton( QString( "%1" ).arg(buttonId) );
        button->setFixedSize(buttonSize);
        button->setStyleSheet(QString("QPushButton{ border-image: url('%1') 0 0 0 0 stretch stretch}").arg(filename));
        connect(button, &QPushButton::clicked, this,  [this, buttonId]
        {
            on_wallpaperButton_clicked(buttonId);
        });
        layout->addWidget(button, rowIndex, columnIndex);
        columnIndex++;
        if(columnIndex >= maxColumnIndex){
            rowIndex++;
            columnIndex = 0;
        }
        buttonId++;
        if(writeLog){
            ui->textEdit->insertPlainText("Loaded " + filename + "\n");
        }
    }
}

void MainWindow::save(){
    QString saveFileName = "SavedWallpaper.sav";
    QFile file(saveFileName);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        foreach(QString wallpaperPath , fileNames){
            out << wallpaperPath + "\n";
        }
    }
    file.close();
}

void MainWindow::load(){
    QString loadFileName = "SavedWallpaper.sav";
    if(!QFile::exists(loadFileName)){
            return;
    }
    QFile file(loadFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream in(&file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          fileNames.append(line);
       }
       file.close();
    }
}

void setWallpaper(std::string path) {
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}

void MainWindow::on_wallpaperButton_clicked(int buttonId){
     QString wallpaperPath = fileNames[buttonId];
     currentWallpaperIndex = buttonId;
     setWallpaper(wallpaperPath.toStdString());
     ui->textEdit->insertPlainText(QString("Wallpaper changed to : %1 \n").arg(wallpaperPath));
}


void MainWindow::on_deleteButton_clicked()
{
    if(currentWallpaperIndex > 0){
        ui->textEdit->insertPlainText(QString("Successfully removed %1 from Wallpaper List \n").arg(fileNames[currentWallpaperIndex]));
        fileNames.removeAt(currentWallpaperIndex);
        currentWallpaperIndex = -1;
        refresh();
        addWallpaper(false);
        save();
    }
    else {
        ui->textEdit->insertPlainText("Please select wallpaper to delete \n");
    }
}

void MainWindow::on_batchDeleteButton_clicked()
{
    BatchDeleteDialog batchDeleteDialog;
    batchDeleteDialog.setModal(true);
    batchDeleteDialog.exec();
    deleteAtIndex = batchDeleteDialog.getIndexToDelete();
    int k = 0;
    for(int i = 0; i < deleteAtIndex.length(); i++) {
        int j = deleteAtIndex[i] - k;
        ui->textEdit->insertPlainText(QString("Successfully removed %1 from Wallpaper List \n").arg(fileNames[j]));
        fileNames.removeAt(j);
        k++;
    }

    refresh();
    addWallpaper(false);
    save();
}

void MainWindow::on_timeButton_clicked()
{
    timerStart = !timerStart;
    if(timerStart == true){
        QTime endTime = ui->timeEdit->time();
        QString endTimeString = endTime.toString();
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
        ui->timeEdit->setEnabled(false);
        ui->timeButton->setText("Stop Timer");
        uint minute = endTime.minute();
        uint second = endTime.second();
        uint msec = (minute * 60000) + (second * 1000);
        ui->textEdit->insertPlainText(QString("Timer started for: %1 (%2 ms) \n").arg(endTimeString).arg(msec));
        timer->start(msec);
    }else{
        delete timer;
        ui->timeEdit->setEnabled(true);
        ui->timeButton->setText("Start Timer");
        ui->textEdit->insertPlainText("Timer stopped \n");
    }
}

int randomNumber(int min, int max){
    srand(time(NULL));
    int randomInteger = min + rand() % max;
    return randomInteger;
}

void MainWindow::timerTimeout(){
    int randomWallpaperIndex = randomNumber(0, fileNames.length());
    QString wallpaperPath = fileNames[randomWallpaperIndex];
    currentWallpaperIndex = randomWallpaperIndex;
    setWallpaper(wallpaperPath.toStdString());
    ui->textEdit->insertPlainText(QString("Wallpaper changed to : %1 \n").arg(wallpaperPath));
}

