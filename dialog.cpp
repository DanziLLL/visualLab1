#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_addBtn_clicked()
{
    MainWindow *myParent= qobject_cast<MainWindow *>(parent());
    if ((!ui->radioR1->isChecked()) && !ui->radioR2->isChecked()) {
        QMessageBox::critical(this, "Error", "Не выбран раздел, в который будет добавлена запись");
        return;
    }
    if (ui->addLine->text() == "") {
        QMessageBox::critical(this, "Error", "Строка ввода пуста");
        return;
    }
    if (ui->radioR1->isChecked()) {
        myParent->R1.push_back(ui->addLine->text());
    }
    else if (ui->radioR2->isChecked()) {
        myParent->R2.push_back(ui->addLine->text());
    }
    this->destroy();
    myParent->reloadLists();
    return;
}

void Dialog::on_cancelBtn_clicked()
{
    this->destroy();
    return;
}
