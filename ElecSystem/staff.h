#ifndef STAFF_H
#define STAFF_H

#include <QMainWindow>

namespace Ui {
class staff;
}

class staff : public QMainWindow
{
    Q_OBJECT

public:
    explicit staff(QWidget *parent = nullptr);
    ~staff();

private:
    Ui::staff *ui;
};

#endif // STAFF_H
