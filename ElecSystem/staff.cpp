#include "staff.h"
#include "ui_staff.h"
#include "mainwindow.h"
#include "analysetable.h"

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

int compareAnalyseTableByScore(AnalyseTable &a,AnalyseTable &b)
{
    return a.getScore()>b.getScore();
}

int compareAnalyseTableByTotal(AnalyseTable &a,AnalyseTable &b)
{
     return a.getTotal()>b.getTotal();
}

int compareAnalyseTableByAverage(AnalyseTable &a,AnalyseTable &b)
{
    return a.getAverge()>b.getAverge();
}
int compareMax(MemInfo &a,MemInfo &b)
{
    return a.getcharge()>b.getcharge();
}

void Staff::on_pushButton_8_released()
{
    //初始化表格
    ui->tableWidget->setRowCount(0);
    QString date = ui->dateEdit_2->text();
    query->prepare("select * from gathar where date = :date");
    query->bindValue(":date",date);
    query->exec();
    double homeAverage = 0;
    int homeCount = 0;
    QMap<QString,AnalyseTable> dataMap;
    QMap<QString,MemInfo> maxMap;
    while(query->next()){
        QString area = query->value("area").toString();
        if(!dataMap.contains(area)){
            dataMap.insert(area,AnalyseTable());
        }
        AnalyseTable at = dataMap.value(area);
        at.addData(query->value("high").toDouble()+query->value("low").toDouble());
        at.setArea(query->value("area").toString());
        dataMap.insert(area,at);
        homeAverage+=(query->value("high").toDouble()+query->value("low").toDouble());
        MemInfo miBuf = MemInfo();
        miBuf.setInfoForStaff(
            query->value("area").toString(),
            query->value("house").toString(),
            query->value("high").toDouble()+query->value("low").toDouble()
                    );
        maxMap.insert(
                    query->value("house").toString(),
                    miBuf
                    );
        homeCount++;
    }
    query->clear();
    QList<MemInfo> memSort = maxMap.values();
    std::sort(memSort.begin(),memSort.end(),compareMax);
    int count = 0;
    for(MemInfo o:memSort){
        if(count<20){
            QString HomeArea = o.getarea();
            AnalyseTable atBuf = dataMap.value(HomeArea);
            atBuf.addScore(20-count);
            dataMap.insert(
                        HomeArea,
                        atBuf
                        );

            count++;
        }else{
            break;
        }
    }
    if(count>0){
        ui->label_18->setText(memSort[0].gethouse());
        ui->lcdNumber_6->display(memSort[0].getcharge());
        ui->lcdNumber_5->display(memSort[0].getcharge()/30);
        ui->lcdNumber_2->display(homeAverage);
        ui->lcdNumber->display(homeAverage/memSort.size());
    }
    count = 0;
    QList<AnalyseTable> dataSort = dataMap.values();
    std::sort(dataSort.begin(),dataSort.end(),compareAnalyseTableByTotal);
    for(AnalyseTable o:dataSort){
        if(count<20){
            o.addScore(40-2*count);
            dataSort.replace(count,o);
        }else{
            break;
        }
        count++;
    }
    count = 0;
    std::sort(dataSort.begin(),dataSort.end(),compareAnalyseTableByAverage);
    for(AnalyseTable o:dataSort){
        if(count<20){
            o.addScore(40-2*count);
            dataSort.replace(count,o);
        }else{
            break;
        }
        count++;
    }
    std::sort(dataSort.begin(),dataSort.end(),compareAnalyseTableByScore);
    if(count>0){
        ui->label_16->setText(dataSort[0].getArea());
        ui->lcdNumber_4->display(dataSort[0].getTotal()/30);
        ui->lcdNumber_3->display(dataSort[0].getTotal());
    }
    for(AnalyseTable o:dataSort){
        int tableCount = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(tableCount);
        ui->tableWidget_2->setItem(tableCount,0,new QTableWidgetItem(o.getArea()));
        ui->tableWidget_2->setItem(tableCount,1,new QTableWidgetItem(QString::number(o.getTotal())));
        ui->tableWidget_2->setItem(tableCount,2,new QTableWidgetItem(QString::number(o.getAverge())));
        ui->tableWidget_2->setItem(tableCount,3,new QTableWidgetItem(QString::number(o.getScore())));
        ui->tableWidget_2->setItem(tableCount,4,new QTableWidgetItem(QString::number(o.getAverge()>homeAverage/homeCount)));
        qDebug()<<o.getArea()<<o.getTotal()<<o.getAverge()<<o.getScore();
    }
}

