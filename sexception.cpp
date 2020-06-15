#include "sexception.h"
#include <cpprest/details/basic_types.h>


std::function<void(web::http::http_response response, utility::string_t url)> SExceptionBase::throw_parse_api_error_exception = [](web::http::http_response response, utility::string_t url){
    //  解析apiServer返回的错误
    SApiException exception;
    pplx::task<web::json::value> getErrTask = response.extract_json();
    try {
        web::json::value value = getErrTask.get();
        //  解析错误成功
        exception.setUrl(url);
        exception.setHttpCode(response.status_code());
        std::string result = utility::conversions::to_utf8string(value[U("result")].as_string());
        exception.setResult(result);
        std::string msg = utility::conversions::to_utf8string(value[U("msg")].as_string());
        exception.setMsg(msg);
    } catch (std::exception &e) {
        //  解析错误失败，错误不是有效的json object
        exception.setUrl(url);
        exception.setHttpCode(response.status_code());
        exception.setResult(PARSE_API_ERROR_FAILED);
        exception.setMsg(e.what());
    }
    throw exception;
};

SExceptionBase::SExceptionBase()
{
    //m_json = json::value::object();
}

void SExceptionBase::setResult(const std::string &result)
{
    m_result = result;
}

void SExceptionBase::setMsg(const std::string &errMsg)
{
    m_msg = errMsg;
    //m_json[U("msg")] = json::value(utility::conversions::to_string_t(errMsg));
}

char const* SExceptionBase::what() const
{
    return m_result.c_str();
}

void SApiException::setHttpCode(int httpCode)
{
    m_httpCode = httpCode;
    //m_json[U("httpCode")] = json::value(httpCode);
}

void SApiException::setUrl(const utility::string_t &url)
{
    m_url = utility::conversions::to_utf8string(url);
    //m_json[U("url")] = json::value(url);
}
