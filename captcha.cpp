#include "captcha.h"
#include <cpprest/http_client.h>
#include "httpclientmgr.h"
#include "errmsg.h"
#include <QDebug>


using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

Captcha::Captcha(QObject *parent) : QObject(parent)
{

}

bool Captcha::getCaptcha(HttpClientMgr* pHttpClient, GetCaptchaResponse *pResp, ErrMsg *pErrMsg)
{
    //  入参检查
    Q_ASSERT(pResp != nullptr);
    Q_ASSERT(pErrMsg != nullptr);
    if (pResp == nullptr || pErrMsg == nullptr) {
        return false;
    }

    //  获取验证码
    auto httpClient = pHttpClient->getHttpClient();
    uri_builder builder(U("/captcha/v1/captcha"));
    pplx::task<QPixmap> getCaptchaRequest = httpClient->request(methods::GET, builder.to_string()).then([](http_response response){
        if (response.status_code() != 200){
            //  TODO : 包装异常对象
            throw "/captcha/v1/captcha is not 200";
        }
        return response.extract_json();
    }).then([=](web::json::value value){
        if (value.is_object() == false) {
            //  TODO : 包装异常对象
            throw "response is not a object";
        }
        auto obj = value.as_object();
        auto captchaId = obj[U("captcha_id")].as_string();
        auto captchaUrl = obj[U("captcha_url")].as_string();
        std::string stdCaptchaId = utility::conversions::to_utf8string(captchaId);
        pResp->m_captchaId = QString::fromStdString(stdCaptchaId);
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

        //  返回
        pErrMsg->m_isOk = false;
        pErrMsg->m_errMsg = QString::fromStdString(e);
        return false;
    }
    pResp->m_captchaImg = captchaPixmap;
    return true;
}
