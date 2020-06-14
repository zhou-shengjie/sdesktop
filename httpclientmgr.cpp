#include "httpclientmgr.h"
#include "cpprest/asyncrt_utils.h"

void HttpClientMgr::setHost(QString host)
{
    auto uHost = utility::conversions::to_string_t(host.toStdString());
    m_pHttpClient = std::make_shared<web::http::client::http_client>(uHost);
}

std::shared_ptr<web::http::client::http_client> HttpClientMgr::getHttpClient() const
{
    if (m_pHttpClient != nullptr){
        return m_pHttpClient;
    }
    return nullptr;
}
