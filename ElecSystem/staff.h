#ifndef STAFF_H
#define STAFF_H

#include <QWidget>

namespace Ui {
class Staff;
}

class Staff : public QMainWindow
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = nullptr);
    ~Staff();

private slots:
    void on_pushButton_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_8_released();

    void on_pushButton_9_released();

    void on_pushButton_10_released();

private:
    Ui::Staff *ui;
};

#endif // STAFF_H
