#ifndef IMAGEPROVIDERBRIDGE_H
#define IMAGEPROVIDERBRIDGE_H

#include <QObject>
#include "imageprovider.h"

class ImageProviderBridge : public QObject
{
    Q_OBJECT
public:
    explicit ImageProviderBridge(QObject *parent = nullptr);
    void setImageProvider(ImageProvider *pImageProvider);
    Q_INVOKABLE bool addImage(const QString &id, const QPixmap &img);
    Q_INVOKABLE void deleteImage(const QString &id);

signals:


protected:
    ImageProvider *m_pImageProvider;
};

#endif // IMAGEPROVIDERBRIDGE_H
