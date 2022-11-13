#include "memsql.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

memsql::memsql(QObject *parent)
    : QObject{parent}
{
    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));
}
