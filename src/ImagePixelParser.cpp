#include "ImagePixelParser.h"
#include <QImage>
#include <QColor>
#include <QMessageBox>
#include <unordered_map>
#include <QFileDialog>

#include "functions.h"

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
    float blockWidth = static_cast<float>(imgWidth) / cols;  // 使用浮点数计算
    float blockHeight = static_cast<float>(imgHeight) / rows;

    std::unordered_map<QString, uint16_t, QStringHasher> colorMap;  // 使用自定义的哈希函数
    std::vector<std::string> colorList;

    pixels.clear();
    colorList.clear();

    // 遍历所有的像素块
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // 获取像素块中心点的坐标以获得更准确的颜色
            int x = static_cast<int>((j + 0.5) * blockWidth);  // 中心点的 x 坐标
            int y = static_cast<int>((i + 0.5) * blockHeight); // 中心点的 y 坐标

            // 确保 x 和 y 在图像边界内
            x = std::min(x, imgWidth - 1);
            y = std::min(y, imgHeight - 1);

            int flippedY = imgHeight - y - 1;

            // 获取像素块的颜色
            QColor pixelColor = image.pixelColor(x, flippedY);

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

// 根据像素点和颜色生成图片
void ImageParser::generateImageFromPixelsAndColors(int rows, int cols, 
                                                   const std::vector<uint16_t>& pixels, 
                                                   const std::vector<std::string>& colors, 
                                                   int pixelSize, 
                                                   const QString& outputPath)
{
    int imgWidth = cols * pixelSize;
    int imgHeight = rows * pixelSize;

    QImage image(imgWidth, imgHeight, QImage::Format_RGB32);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int pixelIndex = i * cols + j;
            uint16_t colorIndex = pixels[pixelIndex];

            if (colorIndex == 0) { // 默认背景颜色
                image.fill(Qt::white);
                continue;
            }

            // 转换颜色字符串为 QColor
            QColor color(QString::fromStdString(colors[colorIndex - 1]));
            int startX = j * pixelSize;
             int startY = (rows - 1 - i) * pixelSize; // 翻转 Y 轴方向

            for (int x = startX; x < startX + pixelSize; ++x) {
                for (int y = startY; y < startY + pixelSize; ++y) {
                    image.setPixelColor(x, y, color);
                }
            }
        }
    }

    if (!image.save(outputPath)) {
        QMessageBox::warning(nullptr, 
                            QString::fromStdString(GBKToUTF8("失败")), 
                            QString::fromStdString(GBKToUTF8("图片导出失败！")));
    } else {
        QMessageBox::information(nullptr, 
                            QString::fromStdString(GBKToUTF8("完成")), 
                            QString::fromStdString(GBKToUTF8("图片已成功导出！")));
    }
}

// 将 RGB 值转换为颜色的十六进制表示字符串
QString ImageParser::colorToString(int r, int g, int b)
{
    return QString("#%1%2%3")
            .arg(r, 2, 16, QChar('0'))
            .arg(g, 2, 16, QChar('0'))
            .arg(b, 2, 16, QChar('0'));
}