#include "superadmin.h"
#include "ui_superadmin.h"

SuperAdmin::SuperAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SuperAdmin)
{
    ui->setupUi(this);
}

SuperAdmin::~SuperAdmin()
{
    delete ui;
}
