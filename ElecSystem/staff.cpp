#include "staff.h"
#include "ui_staff.h"

staff::staff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::staff)
{
    ui->setupUi(this);
}

staff::~staff()
{
    delete ui;
}
