#include "Employee.h"
#include "analysetableforemployee.h"
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
    for(int i=0;i<sizeNum;i++){
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
            query->exec();
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


int count = 0;

void Employee::on_pushButton_7_released()
{

    count = 0;
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
    ui->pushButton_19->setEnabled(false);
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_21->setEnabled(false);
    ui->pushButton_22->setEnabled(false);
}


//按家庭统计
void Employee::on_pushButton_8_released()
{
    count = 0;
    ui->tableWidget_2->setRowCount(0);
    int month_all = 0;
    double fee_all = 0;
    int check = 0;

    QMap<QString, double> power, fee;
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
        fee_all = query->value("charge").toDouble();
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
            check += 1;
        }
    }
    powerlist = power.values();
    feelist = fee.values();
    query->clear();
    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem(infolist[0]));

    for(int i=0;i<infolist.size();i++){
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(infolist[i]));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(powerlist[i])));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(feelist[i])));
    }

    ui->pushButton_19->setEnabled(false);
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_21->setEnabled(false);
    ui->pushButton_22->setEnabled(false);
}


//按小区统计
void Employee::on_pushButton_9_released()
{
    count = 1;
    ui->tableWidget_2->setRowCount(0);
    int month_all = 0;
    double fee_all = 0;
    double avepower = 0;
    double avefee = 0;
    int check = 0;

    QMap<QString, double> areapower, areafee,averagepower,averagefee,number;
    QList<double> areapowerlist ;
    QList<double> areafeelist ;
    QList<QString> areainfolist ;
    QList<double> averagepowerlist ;
    QList<double> averagefeelist ;

    query->prepare("select * from gathar");
    query->exec();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区名称" <<"月总用电量" << "月总电费" << "户平均电量" <<"户平均电费" );

    while(query->next()){
        month_all = query->value("high").toDouble()+query->value("low").toDouble();
        fee_all = query->value("charge").toDouble();
        QString areaaddress = query->value("area").toString();
        if(bool isok = areapower.contains(areaaddress)){
            month_all += areapower.value(areaaddress);
            areapower.insert(areaaddress, month_all);
            fee_all += areafee.value(areaaddress);
            areafee.insert(areaaddress, fee_all);
            check = number.value(areaaddress)+1;
            averagepower.insert(areaaddress, month_all/number.value(areaaddress));
            averagefee.insert(areaaddress, fee_all/number.value(areaaddress));
        }
        else{
            check +=1;
            areapower.insert(areaaddress, month_all);
            areapowerlist.append(month_all);
            areafee.insert(areaaddress, fee_all);
            areafeelist.append(fee_all);
            areainfolist.append(areaaddress);
            number.insert(areaaddress, check);
            averagepower.insert(areaaddress, month_all/number.value(areaaddress));
            averagepowerlist.append(month_all/number.value(areaaddress));
            averagefee.insert(areaaddress, fee_all/number.value(areaaddress));
            averagefeelist.append(fee_all/number.value(areaaddress));
        }
    }
    areapowerlist = areapower.values();
    areafeelist = areafee.values();
    averagepowerlist = averagepower.values();
    averagefeelist = averagefee.values();
    query->clear();

    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem(areainfolist[0]));

    for(int i=0;i<areainfolist.size();i++){
        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(areainfolist[i]));
        ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(areapowerlist[i])));
        ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(areafeelist[i])));
        ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::number(averagepowerlist[i])));
        ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(averagefeelist[i])));
    }
    ui->pushButton_19->setEnabled(true);
    ui->pushButton_20->setEnabled(true);
    ui->pushButton_21->setEnabled(true);
    ui->pushButton_22->setEnabled(true);
}

int compareMemInfoByPower(AnalyseTableForEmployee &a, AnalyseTableForEmployee &b){
    return a.all_power>b.all_power;
}


//按月总用电量排序
void Employee::on_pushButton_19_released()
{
    if(count==1){
        QList<AnalyseTableForEmployee> list;
        int sizeNum=ui->tableWidget_2->rowCount();
        qDebug()<<sizeNum;
        for(int i=0;i<sizeNum;i++){
            list.append(AnalyseTableForEmployee(
                            ui->tableWidget_2->item(i,0)->text(),
                            ui->tableWidget_2->item(i,1)->text().toDouble(),
                            ui->tableWidget_2->item(i,2)->text().toDouble(),
                            ui->tableWidget_2->item(i,3)->text().toDouble(),
                            ui->tableWidget_2->item(i,4)->text().toDouble()
                            ));
        }
        std::sort(list.begin(),list.end(),compareMemInfoByPower);
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        for(AnalyseTableForEmployee o:list){
            int i = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(i);
            ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(o.area));
            ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(o.all_power)));
            ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(o.all_fee)));
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::number(o.averpower)));
            ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(o.averfee)));
        }
    }
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_21->setEnabled(false);
    ui->pushButton_22->setEnabled(false);
}


