#include "Employee.h"
#include "ui_Employee.h"
#include "mainwindow.h"
#include <QSqlError>

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
    qDebug()<<query->exec("create table gathar(area,house,date,high,low,charge)");
    qDebug()<<query->exec("insert into gathar(area,house,date,high,low,charge) values ('江湾城','一单元-502','2022/11','10','10','10')");
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

}


void Employee::on_pushButton_6_clicked()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete query;
    delete this;
}

