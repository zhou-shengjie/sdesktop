#ifndef CAPTCHA_H
#define CAPTCHA_H

#include <QObject>
#include <QPixmap>

class HttpClientMgr;

class GetCaptchaResponse
{
    Q_GADGET
    Q_PROPERTY(bool isOk MEMBER m_isOk)
    Q_PROPERTY(QString errMsg MEMBER m_errMsg)
    Q_PROPERTY(QPixmap captchaImg READ getCaptchaImg)
    Q_PROPERTY(QString captchaId MEMBER m_captchaId)

public:
    GetCaptchaResponse() = default;
    QPixmap getCaptchaImg() {
        return m_captchaImg;
    }

public:
    bool m_isOk;
    QString m_errMsg;
    QPixmap m_captchaImg;
    QString m_captchaId;
};

class Captcha : public QObject
{
    Q_OBJECT
public:
    explicit Captcha(QObject *parent = nullptr);
    Q_INVOKABLE GetCaptchaResponse getCaptcha(const HttpClientMgr* pHttpClient);

signals:
    void getCaptchaFinished(bool isOk);
};

#endif // CAPTCHA_H
