#ifndef SUPERADMIN_H
#define SUPERADMIN_H

#include <QWidget>

namespace Ui {
class SuperAdmin;
}

class SuperAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit SuperAdmin(QWidget *parent = nullptr);
    ~SuperAdmin();

private:
    Ui::SuperAdmin *ui;
};

#endif // SUPERADMIN_H
