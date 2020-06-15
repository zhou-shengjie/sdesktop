#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>
#include <functional>
#include "cpprest/http_msg.h"
#include "cpprest/details/basic_types.h"

#define NOT_JSON_OBJECT "http response is not a valid json object."
#define HTTP_CODE_NOT_200 "http code is not 200."
#define PIXMAP_IS_INVALID "pixmap is in valid."
#define PARSE_API_ERROR_FAILED "parse api error failed."



class SExceptionBase : public std::exception {
public:
    SExceptionBase();
    void setResult(const std::string &result);
    void setMsg(const std::string &msg);
    virtual char const* what() const;

public:
    static std::function<void(web::http::http_response response, utility::string_t url)> throw_parse_api_error_exception;

protected:
    std::string m_result;
    std::string m_msg;
    std::string m_out;
};

class SException : public SExceptionBase
{
public:
    SException() = default;
};

class SApiException : public SExceptionBase
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
