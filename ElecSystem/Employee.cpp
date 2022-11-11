#include "Employee.h"
#include "ui_Employee.h"

Employee::Employee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
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

