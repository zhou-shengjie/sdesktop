#ifndef LOGIN_OUT_H
#define LOGIN_OUT_H

#include <QObject>
#include "userinfo.h"
#include "errmsg.h"

class HttpClientMgr;
class ErrMsg;
class UserInfo;

class LoginRequest : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString account MEMBER account)
    Q_PROPERTY(QString password MEMBER password)
    Q_PROPERTY(QString captchaId MEMBER captchaId)
    Q_PROPERTY(QString captchaSolution MEMBER captchaSolution)
public:
    QString account;
    QString password;
    QString captchaId;
    QString captchaSolution;
};

class LoginOut : public QObject
{
    Q_OBJECT
public:
    explicit LoginOut(QObject *parent = nullptr);
    Q_INVOKABLE bool login(HttpClientMgr *pHttpClient, UserInfo *userInfo, ErrMsg *errMsg, LoginRequest *req);


signals:

};

#endif // LOGIN_OUT_H
