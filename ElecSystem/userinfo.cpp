#include "userinfo.h"

UserInfo::UserInfo()
{

}

UserInfo::UserInfo(QString username,QString password,int role)
{
    this->username = username;
    this->password = password;
    this->role = role;
}

QString UserInfo::getUsername(){
    return this->username;
}

QString UserInfo::getPassword(){
    return this->password;
}

int UserInfo::getRole(){
    return this->role;
}
