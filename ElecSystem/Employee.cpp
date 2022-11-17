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

void Employee::on_pushButton_save_2_released()
{
    ui->tableWidget->setRowCount(0);
    query->exec("select * from gathar");
    while(query->next()){
        int count = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(count);
        ui->tableWidget->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
        ui->tableWidget->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
        ui->tableWidget->setItem(count,2,new QTableWidgetItem(query->value("date").toString()));
        ui->tableWidget->setItem(count,3,new QTableWidgetItem(query->value("high").toString()));
        ui->tableWidget->setItem(count,4,new QTableWidgetItem(query->value("low").toString()));
        ui->tableWidget->setItem(count,5,new QTableWidgetItem(query->value("charge").toString()));
    }
}




void Employee::on_pushButton_7_released()
{

    ui->tableWidget_2->setRowCount(0);
    int month_all;
    QString area = ui->lineEdit->text();
    QString house = ui->lineEdit_2->text();
    QString date = ui->lineEdit_3->text();

    //有小区，有家庭，有日期
    if(!(date.isEmpty()) && !(area.isEmpty()) && !(house.isEmpty())){
        query->prepare("select * from gathar where date = :date and area = :area and house = :house");
        query->bindValue(":date",date);
        query->bindValue(":area",area);
        query->bindValue(":house",house);
        query->exec();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        while(query->next()){
            month_all = query->value("high").toDouble()+query->value("low").toDouble();
            int count = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(count);
            ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(query->value("date").toString()));
            ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(QString::number(month_all)));
            ui->tableWidget_2->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }

    //有小区，无家庭，有日期
    else if(!(date.isEmpty()) && !(area.isEmpty()) && house.isEmpty()){
        query->prepare("select * from gathar where date = :date and area = :area");
        query->bindValue(":date",date);
        query->bindValue(":area",area);
        query->exec();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setColumnCount(4);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" <<"月总用电量" << "电费");
        while(query->next()){
            month_all = query->value("high").toDouble()+query->value("low").toDouble();
            int count = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(count);
            ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(QString::number(month_all)));
            ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(query->value("charge").toString()));
        }
    }

    //有小区，无家庭，无日期
    else if(!(area.isEmpty())&& house.isEmpty() && date.isEmpty()){
        query->prepare("select * from gathar where area = :area");
        query->bindValue(":area",area);
        query->exec();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        while(query->next()){
            month_all = query->value("high").toDouble()+query->value("low").toDouble();
            int count = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(count);
            ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(query->value("date").toString()));
            ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(QString::number(month_all)));
            ui->tableWidget_2->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }

    //有小区，有家庭，无日期
    else if(!(area.isEmpty()) && !(house.isEmpty()) && date.isEmpty()){
        query->prepare("select * from gathar where area = :area and house = :house");
        query->bindValue(":area",area);
        query->bindValue(":house",house);
        query->exec();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名"<< "用电年月" <<"月总用电量" << "电费");
        while(query->next()){
            int count = ui->tableWidget_2->rowCount();
            month_all = query->value("high").toDouble()+query->value("low").toDouble();
            ui->tableWidget_2->insertRow(count);
            ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(query->value("date").toString()));
            ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(QString::number(month_all)));
            ui->tableWidget_2->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }

    //无小区，无家庭，无日期
    else if(area.isEmpty() && house.isEmpty() && date.isEmpty()){
        query->prepare("select * from gathar");
        query->exec();
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        while(query->next()){
            int count = ui->tableWidget_2->rowCount();
            month_all = query->value("high").toDouble()+query->value("low").toDouble();
            ui->tableWidget_2->insertRow(count);
            ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(query->value("area").toString()));
            ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(query->value("house").toString()));
            ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(query->value("date").toString()));
            ui->tableWidget_2->setItem(count,3,new QTableWidgetItem(QString::number(month_all)));
            ui->tableWidget_2->setItem(count,4,new QTableWidgetItem(query->value("charge").toString()));
        }
    }
}


//按家庭统计
void Employee::on_pushButton_8_released()
{
    ui->tableWidget_2->setRowCount(0);
    int month_all = 0;
    double fee_all = 0;

    QMultiMap<QString, double> power, fee;
    QList<double> powerlist ;
    QList<double> feelist ;
    QList<QString> infolist ;

    query->prepare("select * from gathar");
    query->exec();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(3);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "家庭相关信息" <<"年总用电量" << "年总电费");

    while(query->next()){
        month_all = query->value("high").toDouble()+query->value("low").toDouble();
        QString newarea = query->value("area").toString();
        QString newhouse = query->value("house").toString();
        QString newdate = query->value("date").toString();
        QString newyear = newdate.mid(0,4);
        QString newaddress = newarea + "-" + newhouse + "-" + newyear;
        if(bool isok = power.contains(newaddress)){
            month_all += power.value(newaddress);
            power.insert(newaddress, month_all);
            fee_all += fee.value(newaddress);
            fee.insert(newaddress, fee_all);
        }
        else{
            power.insert(newaddress, month_all);
            powerlist.append(month_all);
            fee.insert(newaddress, fee_all);
            feelist.append(fee_all);
            infolist.append(newaddress);
        }
    }

    qDebug() << infolist[0];
    qDebug() << powerlist[0];
    qDebug() << feelist[0];

    for(int i=0;i<infolist.size();i++){
        int count = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(count+1);
        ui->tableWidget_2->setItem(count,0,new QTableWidgetItem(infolist[i]));
        ui->tableWidget_2->setItem(count,1,new QTableWidgetItem(powerlist[i]));
        ui->tableWidget_2->setItem(count,2,new QTableWidgetItem(feelist[i]));
    };

}

//按小区统计
void Employee::on_pushButton_9_released()
{

}
