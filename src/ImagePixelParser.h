#ifndef IMAGEPIXELPARSER_H
#define IMAGEPIXELPARSER_H

#include <QString>
#include <vector>

//解析图片类
class ImageParser
{

public: 
    ImageParser();

    ~ImageParser();

    //解析图片的像素点，将解析数据放入colors和pixels中
    void ImageParser::parseImageToPixelsAndColors(const QString& imagePath, int rows, int cols,
                                              std::vector<uint16_t>& pixels,
                                              std::vector<std::string>& colors);

    QString ImageParser::colorToString(int r, int g, int b);
};

#endif IMAGEPIXELPARSER_H