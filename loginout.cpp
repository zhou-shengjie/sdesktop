#include "loginout.h"
#include "userinfo.h"
#include "errmsg.h"
#include "httpclientmgr.h"
#include <cpprest/http_client.h>
#include <QDebug>

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

LoginOut::LoginOut(QObject *parent) : QObject(parent)
{

}

bool LoginOut::login(HttpClientMgr *pHttpClient, UserInfo *userInfo, ErrMsg *errMsg)
{
    //  获取验证码
    auto httpClient = pHttpClient->getHttpClient();
    uri_builder builder(U("/account/v1/signin"));
    json::value requestBody = json::value::object();
    requestBody[U("account")] = json::value(U("zhoushengjie"));
    requestBody[U("password")] = json::value(U("YsV9mOVNmo7d0Vx9qjU6NCC1NAV1/Q7ENtX1Wn+Y3BGuJVUpTkyev0vxJNzpdwAzHT3zBfqxZNBMI3RvI22FXHoM/hFctqt05XUzDBL+O6H4ykT8uEgNmP6gHPiXmIRYwOU27NG00cDcF7KA4lgOH2LoAY2GaREbppKMrbFn1Qg="));
    pplx::task<void> loginTask = httpClient->request(methods::POST, builder.to_string(), requestBody).then([](http_response response){
        if (response.status_code() != 200) {
            //  TODO : 包装异常对象
            throw "/account/v1/login is not 200";
        }
        return response.extract_json();
    }).then([=](json::value value){
        if (value.is_object() == false) {
            throw "response is not a object";
        }
        json::object o = value.as_object();
        auto userId = o[U("user_id")].as_integer();
        userInfo->setUserId(userId);
        auto mail = QString::fromStdString(utility::conversions::to_utf8string(o[U("mail")].as_string()));
        userInfo->setMail(mail);
        auto phone = QString::fromStdString(utility::conversions::to_utf8string(o[U("phone")].as_string()));
        userInfo->setPhone(phone);
        auto userName = QString::fromStdString(utility::conversions::to_utf8string(o[U("name")].as_string()));
        userInfo->setUserName(userName);
        auto gender = o[U("gender")].as_integer();
        userInfo->setGender(gender);
        auto avatar = QString::fromStdString(utility::conversions::to_utf8string(o[U("avatar")].as_string()));
        userInfo->setAvatar(avatar);
    });

    try {
        loginTask.get();
    } catch (std::string &e) {
        qDebug() << QString::fromStdString(e);
        errMsg->m_isOk = false;
        errMsg->m_errMsg = QString::fromStdString(e);
        return false;
    }
    return true;
}
