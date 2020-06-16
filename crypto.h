#ifndef CRYPTO_H
#define CRYPTO_H

#include <QString>
#include "errmsg.h"

class HttpClientMgr;

class Crypto
{
public:
    Crypto();
    static bool getPublicKey(HttpClientMgr *pHttpClientMgr ,QByteArray &publicKey);
    static bool rsaPublicEncrypt(const QByteArray &publicKey, const QByteArray &original, QByteArray &cipherText);


};

#endif // CRYPTO_H
