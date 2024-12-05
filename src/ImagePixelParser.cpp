#include "ImagePixelParser.h"
#include <QImage>
#include <QColor>
#include <QMessageBox>
#include <unordered_map>
#include <QFileDialog>

ImageParser::ImageParser()
{
    
}

ImageParser::~ImageParser()
{
    
}

// 自定义哈希函数
struct QStringHasher {
    size_t operator()(const QString& str) const {
        return qHash(str);  // 使用 Qt 的 qHash() 函数
    }
};

void ImageParser::parseImageToPixelsAndColors(const QString& imagePath, int rows, int cols,
                                              std::vector<uint16_t>& pixels,
                                              std::vector<std::string>& colors)
{
    QImage image(imagePath);

    if (image.isNull()) {
        QMessageBox::warning(nullptr, "Error", "Failed to load the image!");
        return;
    }

    // 计算每个像素块的宽度和高度
    int imgWidth = image.width();
    int imgHeight = image.height();
    int blockWidth = imgWidth / cols;
    int blockHeight = imgHeight / rows;

    // 如果图片的宽度或高度不能被行列数整除，处理最后一行和最后一列
    int extraWidth = imgWidth % cols;
    int extraHeight = imgHeight % rows;

    std::unordered_map<QString, uint16_t, QStringHasher> colorMap;  // 使用自定义的哈希函数
    std::vector<std::string> colorList;

    pixels.clear();
    colorList.clear();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // 计算当前像素块的左上角坐标
            int x = j * blockWidth;
            int y = i * blockHeight;

            // 处理最后一行和最后一列，确保不超出图片边界
            if (j == cols - 1) {
                x = imgWidth - blockWidth;  // 确保最后一列的像素块不会超出图片边界
            }
            if (i == rows - 1) {
                y = imgHeight - blockHeight;  // 确保最后一行的像素块不会超出图片边界
            }

            // 反转y坐标，解决图片上下颠倒问题
            int flippedY = imgHeight - y - 1;

            // 获取当前像素块的颜色（选择该像素块的左上角点）
            QColor pixelColor = image.pixelColor(x, flippedY);  // 使用翻转后的y坐标

            // 将 RGB 值转换为字符串
            QString colorStr = colorToString(pixelColor.red(), pixelColor.green(), pixelColor.blue());

            // 如果该颜色还没有出现过，则加入 colors 和 colorMap
            if (colorMap.find(colorStr) == colorMap.end()) {
                colorMap[colorStr] = colorList.size() + 1;  // 从 1 开始索引
                colorList.push_back(colorStr.toStdString());
            }

            // 获取颜色的索引，并将索引加入 pixels
            uint16_t colorIndex = colorMap[colorStr];
            pixels.push_back(colorIndex);
        }
    }

    colors = colorList;
}

// 将 RGB 值转换为颜色的十六进制表示字符串
QString ImageParser::colorToString(int r, int g, int b)
{
    return QString("#%1%2%3")
            .arg(r, 2, 16, QChar('0'))
            .arg(g, 2, 16, QChar('0'))
            .arg(b, 2, 16, QChar('0'));
}