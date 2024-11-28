#include "Canvas.h"
#include "MyOpenGLWidget.h"

Canvas::Canvas()
    : m_openGL(nullptr), m_pixelWidth(20), m_pixelHeight(20), m_margin(1),
      m_offsetX(0), m_offsetY(0)
{
}

Canvas::~Canvas()
{
}

void Canvas::init(MyOpenGLWidget* openGLWidget)
{
    m_openGL = openGLWidget;

    if (m_openGL) 
    {
        m_openGL->makeCurrent(); // 确保 OpenGL 上下文处于活动状态
    }
}

void Canvas::initColor(std::vector<std::string> colorStrings)
{
    m_colors.clear();

    for(int i = 0; i < colorStrings.size(); i++)
    {
        int hex = std::stoi(colorStrings[i].substr(1), nullptr, 16); // 去掉前缀 "#" 转换为十进制
        float r = ((hex >> 16) & 0xFF) / 255.0f; // 红色通道
        float g = ((hex >> 8) & 0xFF) / 255.0f;  // 绿色通道
        float b = (hex & 0xFF) / 255.0f;         // 蓝色通道

        m_colors.push_back(Color(r,g,b));
    }

    m_pixelColors.resize(m_row * m_col, 1);     //初始化每个像素的颜色
}

void Canvas::setCanvasSize(uint16_t newRow, uint16_t newCol)
{
    // 临时保存旧的行列数据
    std::vector<uint16_t> oldPixelColors = m_pixelColors;

    // 更新行列数
    uint16_t oldRow = m_row;
    uint16_t oldCol = m_col;
    m_row = newRow;
    m_col = newCol;

    // 新的像素数据 vector，需要根据新行列大小重新分配空间
    std::vector<uint16_t> newPixelColors(m_row * m_col, 0); // 默认颜色值为 0

    // 将旧的像素数据迁移到新的 vector 中
    for (uint16_t i = 0; i < m_row; ++i) {
        for (uint16_t j = 0; j < m_row; ++j) {
            // 计算旧像素的索引
            uint16_t oldIndex = i * oldCol + j;
            // 计算新像素的索引
            uint16_t newIndex = i * newCol + j;

            if(oldIndex < oldPixelColors.size() && i < oldRow && j < oldCol)
            {
                newPixelColors[newIndex] = oldPixelColors[oldIndex];
            }
            else
            {
                newPixelColors[newIndex] = 1;
            }

            // 迁移旧数据到新位置

        }
    }

    // 重新赋值给 m_pixelColors
    m_pixelColors = std::move(newPixelColors);
}

void Canvas::render()
{
    for (uint16_t i = 0; i < m_row; ++i) {
        for (uint16_t j = 0; j < m_col; ++j) {
            float x = j * (m_pixelWidth + m_margin) + m_offsetX;
            float y = i * (m_pixelHeight + m_margin) + m_offsetY;

            // 获取当前像素的颜色索引，并找到对应的颜色
            uint16_t pixelIndex = i * m_col + j;
            uint16_t colorIndex = m_pixelColors[pixelIndex];
            Color c = m_colors[colorIndex];  // 获取该像素的颜色

            glBegin(GL_QUADS);
            glColor3f(c.r, c.g, c.b); // 设置像素颜色
            glVertex2f(x, y);
            glVertex2f(x + m_pixelWidth, y);
            glVertex2f(x + m_pixelWidth, y + m_pixelHeight);
            glVertex2f(x, y + m_pixelHeight);
            glEnd();
        }
    }
}

// 移动画布
void Canvas::moveCanvas(int dx, int dy)
{
    m_offsetX += dx;
    m_offsetY -= dy;
    // 每次移动后更新 OpenGL 渲染
    if (m_openGL) {
        m_openGL->update(); // 确保界面刷新
    }
}
