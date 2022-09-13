#include "batchdeletedialog.h"
#include "ui_batchdeletedialog.h"
#include <string>

BatchDeleteDialog::BatchDeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BatchDeleteDialog)
{
    ui->setupUi(this);

}

BatchDeleteDialog::~BatchDeleteDialog()
{
    delete ui;
}

QList<int> parseString(std::string textToParse){
    std::string temp;
   textToParse.erase(remove_if(textToParse.begin(), textToParse.end(), ::isspace), textToParse.end());

   QList<int> toDelete;
   bool repeat = false;
   int min, max;

   for(int i = 0; i <= textToParse.length(); i++){
       if(textToParse[i] == '-'){
           repeat = true;
           min = stoi(temp);
           temp = "";
           continue;
       }
       if(textToParse[i] != ','){
           temp += textToParse[i];
       }
       if (textToParse[i] == ','  || i == textToParse.length()){
           if(repeat == true){
               repeat = false;
               max = stoi(temp);
               temp = "";
               for(int j = min; j <= max; j++){
                   toDelete.append(j);
               }
               continue;
           }
           toDelete.append(stoi(temp));
           temp = "";
       }
   }

   return toDelete;
}

void BatchDeleteDialog::on_batchDeleteConfirmButton_clicked()
{
    std::string textToParse = ui->batchDeleteLineEdit->text().toStdString();
    deleteAtIndex = parseString(textToParse);
    this->close();
}

QList<int> BatchDeleteDialog::getIndexToDelete(){
    return deleteAtIndex;
}

