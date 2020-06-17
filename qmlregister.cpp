#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "globalconfig.h"
#include "httpclientmgr.h"
#include "qmlregister.h"
#include "captcha.h"
#include "userinfo.h"
#include "loginout.h"
#include "errmsg.h"

//  registe qml object
void registerQmlObject()
{
    //  singleton
    static GlobalConfig s_gConfig;
    static HttpClientMgr s_httpClientMgr;
    qmlRegisterSingletonInstance<GlobalConfig>("Sjyun.Desktop", 1, 0, "GlobalConfig", &s_gConfig);
    qmlRegisterSingletonInstance<HttpClientMgr>("Sjyun.Desktop", 1, 0, "HttpClientMgr", &s_httpClientMgr);

    //  type
    qmlRegisterType<Captcha>("Sjyun.Desktop", 1, 0, "Captcha");
    qmlRegisterType<LoginOut>("Sjyun.Desktop", 1, 0, "LoginOut");
    qmlRegisterType<UserInfo>("Sjyun.Desktop", 1, 0, "UserInfo");
    qmlRegisterType<GetCaptchaResponse>("Sjyun.Desktop", 1, 0, "GetCaptchaResponse");
    qmlRegisterType<ErrMsg>("Sjyun.Desktop", 1, 0, "ErrMsg");
    qmlRegisterType<LoginRequest>("Sjyun.Desktop", 1, 0, "LoginRequest");

    //  meta type


}
