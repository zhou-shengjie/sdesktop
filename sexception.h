#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>
#include <functional>
#include <cpprest/details/basic_types.h>
#include <cpprest/http_msg.h>

#define NOT_JSON_OBJECT "http response is not a valid json object."
#define HTTP_CODE_NOT_200 "http code is not 200."
#define PIXMAP_IS_INVALID "pixmap is in valid."
#define PARSE_API_ERROR_FAILED "parse api error failed."


class SException : public std::exception
{
public:
    SException() = default;
    SException(const std::string &result, const std::string &msg);
    void setResult(const std::string &result);
    void setMsg(const std::string &msg);
    QString getResult();
    QString getMsg();
    virtual char const* what() const;

    public:
    //  noexcept(false)
    //  exception:
    //  1.解析apiserver错误成功
    //  2.解析apiserver错误失败，result:PARSE_API_ERROR_FAILED
    static std::function<void(const web::http::http_response &response, const utility::string_t &url)> throw_parse_api_error_exception;

protected:
        std::string m_result;
        std::string m_msg;
};

class SApiException : public SException
{
public:
    SApiException() = default;

    void setHttpCode(int httpCode);
    void setUrl(const utility::string_t &url);

protected:
    int m_httpCode;
    std::string m_url;
};

#endif // EXCEPTION_H
