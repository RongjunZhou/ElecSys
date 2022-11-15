#include "Employee.h"
#include "ui_Employee.h"
#include "mainwindow.h"
#include <QSqlError>
#include "meminfo.h"


Employee::Employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
    this->setWindowTitle("用户端（统计员）");
    database=QSqlDatabase::addDatabase("QSQLITE","employee");
    database.setDatabaseName("employee.db");
    database.open();
    query = new QSqlQuery(database);
    query->exec("create table gathar(area Not Null,house Not Null,date Not Null,high Not Null,low Not Null,charge)");
}

Employee::~Employee()
{
    delete ui;
}

void Employee::on_pushButton_released()
{
    //查看用户，切换到查看页面
    ui->stackedWidget->setCurrentWidget(ui->searchpage);
}


void Employee::on_pushButton_2_released()
{
    //统计用户，切换到统计页面
    ui->stackedWidget->setCurrentWidget(ui->statpage);
}

void Employee::on_pushButton_3_released()
{
    //退出系统
    close();
}

void Employee::on_pushButton_4_released()
{
    //返回主菜单
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Employee::on_pushButton_5_released()
{
    ui->stackedWidget->setCurrentWidget(ui->menupage);
}


void Employee::on_pushButton_add_released()
{
    //添加新用户
    ui->tableWidget->insertRow((ui->tableWidget->rowCount()));
    //跳转到最下方
    ui->tableWidget->scrollToBottom();
}


void Employee::on_pushButton_save_released()
{
    QList<MemInfo> list;
    int sizeNum=ui->tableWidget->rowCount();
    qDebug()<<sizeNum;
    for(int i=1;i<sizeNum;i++){
        area  = ui->tableWidget->item(i,0)->text();
        house = ui->tableWidget->item(i,1)->text();
        date = ui->tableWidget->item(i,2)->text();
        high = ui->tableWidget->item(i,3)->text().toDouble();
        low = ui->tableWidget->item(i,4)->text().toDouble();
        charge = 0.5*high + 0.8*low;
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(charge));
        list.append(MemInfo(area,house,date,high,low,charge));
    }
    for(MemInfo o:list){
        query->prepare("select COUNT(*) from gathar where area = :area and house = :house and date = :date");
        query->bindValue(":area", o.getarea());
        query->bindValue(":house", o.gethouse());
        query->bindValue(":date", o.getdate());
        query->exec();
        query->next();
        int count = query->value("COUNT(*)").toInt();
        query->clear();
        if(count>0){
            query->prepare("update gathar set high =:high, low=:low, charge=:charge where area=:area and house=:house and date=:date");
            query->bindValue(":high", o.gethigh());
            query->bindValue(":low", o.getlow());
            query->bindValue(":charge", o.getcharge());
            query->bindValue(":area", o.getarea());
            query->bindValue(":house", o.gethouse());
            query->bindValue(":date", o.getdate());
        }else{
          query->prepare("insert into gathar (area,house,date,high,low,charge) "
                         "values (:area,:house,:date,:high,:low,:charge)");
          query->bindValue(":area", o.getarea());
          query->bindValue(":house", o.gethouse());
          query->bindValue(":date",o.getdate());
          query->bindValue(":high",o.gethigh());
          query->bindValue(":low",o.getlow());
          query->bindValue(":charge",o.getcharge());
          query->exec();
        }
        query->clear();
    }
}


void Employee::on_pushButton_6_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete query;
    delete this;
}

