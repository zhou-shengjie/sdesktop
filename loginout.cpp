#include "loginout.h"
#include "userinfo.h"
#include "errmsg.h"

LoginOut::LoginOut(QObject *parent) : QObject(parent)
{

}

bool LoginOut::login(UserInfo *userInfo, ErrMsg *errMsg)
{

    return true;
}
