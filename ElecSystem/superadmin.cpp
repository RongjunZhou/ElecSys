#include "superadmin.h"
#include "ui_superadmin.h"

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
    delete query;
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
    query->clear();
    ui->sTable->insertRow(userInfoList.size());
    for(int i = 0;i < userInfoList.size();i++){
        ui->sTable->setItem(i+1,0,new QTableWidgetItem((QString)userInfoList[i].getUsername()));
        ui->sTable->setItem(i+1,1,new QTableWidgetItem((QString)userInfoList[i].getPassword()));
        ui->sTable->setItem(i+1,2,new QTableWidgetItem(userInfoList[i].getRole()));
    }
    ui->sTable->show();

}


void SuperAdmin::on_fixSubmit_clicked()
{
    UserInfo userInfo = UserInfo(
                ui->username->text(),
                ui->password->text(),
                ui->role->value()
                );
    query->prepare("select COUNT(*) from userInfo where username = :username");
    query->bindValue(":username",userInfo.getUsername());
    query->exec();
    query->next();
    int count = query->value("COUNT(*)").toInt();
    query->clear();
    if(count>0){
        query->prepare("update userinfo set password = :password, role = :role where username = :username");
        query->bindValue(":password",userInfo.getPassword());
        query->bindValue(":role",userInfo.getRole());
        query->bindValue(":username",userInfo.getUsername());
        if(query->exec()){
            QMessageBox::information(this,"提示","成功");
            query->clear();
        }else{
            QMessageBox::information(this,"提示","失败");
            query->clear();
        }
    }else{
        QMessageBox::information(this,"提示","用户名不存在，请检查");
    }
}


void SuperAdmin::on_delSubmit_clicked()
{
    QString username = ui->delUsername->text();
    query->prepare("delete from userinfo where username = :username");
    query->bindValue(":username",username);
    if(query->exec()){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::information(this,"提示","用户名不存在，请检查");
    }
    query->clear();
}


void SuperAdmin::on_newSubmit_clicked()
{
    UserInfo userInfo = UserInfo(
                ui->newUsername->text(),
                ui->newPassword->text(),
                ui->newRole->value()
                );
    query->prepare("insert into userinfo (username,password,role) values (:username,:password,:role)");
    query->bindValue(":password",userInfo.getPassword());
    query->bindValue(":role",userInfo.getRole());
    query->bindValue(":username",userInfo.getUsername());
    if(query->exec()){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::information(this,"提示","用户名已存在，请检查");
    }
    query->clear();
}

