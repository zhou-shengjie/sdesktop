#ifndef ERRMSG_H
#define ERRMSG_H

#include <QObject>

class ErrMsg : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOk MEMBER m_isOk)
    Q_PROPERTY(QString errMsg MEMBER m_errMsg)

public:
    explicit ErrMsg(QObject *parent = nullptr);

signals:

public:
    bool m_isOk;
    QString m_errMsg;

};

#endif // ERRMSG_H
