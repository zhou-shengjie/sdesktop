#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QObject>
#include <QQuickImageProvider>
#include <QMutex>

class ImageProvider : public QQuickImageProvider
{
public:
    ImageProvider();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

    bool addImage(const QString &id, const QPixmap &img);
    void deleteImage(const QString &id);

protected:
    QMap<QString ,QPixmap> m_mapId2Pixmap;
};

#endif // IMAGEPROVIDER_H
