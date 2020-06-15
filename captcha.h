#ifndef CAPTCHA_H
#define CAPTCHA_H

#include <QObject>
#include <QPixmap>

class HttpClientMgr;
class ErrMsg;

class GetCaptchaResponse: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPixmap captchaImg READ getCaptchaImg)
    Q_PROPERTY(QString captchaId MEMBER m_captchaId)

public:
    GetCaptchaResponse(QObject *parent = nullptr);
    QPixmap getCaptchaImg();


public:
    QPixmap m_captchaImg;
    QString m_captchaId;
};

class Captcha : public QObject
{
    Q_OBJECT
public:
    explicit Captcha(QObject *parent = nullptr);
    Q_INVOKABLE bool getCaptcha(HttpClientMgr* pHttpClient, GetCaptchaResponse *pResp, ErrMsg *pErrMsg);
};

#endif // CAPTCHA_H
