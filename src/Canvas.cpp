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

void Canvas::printPixels(uint16_t row, uint16_t col)
{
    m_row = row;
    m_col = col;

    if (m_openGL) {
        m_openGL->update();
    }
}

void Canvas::render()
{
    for (uint16_t i = 0; i < m_row; ++i) {
        for (uint16_t j = 0; j < m_col; ++j) {
            float x = j * (m_pixelWidth + m_margin) + m_offsetX;
            float y = i * (m_pixelHeight + m_margin) + m_offsetY;

            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f); // 设置像素颜色为白色
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
