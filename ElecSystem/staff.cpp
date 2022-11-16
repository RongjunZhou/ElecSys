#include "staff.h"
#include "ui_staff.h"
#include "mainwindow.h"

Staff::Staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
    this->setWindowTitle("用户端（工作人员）");
    database=QSqlDatabase::addDatabase("QSQLITE","manager");
    database.setDatabaseName("employee.db");
    if(!database.open()){
        QMessageBox::information(this,"提示","请先录入数据");
        this->close();
    }
    query = new QSqlQuery(database);
    ui->tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);

}

Staff::~Staff()
{
    delete ui;
}

void Staff::on_pushButton_released()
{
    //查看用户，切换到查看页面
    ui->stackedWidget->setCurrentWidget(ui->viewpage);
}


void Staff::on_pushButton_2_released()
{
    //查看用户，切换到扩容建议页面
    ui->stackedWidget->setCurrentWidget(ui->demandpage);
}


void Staff::on_pushButton_3_released()
{
    //退出系统
    close();
}


void Staff::on_pushButton_6_released()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}


void Staff::on_pushButton_4_released()
{
    //返回主菜单
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Staff::on_pushButton_5_released()
{
    //返回主菜单
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Staff::on_pushButton_7_released()
{
    if(ui->checkBox->isChecked()){
        ui->tableWidget->setRowCount(0);
    }
    QString date = ui->dateEdit->text();
    QString area = ui->lineEdit->text();
    QString house = ui->lineEdit_2->text();
    if(area.isEmpty()){
        query->prepare("select * from gathar where date = :date");
        query->bindValue(":date",date);
        query->exec();
        while(query->next()){
            int count = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(count);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(query->value("high").toString()));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(query->value("low").toString()));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }else if(house.isEmpty()){
        query->prepare("select * from gathar where date = :date and area = :area");
        query->bindValue(":date",date);
        query->bindValue(":area",area);
        query->exec();
        while(query->next()){
            int count = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(count);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(query->value("high").toString()));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(query->value("low").toString()));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }else{
        query->prepare("select * from gathar where date = :date and area = :area and house = :house");
        query->bindValue(":date",date);
        query->bindValue(":area",area);
        query->bindValue(":house",house);
        query->exec();
        while(query->next()){
            int count = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(count);
            ui->tableWidget->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget->setItem(count,2,new QTableWidgetItem(query->value("high").toString()));
            ui->tableWidget->setItem(count,3,new QTableWidgetItem(query->value("low").toString()));
            ui->tableWidget->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }
}


void Staff::on_pushButton_8_released()
{
    //初始化表格
    ui->tableWidget->setRowCount(0);
    QString date = ui->dateEdit_2->text();
    query->prepare("select * from gathar where date = :date");
    query->bindValue(":date",date);
    query->exec();
    //QMap<QString,>
}

