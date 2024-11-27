#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <cstdint>

class MyOpenGLWidget;  // 前置声明

class Canvas : public QObject, protected QOpenGLFunctions
{
public:
    Canvas();
    ~Canvas();

    void init(MyOpenGLWidget* openGLWidget);

    void printPixels(uint16_t row, uint16_t col);

    void render();  //重新绘制画布

    void moveCanvas(int dx, int dy);  // 添加移动画布的函数

private:
    MyOpenGLWidget* m_openGL;

    int m_pixelWidth;  // 每个像素点的宽度
    int m_pixelHeight; // 每个像素点的高度
    int m_margin;      // 像素点之间的间隔宽度

    uint16_t m_row;
    uint16_t m_col;

    int m_offsetX;  // 记录画布的水平偏移量
    int m_offsetY;  // 记录画布的垂直偏移量
};

#endif
