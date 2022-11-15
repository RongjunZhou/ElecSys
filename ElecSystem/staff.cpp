#include "staff.h"
#include "ui_staff.h"

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
