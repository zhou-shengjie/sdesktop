#include "errmsg.h"
#include "sexception.h"

ErrMsg::ErrMsg(QObject *parent) : QObject(parent)
{

}

void Exception2ErrMsg(const std::exception &e, ErrMsg *pErrMsg)
{
    pErrMsg->m_isOk = false;
    //  SExpection
    const std::exception *p = &e;
    const SException *sExpection = dynamic_cast<const SException *>(p);
    if (sExpection != nullptr) {
        pErrMsg->m_result = sExpection->getResult();
        pErrMsg->m_errMsg = sExpection->getMsg();
    }
    //  std::exception
    pErrMsg->m_result = QString::fromStdString(e.what());
}
