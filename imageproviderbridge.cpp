#include "imageproviderbridge.h"

ImageProviderBridge::ImageProviderBridge(QObject *parent) : QObject(parent)
{

}

void ImageProviderBridge::setImageProvider(ImageProvider *pImageProvider)
{
    m_pImageProvider = pImageProvider;
}

bool ImageProviderBridge::addImage(const QString &id, const QPixmap &img)
{
    if (nullptr == m_pImageProvider) {
        return false;
    }
    m_pImageProvider->addImage(id, img);
    return true;
}

void ImageProviderBridge::deleteImage(const QString &id)
{
    if (nullptr == m_pImageProvider) {
        return;
    }
    m_pImageProvider->deleteImage(id);
}
