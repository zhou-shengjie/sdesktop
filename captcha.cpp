#include "captcha.h"
#include <cpprest/http_client.h>
#include "httpclientmgr.h"
#include <QDebug>

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

Captcha::Captcha(QObject *parent) : QObject(parent)
{

}

GetCaptchaResponse Captcha::getCaptcha(const HttpClientMgr* pHttpClient)
{
    GetCaptchaResponse ret;
    auto httpClient = pHttpClient->getHttpClient();
    uri_builder builder(U("/captcha/v1/captcha"));
    pplx::task<QPixmap> getCaptchaRequest = httpClient->request(methods::GET, builder.to_string()).then([](http_response response){
        if (response.status_code() != 200){
            //  TODO : 包装异常对象
            throw "/captcha/v1/captcha is not 200";
        }
        return response.extract_json();
    }).then([&](web::json::value value){
        if (value.is_object() == false) {
            //  TODO : 包装异常对象
            throw "response is not a object";
        }
        auto obj = value.as_object();
        auto captchaId = obj[U("captcha_id")].as_string();
        auto captchaUrl = obj[U("captcha_url")].as_string();
        std::string stdCaptchaId = utility::conversions::to_utf8string(captchaId);
        ret.m_captchaId = QString::fromStdString(stdCaptchaId);
        uri_builder builder(captchaUrl);
        return httpClient->request(methods::GET, builder.to_string());
    }).then([](http_response response){
        if (response.status_code() != 200){
            //  TODO : 包装异常对象
            throw "/captcha/v1/captcha is not 200";
        }
        return response.extract_vector();
    }).then([](std::vector<unsigned char> vec){
        QPixmap captcha;
        bool isOk = captcha.loadFromData(vec.data(), vec.size());
        if (false == isOk) {
            //  TODO : 包装异常对象
            throw "load pixmap failed";
        }
        return captcha;
    });

    QPixmap captchaPixmap;
    try {
        captchaPixmap = getCaptchaRequest.get();
    }catch(std::string e)
    {
        //  TODO : 日志记录
        qDebug() << QString::fromStdString(e);

        ret.m_isOk = false;
        ret.m_errMsg = QString::fromStdString(e);
        return ret;
    }
    ret.m_isOk = true;
    ret.m_captchaImg = captchaPixmap;
    emit getCaptchaFinished(true);
    return ret;
}
