#include "superadmin.h"
#include "ui_superadmin.h"
#include "mainwindow.h"

SuperAdmin::SuperAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperAdmin)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("QSQLITE","superAdmin");
    database.setDatabaseName("data.db");
    database.open();
    query = new QSqlQuery(database);
}

SuperAdmin::~SuperAdmin()
{
    delete ui;
}

void SuperAdmin::on_sButton_clicked()
{

    QString username = ui->sLine->text();
    QList<UserInfo> userInfoList;
    query->prepare("select * from userInfo where username LIKE :username");
    query->bindValue(":username",username);
    query->exec();
    while(query->next()){
        userInfoList.append(
                    UserInfo(
                        query->value("username").toString(),
                        query->value("password").toString(),
                        query->value("role").toInt()
                        )
        );
    }
    ui->sTable->insertRow(userInfoList.size());
    for(int i = 0;i < userInfoList.size();i++){
        ui->sTable->setItem(i,0,new QTableWidgetItem((QString)userInfoList[i].getUsername()));
        ui->sTable->setItem(i,1,new QTableWidgetItem((QString)userInfoList[i].getPassword()));
        ui->sTable->setItem(i,2,new QTableWidgetItem(userInfoList[i].getRole()));
    }
    ui->sTable->show();

}


void SuperAdmin::on_pushButton_6_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}


void SuperAdmin::on_pushButton_7_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}


void SuperAdmin::on_pushButton_8_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}


void SuperAdmin::on_pushButton_9_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}

