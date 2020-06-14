#ifndef USERINFO_H
#define USERINFO_H

#include <QObject>

class UserInfo: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(int gender READ getGender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString mail READ getMail WRITE setMail NOTIFY mailChanged)
    Q_PROPERTY(QString phone READ getPhone WRITE setPhone  NOTIFY phoneChanged)

public:
    explicit UserInfo(QObject *parent = nullptr);

    //  userId
    int getUserId();
    void setUserId(int userId);
    //  userName
    QString getUserName();
    void setUserName(const QString &userName);
    //  avatar
    QString getAvatar();
    void setAvatar(const QString &avatar);
    //  gender
    int getGender();
    void setGender(int gender);
    //  mail
    QString getMail();
    void setMail(const QString &mail);
    // phone
    QString getPhone();
    void setPhone(const QString &phone);

signals:
    void userIdChanged();
    void userNameChanged();
    void avatarChanged();
    void genderChanged();
    void mailChanged();
    void phoneChanged();

protected:
    int m_nUserId;
    QString m_strUserName;
    QString m_strAvatar;
    int m_nGender;
    QString m_strMail;
    QString m_strPhone;
};
#endif // USERINFO_H
