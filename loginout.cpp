#include "loginout.h"
#include "userinfo.h"
#include "errmsg.h"
#include "httpclientmgr.h"
#include <cpprest/http_client.h>
#include "sexception.h"
#include "crypto.h"
#include <QCryptographicHash>

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

LoginOut::LoginOut(QObject *parent) : QObject(parent)
{

}

bool LoginOut::login(HttpClientMgr *pHttpClient, UserInfo *userInfo, ErrMsg *errMsg, const QString &account, const QString &password)
{
    Q_ASSERT(pHttpClient != nullptr);
    Q_ASSERT(userInfo != nullptr);
    Q_ASSERT(errMsg != nullptr);
    if (pHttpClient == nullptr || userInfo == nullptr || errMsg == nullptr) {
        return false;
    }

    //  获取公钥
    QByteArray publicKey;
    if (Crypto::getPublicKey(pHttpClient, publicKey) == false) {
        return false;
    }
    //  密码sha1->toHex->公钥加密->base64
    auto sha1 = QCryptographicHash::hash(password.toLatin1(), QCryptographicHash::Sha1).toHex();
    QByteArray passwordWithEncrypt;
    if (Crypto::rsaPublicEncrypt(publicKey, sha1, passwordWithEncrypt) == false) {
        return false;
    }

    //  登录
    auto httpClient = pHttpClient->getHttpClient();
    utility::string_t loginUrl(U("/account/v1/signin"));
    uri_builder builder(loginUrl);
    json::value requestBody = json::value::object();
    requestBody[U("account")] = json::value(utility::conversions::to_string_t(account.toStdString()));
    requestBody[U("password")] = json::value(utility::conversions::to_string_t(passwordWithEncrypt.toStdString()));
    pplx::task<void> loginTask = httpClient->request(methods::POST, builder.to_string(), requestBody).then([=](http_response response){
        if (response.status_code() != 200) {
            SException::throw_http_code_not_ok_exception(response, loginUrl);
        }
        return response.extract_json();
    }).then([=](json::value value){
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
    } catch (std::exception &e) {
        Exception2ErrMsg(e, errMsg);
        return false;
    }
    return true;
}
