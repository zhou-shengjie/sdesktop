#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "globalconfig.h"
#include "httpclientmgr.h"
#include "qmlRegister.h"
#include "captcha.h"

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
    qRegisterMetaType<const HttpClientMgr*>("const HttpClientMgr*");
    qRegisterMetaType<GetCaptchaResponse>("GetCaptchaResponse");
}
