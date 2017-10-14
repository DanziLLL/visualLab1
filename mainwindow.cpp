#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::multiSort(int i, QStringList list)
{
    int j, k;
    int step = 1;
    bool flag;
    QStringList res;
    switch(i) {
    case 0: { //length asc
        int min = 65535, max = -1;
        for (j = 0; j < list.size(); j++) {
            if (list.value(j).length() < min) {
                min = list.value(j).length();
            }
            if (list.value(j).length() > max) {
                max = list.value(j).length();
            }
        }
        for (j = min; j <= max; j++) {
            for (k = 0; k < list.size(); k++) {
                if (list.value(k).length() == j) {
                    res.push_back(list.value(k));
                }
            }
        }
        return res;
    }
    case 1: { //length desc
        int min = 65535, max = -1;
        for (j = 0; j < list.size(); j++) {
            if (list.value(j).length() < min) {
                min = list.value(j).length();
            }
            if (list.value(j).length() > max) {
                max = list.value(j).length();
            }
        }
        for (j = max; j >= min; j--) {
            for (k = 0; k < list.size(); k++) {
                if (list.value(k).length() == j) {
                    res.push_back(list.value(k));
                }
            }
        }
        return res;
    }
    case 2: { //alphabet asc
        res.push_back(list.value(0));
        for (j = 1; j < list.size(); j++) {
            flag = 0;
            step = 1;
            res.push_back(list.value(j));
            while (!flag) {
                if ((step <= j) && (QString::compare(res.at(j - step), res.at(j - step + 1)) > 0)){
                    res.swap(j - step, j - step + 1);
                    step++;
                }
                else {
                    flag = 1;
                }
            }
        }
        return res;
    }
    case 3: { //alphabet desc
        res.push_back(list.value(0));
        for (j = 1; j < list.size(); j++) {
            res.push_back(list.value(j));
            flag = 0;
            step = 1;
            while (!flag) {
                if ((step <= j) && (QString::compare(res.at(j - step), res.at(j - step + 1)) < 0)) {
                    res.swap(j - step, j - step + 1);
                    step++;
                }
                else {
                    flag = 1;
                }
            }
        }
        return res;
    }
    }
}

void MainWindow::on_btnClearR1_clicked()
{
    ui->listR1->clear();
    R1.clear();
}

void MainWindow::on_btnClearR2_clicked()
{
    ui->listR2->clear();
    R2.clear();
}

void MainWindow::on_btnSortR1_clicked()
{
    int index = ui->comboR1->currentIndex();
    ui->listR1->clear();
    R1 = multiSort(index, R1);
    ui->listR1->addItems(R1);
}

void MainWindow::on_btnSortR2_clicked()
{
    int index = ui->comboR1->currentIndex();
    ui->listR2->clear();
    R2 = multiSort(index, R2);
    ui->listR2->addItems(R2);
}

void MainWindow::on_btnExit_clicked()
{
    if (file->isOpen())
        file->close();
    exit(0);
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this);
    file = new QFile(fileName);
    file->open(QIODevice::ReadOnly);
    ui->showText->setText(file->readAll());
}

void MainWindow::on_actionSave_triggered()
{
    fileName = QFileDialog::getSaveFileName(this);
    file = new QFile(fileName);
    file->open(QIODevice::ReadWrite);
    QStringList::const_iterator it;
    QTextStream stream(file);
    for (it = R2.begin(); it != R2.end(); ++it) {
        stream << *it << endl;
    }
}

void MainWindow::on_actionExit_triggered()
{
    if (file->isOpen())
        file->close();
    exit(0);
}

