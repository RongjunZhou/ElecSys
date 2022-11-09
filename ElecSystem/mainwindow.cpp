#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("data.db");
    database.open();
    query = new QSqlQuery(database);
    query->exec("creat table userInfo(username unique,password,role)");
    query->exec("insert into userInfo(username,password,role) values ('郑霄鹏','123','1')");
}

MainWindow::~MainWindow()
{
    delete query;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->username = ui->username->text();
    this->password = ui->password->text();
    qDebug()<<username<<password;
    if(this->username=="Admin"){
        if(this->password=="njupt+1s"){
            QMessageBox::information(this,"提示","登陆成功");
            //todo
        }else{
            QMessageBox::information(this,"提示","密码错误");
        }
    }else{
        query->prepare("select COUNT(*) from userInfo where username = :username");
        query->bindValue(":username",username);
        query->exec();
        int count = query->next();
        if(count){
            query->clear();
            query->prepare("select password,role from userInfo where username = :username");
            query->bindValue(":username",username);
            query->exec();
            QString truePassword= query->value("password").toString();
            int role = query->value("role").toInt();
            if(truePassword==password){
                QMessageBox::information(this,"提示","登陆成功");
                switch(role){
                case 1:
                    //todo
                    break;
                case 2:
                    //todo
                    break;
                }
            }
            else{
                QMessageBox::information(this,"提示","密码错误");
            }
        }else{
            QMessageBox::information(this,"提示","用户名不存在");
        }
    }
}