int compareMemInfoByFee(AnalyseTableForEmployee &a, AnalyseTableForEmployee &b){
    return a.all_fee>b.all_fee;
}

//按每月电费排序
void Employee::on_pushButton_20_released()
{
    if(count==1){
        QList<AnalyseTableForEmployee> list;
        int sizeNum=ui->tableWidget_2->rowCount();
        qDebug()<<sizeNum;
        for(int i=0;i<sizeNum;i++){
            list.append(AnalyseTableForEmployee(
                            ui->tableWidget_2->item(i,0)->text(),
                            ui->tableWidget_2->item(i,1)->text().toDouble(),
                            ui->tableWidget_2->item(i,2)->text().toDouble(),
                            ui->tableWidget_2->item(i,3)->text().toDouble(),
                            ui->tableWidget_2->item(i,4)->text().toDouble()
                            ));
        }
        std::sort(list.begin(),list.end(),compareMemInfoByFee);
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        for(AnalyseTableForEmployee o:list){
            int i = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(i);
            ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(o.area));
            ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(o.all_power)));
            ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(o.all_fee)));
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::number(o.averpower)));
            ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(o.averfee)));
        }
    }
    ui->pushButton_19->setEnabled(false);
    ui->pushButton_21->setEnabled(false);
    ui->pushButton_22->setEnabled(false);
}

//按户平均电量排序

int compareMemInfoByAverpower(AnalyseTableForEmployee &a, AnalyseTableForEmployee &b){
    return a.averpower>b.averpower;
}
void Employee::on_pushButton_21_released()
{
    if(count==1){
        QList<AnalyseTableForEmployee> list;
        int sizeNum=ui->tableWidget_2->rowCount();
        qDebug()<<sizeNum;
        for(int i=0;i<sizeNum;i++){
            list.append(AnalyseTableForEmployee(
                            ui->tableWidget_2->item(i,0)->text(),
                            ui->tableWidget_2->item(i,1)->text().toDouble(),
                            ui->tableWidget_2->item(i,2)->text().toDouble(),
                            ui->tableWidget_2->item(i,3)->text().toDouble(),
                            ui->tableWidget_2->item(i,4)->text().toDouble()
                            ));
        }
        std::sort(list.begin(),list.end(),compareMemInfoByAverpower);
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        for(AnalyseTableForEmployee o:list){
            int i = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(i);
            ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(o.area));
            ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(o.all_power)));
            ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(o.all_fee)));
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::number(o.averpower)));
            ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(o.averfee)));
        }
    }
    ui->pushButton_19->setEnabled(false);
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_22->setEnabled(false);
}

//按户平均电费排序

int compareMemInfoByAverfee(AnalyseTableForEmployee &a, AnalyseTableForEmployee &b){
    return a.averfee>b.averfee;
}
void Employee::on_pushButton_22_released()
{
    if(count==1){
        QList<AnalyseTableForEmployee> list;
        int sizeNum=ui->tableWidget_2->rowCount();
        qDebug()<<sizeNum;
        for(int i=0;i<sizeNum;i++){
            list.append(AnalyseTableForEmployee(
                            ui->tableWidget_2->item(i,0)->text(),
                            ui->tableWidget_2->item(i,1)->text().toDouble(),
                            ui->tableWidget_2->item(i,2)->text().toDouble(),
                            ui->tableWidget_2->item(i,3)->text().toDouble(),
                            ui->tableWidget_2->item(i,4)->text().toDouble()
                            ));
        }
        std::sort(list.begin(),list.end(),compareMemInfoByAverfee);
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList() << "老小区" << "家庭户名" << "用电年月" <<"月总用电量" << "电费");
        for(AnalyseTableForEmployee o:list){
            int i = ui->tableWidget_2->rowCount();
            ui->tableWidget_2->insertRow(i);
            ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(o.area));
            ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(QString::number(o.all_power)));
            ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(QString::number(o.all_fee)));
            ui->tableWidget_2->setItem(i,3,new QTableWidgetItem(QString::number(o.averpower)));
            ui->tableWidget_2->setItem(i,4,new QTableWidgetItem(QString::number(o.averfee)));
        }
    }
    ui->pushButton_19->setEnabled(false);
    ui->pushButton_20->setEnabled(false);
    ui->pushButton_21->setEnabled(false);
}
