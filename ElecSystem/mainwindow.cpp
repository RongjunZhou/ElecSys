#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::on_pushButton_clicked()
{
    this->username = ui->username->text();
    this->password = ui->password->text();
    if(this->username=="Admin"){
        if(this->password=="njupt+1s"){
            return 3;
        }
    }
    if(1){
        return 0;
    }
    return -1;
}