void MainWindow::on_btnParse_clicked()
{
    QRegExp separator("( |\n|\t)");
    QString text = ui->showText->toPlainText();
    R1 = text.split(separator, QString::SkipEmptyParts);
    if (!(ui->radioAll->isChecked()) && !(ui->radioMail->isChecked()) && !(ui->radioNum->isChecked())) {
        QMessageBox::critical(this, "Error", "Не выбран режим поиска");
        return;
    }
    if (file == NULL) {
        QMessageBox::critical(this, "Error", "Не выбран файл");
        return;
    }

    if (ui->radioAll->isChecked()) {
        ui->listR1->addItems(R1);
    }
    if (ui->radioNum->isChecked()) {
        QRegExp r(".*[0-9]+.*");
        QRegExpValidator v(r, 0);
        QString check;
        QMutableListIterator<QString> it(R1);
        int pos = 0;
        while (it.hasNext()) {
            check = it.next();
            if (v.validate(check, pos) != QValidator::Acceptable) {
                it.remove();
            }
        }
        ui->listR1->addItems(R1);
    }
    if (ui->radioMail->isChecked()) {
        QRegExp r(".*@.*\..*");
        QRegExpValidator v(r, 0);
        QString check;
        QMutableListIterator<QString> it(R1);
        int pos = 0;
        while (it.hasNext()) {
            check = it.next();
            if (v.validate(check, pos) != QValidator::Acceptable) {
                it.remove();
            }
        }
        ui->listR1->addItems(R1);
    }
}

void MainWindow::on_btnLtoRsingle_clicked()
{
    R2.push_back(R1.value(ui->listR1->currentRow()));
    R1.removeAt(ui->listR1->currentRow());
    ui->listR1->clear();
    ui->listR2->clear();
    ui->listR1->addItems(R1);
    ui->listR2->addItems(R2);
}

void MainWindow::on_btnRtoLsingle_clicked()
{
    R1.push_back(R2.value(ui->listR2->currentRow()));
    R2.removeAt(ui->listR2->currentRow());
    ui->listR1->clear();
    ui->listR2->clear();
    ui->listR1->addItems(R1);
    ui->listR2->addItems(R2);
}

void MainWindow::on_btnLtoRmultiple_clicked()
{
    R2.clear();
    ui->listR1->clear();
    ui->listR2->clear();
    R2 = R1;
    ui->listR2->addItems(R2);
}

void MainWindow::on_btnRtoLmultiple_clicked()
{
    R1.clear();
    ui->listR1->clear();
    ui->listR2->clear();
    R1 = R2;
    ui->listR1->addItems(R1);
}

void MainWindow::on_btnSearch_clicked()
{
    int i;
    if (!ui->checkR1->isChecked() && !ui->checkR2->isChecked()) {
        QMessageBox::critical(this, "Error", "Не выбран раздел, в котором будет производиться поиск");
        return;
    }
    if (ui->lineSearch->text() == "") {
        QMessageBox::critical(this, "Error", "Не задан поисковый запрос");
        return;
    }
    ui->listSearch->clear();
    if (ui->checkR1->isChecked()) {
        for (i = 0; i < R1.size(); i++) {
            if (R1.value(i).contains(ui->lineSearch->text())) {
                ui->listSearch->addItem(R1.at(i));
            }
        }
    }
    if (ui->checkR2->isChecked()) {
        for (i = 0; i < R2.size(); i++) {
            if (R2.value(i).contains(ui->lineSearch->text())) {
                ui->listSearch->addItem(R2.at(i));
            }
        }
    }
}

void MainWindow::reloadLists()
{
    ui->listR1->clear();
    ui->listR2->clear();
    ui->listR1->addItems(R1);
    ui->listR2->addItems(R2);
}

void MainWindow::on_btnAdd_clicked()
{
    Dialog *d = new Dialog(this);
    d->show();
}

void MainWindow::on_btnClear_clicked()
{
    ui->listR1->clear();
    ui->listR1->clear();
    R1.clear();
    R2.clear();
    ui->lineSearch->clear();
    ui->listSearch->clear();
    ui->showText->clear();
    ui->radioAll->setChecked(false);
    ui->radioMail->setChecked(false);
    ui->radioNum->setChecked(false);
    ui->checkR1->setChecked(false);
    ui->checkR2->setChecked(false);
}
