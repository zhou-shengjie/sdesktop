#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

class UserInfo: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int userId MEMBER m_uUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString userName MEMBER m_strUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString avatar MEMBER m_strAvatar NOTIFY avatarChanged)
    Q_PROPERTY(int gender MEMBER m_uGender NOTIFY genderChanged)
    Q_PROPERTY(QString mail MEMBER m_strMail NOTIFY mailChanged)
    Q_PROPERTY(QString phone MEMBER m_strPhone NOTIFY phoneChanged)

public:
    explicit UserInfo(QObject *parent = nullptr);

signals:
    void userIdChanged();
    void userNameChanged();
    void avatarChanged();
    void genderChanged();
    void mailChanged();
    void phoneChanged();

public:
    bool m_isOk;
    QString m_errMsg;
    uint64_t m_uUserId;
    QString m_strUserName;
    QString m_strAvatar;
    uint8_t m_uGender;
    QString m_strMail;
    QString m_strPhone;
};
#endif // USERINFO_H
