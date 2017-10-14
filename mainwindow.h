#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QStringList R1, R2;
    void reloadLists();
    ~MainWindow();

private slots:
    void on_btnClearR1_clicked();

    void on_btnClearR2_clicked();

    void on_btnSortR1_clicked();

    void on_btnSortR2_clicked();

    void on_btnExit_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_btnParse_clicked();

    QStringList multiSort(int i, QStringList list);

    void on_btnLtoRsingle_clicked();

    void on_btnRtoLsingle_clicked();

    void on_btnLtoRmultiple_clicked();

    void on_btnRtoLmultiple_clicked();

    void on_btnSearch_clicked();

    void on_btnAdd_clicked();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QFile *file = NULL;
};

#endif // MAINWINDOW_H
