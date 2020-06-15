#include "captcha.h"
#include <cpprest/http_client.h>
#include "httpclientmgr.h"
#include "errmsg.h"
#include "sexception.h"

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

GetCaptchaResponse::GetCaptchaResponse(QObject *parent)
    :QObject(parent)
{

}

QPixmap GetCaptchaResponse::getCaptchaImg()
{
    return m_captchaImg;
}

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
    utility::string_t getCaptchaUrl(U("/captcha/v1/captcha"));
    utility::string_t getCaptchaFile;
    uri_builder builder(getCaptchaUrl);
    pplx::task<QPixmap> getCaptchaRequest = httpClient->request(methods::GET, builder.to_string()).then([=](http_response response){
        if (response.status_code() != 200){
            SException::throw_parse_api_error_exception(response, getCaptchaUrl);
        }
        return response.extract_json();
    }).then([=, &getCaptchaFile](web::json::value value){
        auto obj = value.as_object();
        auto captchaId = obj[U("captcha_id")].as_string();
        auto captchaUrl = obj[U("captcha_url")].as_string();
        std::string stdCaptchaId = utility::conversions::to_utf8string(captchaId);
        pResp->m_captchaId = QString::fromStdString(stdCaptchaId);
        uri_builder builder(captchaUrl);
        getCaptchaFile = captchaUrl;
        return httpClient->request(methods::GET, builder.to_string());
    }).then([=](http_response response){
        if (response.status_code() != 200){
            SException::throw_parse_api_error_exception(response, getCaptchaFile);
        }
        return response.extract_vector();
    }).then([](std::vector<unsigned char> vec){
        QPixmap captcha;
        bool isOk = captcha.loadFromData(vec.data(), vec.size());
        if (false == isOk) {
            SException exception(PIXMAP_IS_INVALID, "captcha pixmap is invalid");
            throw exception;
        }
        return captcha;
    });

    QPixmap captchaPixmap;
    try {
        captchaPixmap = getCaptchaRequest.get();
    }
    catch(std::exception &e)
    {
        //  TODO : 日志记录

        pErrMsg->m_isOk = false;
        //  SExpection
        std::exception *p = &e;
        SException *sExpection = dynamic_cast<SException *>(p);
        if (sExpection != nullptr) {
            pErrMsg->m_result = sExpection->getResult();
            pErrMsg->m_errMsg = sExpection->getMsg();
            return false;
        }
        //  std::exception
        pErrMsg->m_result = QString::fromStdString(e.what());
        return false;
    }
    pResp->m_captchaImg = captchaPixmap;
    return true;
}


