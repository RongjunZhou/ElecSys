#ifndef STAFF_H
#define STAFF_H

#include <QWidget>

namespace Ui {
class Staff;
}

class Staff : public QWidget
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = nullptr);
    ~Staff();

private:
    Ui::Staff *ui;
};

#endif // STAFF_H
