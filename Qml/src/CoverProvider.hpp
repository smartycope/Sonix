#pragma once

#include <QQuickImageProvider>
#include <QPixmap>
#include <QImage>
#include <QString>
#include <QQuickWindow>
#include "Global.hpp"
#include <QColor>


class CoverProvider: public QQuickImageProvider{
  public:
    CoverProvider(): QQuickImageProvider(QQuickImageProvider::Pixmap) { }

    static std::string authcode;
    // static std::string filepath;

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

  private:
    QColor getAverageColor(const QPixmap& pix);
};