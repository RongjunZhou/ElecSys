#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "userinfo.h"

namespace Ui {
class SuperAdmin;
}

class SuperAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit SuperAdmin(QWidget *parent = nullptr);
    ~SuperAdmin();

private slots:
    void on_sButton_clicked();

private:
    Ui::SuperAdmin *ui;
    QSqlDatabase database;
    QSqlQuery *query;
};

#endif // SUPERADMIN_H
