#ifndef LOGIN_OUT_H
#define LOGIN_OUT_H

#include <QObject>
#include "userinfo.h"
#include "errmsg.h"

class ErrMsg;
class UserInfo;

class LoginOut : public QObject
{
    Q_OBJECT
public:
    explicit LoginOut(QObject *parent = nullptr);
    Q_INVOKABLE bool login(UserInfo *userInfo, ErrMsg *errMsg);


signals:

};

#endif // LOGIN_OUT_H
