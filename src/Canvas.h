#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <cstdint>
#include <vector>
#include <string>

struct Color
{
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    Color(float red, float green, float blue): r(red) ,g(green),b(blue){}
};

class MyOpenGLWidget;  // 前置声明

class Canvas : public QObject, protected QOpenGLFunctions
{
public:
    Canvas();
    ~Canvas();

    void init(MyOpenGLWidget* openGLWidget);

    void initColor(std::vector<std::string> str);

    void setCanvasSize(uint16_t row, uint16_t col);

    void render();  //重新绘制画布

    void moveCanvas(int dx, int dy);  // 添加移动画布的函数

    int getPixelWidth() const { return m_pixelWidth; }
    void setPixelWidth(int width) { m_pixelWidth = width; }

    int getPixelHeight() const { return m_pixelHeight; }
    void setPixelHeight(int height) { m_pixelHeight = height; }

    int getMargin() const { return m_margin; }
    void setMargin(int margin) { m_margin = margin; }

    int getoffsetX() const { return m_offsetX; }
    void setoffsetX(int offsetX) { m_offsetX = offsetX; }

    int getoffsetY() const { return m_offsetY; }
    void setoffsetY(int offsetY) { m_offsetY = offsetY; }

    int getCol() const { return m_col; }  // 获取列数
    int getRow() const { return m_row; }  // 获取行数

    int getPainterColor() const { return m_painterColor; }  // 获取画笔颜色
    void setPainterColor(uint16_t index) {
        if(index < m_colors.size())
        {
           m_painterColor = index;
        }
    }

    void setPixelColor(int index, uint16_t colorIndex) { m_pixelColors[index] = colorIndex; } // 设置指定像素的颜色
    const std::vector<uint16_t>& getPixelColors() const { return m_pixelColors; }

private:
    MyOpenGLWidget* m_openGL;

    int m_pixelWidth;  // 每个像素点的宽度
    int m_pixelHeight; // 每个像素点的高度
    int m_margin;      // 像素点之间的间隔宽度

    uint16_t m_row = 0;
    uint16_t m_col = 0;

    int m_offsetX;  // 记录画布的水平偏移量
    int m_offsetY;  // 记录画布的垂直偏移量

    std::vector<Color> m_colors;
    std::vector<uint16_t> m_pixelColors;     //存储每个像素点的颜色，uint16值对应m_colors对应索引的颜色

    uint16_t m_painterColor = 0;
};

#endif
