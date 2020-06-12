#ifndef LOGIN_OUT_MGR_H
#define LOGIN_OUT_MGR_H

#include <QObject>

class LoginOutMgr : public QObject
{
    Q_OBJECT
public:
    explicit LoginOutMgr(QObject *parent = nullptr);

signals:

};

#endif // LOGIN_OUT_MGR_H
