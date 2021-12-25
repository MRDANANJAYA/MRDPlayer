#ifndef VIDEOWIDGETSURFACE_H
#define VIDEOWIDGETSURFACE_H

#include <QObject>

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QImage>
#include <QVideoFrame>
#include <QLabel>

class PlayerFrame : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    PlayerFrame(QObject *parent = nullptr);
    void stopVideo();
Q_SIGNALS:
    void fnSurfaceStopped(QPixmap pix);

private slots:
    void fnClearPixmap();

private:
    QPixmap Image;
    QImage::Format imgFormat;
    QVideoFrame CFrame;

    bool Videostart(const QVideoSurfaceFormat &format);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

    bool isFormatSupported(const QVideoSurfaceFormat &format) const;

    bool present(const QVideoFrame &frame);
    QObject * QAbstractVideoSurface;
};

#endif
