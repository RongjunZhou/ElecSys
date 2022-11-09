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
    query = QSqlQuery("connect",database);
    query.exec("creat table userInfo(username unique,password,role)");
    query.exec("insert into userInfo(username,password,role) values ('郑霄鹏','123','1')");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->username = ui->username->text();
    this->password = ui->password->text();
    qDebug()<<username<<password;
    if(this->username.compare("Admin")){
        if(this->password.compare("njupt+1s")){
            QMessageBox::information(this,"提示","登陆成功");
            //todo
            return ;
        }
    }else{
        query.prepare("select COUNT(*) from userInfo where username = :username");
        query.bindValue(":username",username);
        query.exec();
        int count = query.next();
        if(count){
            query.clear();
            query.prepare("select password,role from userInfo where username = :username");
            query.bindValue(":username",username);
            query.exec();
            QString truePassword= query.value("password").toString();
            int role = query.value("role").toInt();
            if(truePassword.compare(password)){
                QMessageBox::information(this,"提示","登陆成功");
                //todo
                switch(role){
                case 1:
                    break;
                case 2:
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

