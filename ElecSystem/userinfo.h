#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    UserInfo();
    UserInfo(QString,QString,int);
    QString getUsername();
    QString getPassword();
    int getRole();
private:
    QString username;
    QString password;
    int role;
};

#endif // USERINFO_H
