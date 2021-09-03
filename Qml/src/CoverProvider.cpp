#include "CoverProvider.hpp"

std::string CoverProvider::authcode = "";
// std::string CoverProvider::filepath = "";

QPixmap CoverProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize){
    Global::log("Loading cover...");
    // I don't think this is actually nessicary
    // todo("implement authcode into the cover");

    QPixmap pixmap = QPixmap(":/defaultCover");

    if (id == "default"){
        *size = pixmap.size();
        return pixmap;
    }


    if (not id.isEmpty()){
        std::string coverData = Global::runFFmpegCmd(authcode + " -i \"/" + id.toStdString() + "\" -map 0:v? -c:v:1 png -disposition:v:1 attached_pic -f apng", false, false);

        // If there's less than 64 bytes, assume its just an error message (crude, but effective)
        if (coverData.length() > 64)
            pixmap.loadFromData(reinterpret_cast<uchar*>(coverData.data()), coverData.size(), "png");
    }

    *size = pixmap.size();

    Global::ui->setProperty("color", getAverageColor(pixmap).name());

    return pixmap;
}
// This totally works. Not entirely sure why. But it's SICK.
QColor CoverProvider::getAverageColor(const QPixmap& pix){
    QImage img = pix.toImage();
    int count = 0;
    int totalR = 0, totalG = 0, totalB = 0;
    int r = 0, g = 0, b = 0;

    for (int x = 0; x < pix.width(); ++x){
        for (int y = 0; y < pix.height(); ++y){
            QColor(img.pixel(x, y)).getRgb(&r, &g, &b);
            totalR += r;
            totalG += g;
            totalB += b;
            count  += 1;
        }
    }
    // _debug(totalR)
    // _debug(totalG)
    // _debug(totalB)
    // _debug(count)

    return QColor(totalR / count, totalG / count, totalB / count);
}