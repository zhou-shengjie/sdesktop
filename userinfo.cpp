#include "userinfo.h"

UserInfo::UserInfo(QObject *parent)
    :QObject(parent)
{

}

int UserInfo::getUserId()
{
    return m_nUserId;
}

void UserInfo::setUserId(int userId)
{
    if (m_nUserId == userId){
        return;
    }
    m_nUserId = userId;
    emit userIdChanged();
}

QString UserInfo::getUserName()
{
    return m_strUserName;
}

void UserInfo::setUserName(const QString &userName)
{
    if (m_strUserName == userName) {
        return;
    }
    m_strUserName = userName;
    emit userNameChanged();
}

QString UserInfo::getAvatar()
{
    return m_strAvatar;
}

void UserInfo::setAvatar(const QString &avatar)
{
    if (m_strAvatar == avatar) {
        return;
    }
    m_strAvatar = avatar;
    emit avatarChanged();
}

int UserInfo::getGender()
{
    return m_nGender;
}

void UserInfo::setGender(int gender)
{
    if (m_nGender == gender) {
        return;
    }
    m_nGender = gender;
    emit genderChanged();
}

QString UserInfo::getMail()
{
    return m_strMail;
}

void UserInfo::setMail(const QString &mail)
{
    if (m_strMail == mail) {
        return;
    }
    m_strMail = mail;
    emit mailChanged();
}

QString UserInfo::getPhone()
{
    return m_strPhone;
}

void UserInfo::setPhone(const QString &phone)
{
    if (m_strPhone == phone){
        return;
    }
    m_strPhone = phone;
    emit phoneChanged();
}
