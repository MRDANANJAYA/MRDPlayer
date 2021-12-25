

#include "MRDplayerframe.h"
#include <QtWidgets>
#include <qvideosurfaceformat.h>
#include <QAbstractVideoSurface>

PlayerFrame::PlayerFrame(QObject *parent)
    : imgFormat(QImage::Format_Invalid)
    , QAbstractVideoSurface(parent)
{

}

bool PlayerFrame::Videostart(const QVideoSurfaceFormat &format)
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize Size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !Size.isEmpty())
    {
        this->imgFormat = imageFormat;
        QAbstractVideoSurface::start(format);
        return true;

    }
    else return false;
}

void PlayerFrame::fnClearPixmap()
{
    Image = QPixmap();
}

void PlayerFrame::stopVideo()
{
    QAbstractVideoSurface::stop();
}

QList<QVideoFrame::PixelFormat> PlayerFrame::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool PlayerFrame::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid && !size.isEmpty() && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool PlayerFrame::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size())
    {
        setError(IncorrectFormatError);
        stop();
        return false;
    }
    else
    {
        if (!Image.isNull())
        {
             fnSurfaceStopped(Image);
        }

        CFrame = frame;
        if (CFrame.map(QAbstractVideoBuffer::ReadOnly))
        {
            QImage image(
                    CFrame.bits(),
                    CFrame.width(),
                    CFrame.height(),
                    CFrame.bytesPerLine(),
                    imgFormat);
            if (Image.isNull())
            {
                    Image = QPixmap::fromImage(image.copy(image.rect()));
            }
            CFrame.unmap();
        }
        return true;
    }
}
