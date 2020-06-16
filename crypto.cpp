#include "crypto.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <cpprest/http_client.h>
#include "httpclientmgr.h"
#include "sexception.h"
#include <gsl/gsl>

using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

Crypto::Crypto()
{

}

bool Crypto::getPublicKey(HttpClientMgr *pHttpClientMgr ,QByteArray &publicKey)
{
    auto httpClient = pHttpClientMgr->getHttpClient();
    utility::string_t getPublicKeyUr(U("/encrypt/v1/publickey"));
    auto getPublicKeyTask = httpClient->request(methods::GET, getPublicKeyUr).then([=](http_response response){
        if (response.status_code() != 200) {
            SException::throw_http_code_not_ok_exception(response, getPublicKeyUr);
        }
        return response.extract_json();
    }).then([&publicKey](web::json::value value){
        auto getPublicKeyResp = value.as_object();
        std::string pk = utility::conversions::to_utf8string(getPublicKeyResp[U("public_key")].as_string());
        publicKey = QByteArray::fromBase64(QString::fromStdString(pk).toLatin1());
    });

    try {
        getPublicKeyTask.get();
    } catch (std::exception &e) {
        return false;
    }

    return true;
}

bool Crypto::rsaPublicEncrypt(const QByteArray &publicKey, const QByteArray &original, QByteArray &cipherText)
{
    BIO * bioMemPublicKey = nullptr;
    RSA *publicRsa = nullptr;
    unsigned char *pCipeherText = nullptr;
    //  defer
    auto _ = gsl::finally([&](){
        if (bioMemPublicKey != nullptr) BIO_free_all(bioMemPublicKey);
        if (publicRsa != nullptr) RSA_free(publicRsa);
        if (pCipeherText != nullptr) free(pCipeherText);
    });
    //  创建publicKey的bio_mem_buf
    bioMemPublicKey = BIO_new_mem_buf(publicKey.data(), -1);
    if (bioMemPublicKey == nullptr) {
        return false;
    }
    //  从bioMemPublicKey解析publicKey
    publicRsa = PEM_read_bio_RSA_PUBKEY(bioMemPublicKey, nullptr, nullptr, nullptr);
    if (publicRsa == nullptr) {
        return false;
    }

    //  长度
    int rsaSize = RSA_size(publicRsa);
    int originalSize = rsaSize - 42; //  RSA_size(rsa) - 42 for RSA_PKCS1_OAEP_PADDING
    int cipherTextSize = rsaSize;
    //  检查original长度是否超过密钥长度
    if (original.size() > originalSize) {
        return false;
    }
    pCipeherText = (unsigned char *)malloc(cipherTextSize);
    if (pCipeherText == nullptr) {
        return false;
    }
    memset(pCipeherText, 0, cipherTextSize);
    int ret = RSA_public_encrypt(original.size(), (const unsigned char *)original.data(), pCipeherText, publicRsa, RSA_PKCS1_OAEP_PADDING);
    if (ret < 0) {
        return false;
    }
    cipherText = QByteArray((const char *)pCipeherText, ret).toBase64();
    return true;
}
