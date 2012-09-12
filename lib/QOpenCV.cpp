#include "QOpenCV.hpp"

namespace QOpenCV {

static QVector<QRgb> s_greyTable;
QImage wrapImage( const cv::Mat& cvmat)
{
    int height = cvmat.rows;
    int width = cvmat.cols;

    if (cvmat.depth() == CV_8U && cvmat.channels() == 3) {
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if (cvmat.depth() == CV_8U && cvmat.channels() == 1) {
        QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_Indexed8);
        img.setColorTable(greyTable());
        return img;
    } else {
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}

const QVector<QRgb>& greyTable()
{
    if (!s_greyTable.size()) {
        for (int i = 0; i < 256; i++){
            s_greyTable.push_back(qRgb(i, i, i));
        }
    }
    return s_greyTable;
}

cv::Rect grow( const cv::Rect& rect, double scale )
{
    cv::Size size = rect.size();

    size.width = (scale * size.width);
    size.height = (scale * size.height);

    cv::Point offset = size - rect.size();
    offset.x /= 2;
    offset.y /= 2;

    return cv::Rect( rect.tl() - offset, size );
}

}
