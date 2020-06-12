#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

#include <QObject>
#include <cpprest/json.h>

class GlobalConfig : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE bool loadConfig();
    Q_INVOKABLE QString getString(const QString &key);
    Q_INVOKABLE int getInt(const QString &key);
    Q_INVOKABLE double getReal(const QString &key);
    Q_INVOKABLE bool getBool(const QString &key);

signals:

protected:
    std::unique_ptr<web::json::object> m_pConfig;
};

#endif // GLOBALCONFIG_H
