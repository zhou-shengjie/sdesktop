#ifndef HTTPCLIENTMGR_H
#define HTTPCLIENTMGR_H

#include <QObject>
#include <cpprest/http_client.h>
#include "globalconfig.h"

class HttpClientMgr : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void setHost(QString host);
    std::shared_ptr<web::http::client::http_client> getHttpClient() const;

signals:

protected:
    std::shared_ptr<web::http::client::http_client> m_pHttpClient;

};

#endif // HTTPCLIENTMGR_H
