#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "staff.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icons/logo.ico"));
    database = QSqlDatabase::addDatabase("QSQLITE","login");
    database.setDatabaseName("data.db");
    if(!database.open()){
        QMessageBox::information(this,"错误","数据库打开失败");
        this->close();
    }
    query = new QSqlQuery(database);
    query->exec("create table userInfo(username unique,password,role)");
    query->exec("insert into userInfo(username,password,role) values ('郑霄鹏','123','1')");
    query->exec("insert into userInfo(username,password,role) values ('郑喆','123','2')");
    //query->exec("insert into userInfo(username,password,role) values ('郑霄鹏','123','1')");
}

MainWindow::~MainWindow()
{
    database.close();
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
            QMessageBox::information(this,"提示","登录成功");
            database.close();
            SuperAdmin *superAdmin = new SuperAdmin();
            superAdmin->setWindowIcon(QIcon(":/icons/logo.ico"));
            superAdmin->show();
            this->close();
        }else{
            QMessageBox::information(this,"提示","密码错误");
        }
    }else{
        query->prepare("select COUNT(*) from userInfo where username = :username");
        query->bindValue(":username",username);
        query->exec();
        query->next();
        int count = query->value("COUNT(*)").toInt();
        qDebug()<<count;
        if(count){
            query->clear();
            query->prepare("select password,role from userInfo where username = :username");
            query->bindValue(":username",username);
            query->exec();
            query->next();
            QString truePassword= query->value("password").toString();
            int role = query->value("role").toInt();
            if(truePassword==password){
                QMessageBox::information(this,"提示","登录成功");
                if(role==1){
                    Employee * employee = new Employee();
                    employee->setWindowIcon(QIcon(":/icons/logo.ico"));
                    employee->show();
                    this->close();
                    this->~MainWindow();
                }else if(role==2){
                    Staff * staff = new Staff();
                    staff->setWindowIcon(QIcon(":/icons/logo.ico"));
                    staff->show();
                    this->close();
                    this->~MainWindow();
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


void MainWindow::on_pushButton_2_clicked()
{
    close();
}

