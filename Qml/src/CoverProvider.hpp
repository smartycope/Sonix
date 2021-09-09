#pragma once

#include <QQuickImageProvider>
#include <QPixmap>
#include <QString>
#include <QColor>


class CoverProvider: public QQuickImageProvider{
  public:
    CoverProvider(): QQuickImageProvider(QQuickImageProvider::Pixmap) { }

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

  private:
    QColor getAverageColor(const QPixmap& pix);
};