#include "globalconfig.h"
#include <QFile>
#include <cpprest/filestream.h>

bool GlobalConfig::loadConfig()
{
    QFile file("config/config.json");
    bool isOk = file.open(QIODevice::ReadOnly);
    if (false == isOk) {
        return false;
    }
    auto raw = file.readAll();
    auto v = web::json::value::parse(raw.toStdString());
    if (false == v.is_object()) {
        return false;
    }
    auto obj = v.as_object();
    m_pConfig  = std::make_unique<web::json::object>(obj);
    return true;
}

QString GlobalConfig::getString(const QString &key)
{
    auto uKey = utility::conversions::to_string_t(key.toStdString());
    auto value =  m_pConfig->at(uKey).as_string();
    return QString::fromStdString(utility::conversions::to_utf8string(value));
}

int GlobalConfig::getInt(const QString &key)
{
    auto uKey = utility::conversions::to_string_t(key.toStdString());
    return  m_pConfig->at(uKey).as_integer();
}

double GlobalConfig::getReal(const QString &key)
{
    auto uKey = utility::conversions::to_string_t(key.toStdString());
    return  m_pConfig->at(uKey).as_double();
}


bool GlobalConfig::getBool(const QString &key)
{
    auto uKey = utility::conversions::to_string_t(key.toStdString());
    return  m_pConfig->at(uKey).as_bool();
}
