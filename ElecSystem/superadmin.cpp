#include "superadmin.h"
#include "ui_superadmin.h"

SuperAdmin::SuperAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperAdmin)
{
    ui->setupUi(this);
    database = QSqlDatabase::addDatabase("Admin");
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
    ui->sTable->insertRow(userInfoList.size()+1);
    ui->sTable->setItem(0,0,new QTableWidgetItem((QString)"用户名"));
    ui->sTable->setItem(0,1,new QTableWidgetItem((QString)"密码"));
    ui->sTable->setItem(0,2,new QTableWidgetItem((QString)"权限"));
    for(int i = 0;i < userInfoList.size();i++){
        ui->sTable->setItem(i+1,0,new QTableWidgetItem((QString)userInfoList[i].getUsername()));
        ui->sTable->setItem(i+1,1,new QTableWidgetItem((QString)userInfoList[i].getPassword()));
        ui->sTable->setItem(i+1,2,new QTableWidgetItem(userInfoList[i].getRole()));
    }
    ui->sTable->show();

}

