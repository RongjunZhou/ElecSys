#ifndef MEMSQL_H
#define MEMSQL_H

#include <QObject>

class memsql : public QObject
{
    Q_OBJECT
public:
    explicit memsql(QObject *parent = nullptr);

signals:

};

#endif // MEMSQL_H
