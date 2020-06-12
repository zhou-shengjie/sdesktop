#include "imageprovider.h"

ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    //  Note: this method may be called by multiple threads, so ensure the implementation of this method is reentrant.
    auto img = m_mapId2Pixmap.value(id);
    if (img.isNull() == true){
        //  TODO : default blank image
        QPixmap blankImg(100, 100);
        blankImg.fill(QColor(Qt::white).rgba());
        img = blankImg;
    }
    //  image original size
    *size = img.size();
    //  if request size in valid use request size , if not use original size.
    QSize retSize = img.size();
    if (requestedSize.width() > 0) {
        retSize.setWidth(requestedSize.width());
    }
    if (requestedSize.height() > 0) {
        retSize.setHeight(requestedSize.height());
    }
    //  image requested size
    img = img.scaled(retSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    return img;
}

bool ImageProvider::addImage(const QString &id, const QPixmap &img)
{
    if (true == img.isNull()){
        return false;
    }
    m_mapId2Pixmap.insert(id, img);
    return true;
}

void ImageProvider::deleteImage(const QString &id)
{
    m_mapId2Pixmap.remove(id);
}
