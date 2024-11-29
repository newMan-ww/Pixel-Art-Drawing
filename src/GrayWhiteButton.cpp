#include "GrayWhiteButton.h"
#include <QPainter>

GrayWhiteButton::GrayWhiteButton(QWidget *parent)
    : QPushButton(parent) {
    setAutoFillBackground(true);  // 确保按钮的背景填充
}

void GrayWhiteButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 获取按钮的宽度和高度
    int width = this->width();
    int height = this->height();

    // 设置每个小块的尺寸
    int blockSize = 8;  // 每个小块的宽度和高度
    int numBlocksX = width / blockSize;  // 水平方向上小块的数量
    int numBlocksY = height / blockSize; // 垂直方向上小块的数量

    // 绘制灰白交替的小像素块
    for (int y = 0; y < numBlocksY; ++y) {
        for (int x = 0; x < numBlocksX; ++x) {
            QColor color = ((x + y) % 2 == 0) ? QColor(192, 192, 192) : QColor(128, 128, 128); // 交替颜色
            painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, color);  // 绘制小块
        }
    }

    // 不调用 QPushButton::paintEvent(event)，以避免绘制默认的背景和文本
    // 如果需要绘制文本，可以通过 QPainter 自行绘制文本：
    painter.setPen(QColor(0, 0, 0));  // 设置文字颜色为黑色
    painter.drawText(rect(), Qt::AlignCenter, text());  // 在按钮的中心绘制文字
}

