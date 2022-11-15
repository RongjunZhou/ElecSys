#include "staff.h"
#include "ui_staff.h"
#include "mainwindow.h""

Staff::Staff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::staff)
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
    ui->stackedWidget->setCurrentWidget(ui->page_inquire);
}


void Staff::on_pushButton_3_released()
{
    //统计用户，切换到统计页面
    ui->stackedWidget->setCurrentWidget(ui->page_demand);
}


void Staff::on_pushButton_4_released()
{
    //退出系统
    close();
}


void Staff::on_pushButton_8_released()
{
    //退出到主界面
    MainWindow *loginWindow = new MainWindow();
    loginWindow ->show();
    delete this;
}


void Staff::on_pushButton_9_released()
{
    //返回主菜单
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}


void Staff::on_pushButton_10_released()
{
    //返回主菜单
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

