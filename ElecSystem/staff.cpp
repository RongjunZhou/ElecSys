#include "staff.h"
#include "ui_staff.h"
#include "mainwindow.h""

Staff::Staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
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

