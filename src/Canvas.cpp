#include "Canvas.h"
#include "MyOpenGLWidget.h"

std::vector<uint16_t> g_pixelSize = {
        3,
        6,
        9,
        12,
        15,
        18,
        21,
        24,
        27,
        30,
        33,
        36,
        39,
        42,
        45,
        48,
        51,
        54,
        57};

Canvas::Canvas()
    : m_openGL(nullptr), m_pixelWidth(21), m_pixelHeight(21), m_margin(0),
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

    m_colors.push_back(Color(-1.0,-1.0,-1.0));  //第一个元素为默认元素，用来指示无颜色

    for(int i = 0; i < colorStrings.size(); i++)
    {
        int hex = std::stoi(colorStrings[i].substr(1), nullptr, 16); // 去掉前缀 "#" 转换为十进制
        float r = ((hex >> 16) & 0xFF) / 255.0f; // 红色通道
        float g = ((hex >> 8) & 0xFF) / 255.0f;  // 绿色通道
        float b = (hex & 0xFF) / 255.0f;         // 蓝色通道

        m_colors.push_back(Color(r,g,b));
    }

    m_pixelColors.resize(m_row * m_col, 0);     //初始化每个像素的颜色
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
        for (uint16_t j = 0; j < m_col; ++j) {
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
                newPixelColors[newIndex] = 0;
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

            // 如果 colorIndex 为 0，表示要显示灰白交替的背景
            if (colorIndex == 0) {
                 paintBackground(x, y, i, j);
            } else {
                // 如果 colorIndex 不是 0，渲染正常颜色像素
                paintPixel(x, y, colorIndex);
            }

            paintLine(x, y);

        }
    }
}


void Canvas::paintLine(int x, int y)
{   
    // 绘制每个大像素点的分界线（黑色边框）
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); // 黑色边框

    // 绘制列分隔线（考虑 margin）
    if (m_showColLine)
    {
        // 绘制左边框（考虑 margin）
        glVertex2f(x, y);
        glVertex2f(x, y + m_pixelHeight + m_margin);  // 增加 margin 到右侧边界

        // 绘制右边框（考虑 margin）
        glVertex2f(x + m_pixelWidth + m_margin, y);  // 增加 margin 到右侧边界
        glVertex2f(x + m_pixelWidth + m_margin, y + m_pixelHeight + m_margin);  // 增加 margin 到右侧边界
    }

    // 绘制行分隔线（考虑 margin）
    if (m_showRowLine)
    {
        // 绘制上边框
        glVertex2f(x, y);
        glVertex2f(x + m_pixelWidth + m_margin, y);  // 增加 margin 到下侧边界

        // 绘制下边框
        glVertex2f(x, y + m_pixelHeight + m_margin);  // 增加 margin 到下侧边界
        glVertex2f(x + m_pixelWidth + m_margin, y + m_pixelHeight + m_margin);  // 增加 margin 到下侧边界
    }
    
    glEnd();
}

void Canvas::paintPixel(int x, int y, int colorIndex)
{
    Color c = m_colors[colorIndex];  // 获取该像素的颜色

    glBegin(GL_QUADS);
    glColor3f(c.r, c.g, c.b); // 设置像素颜色
    glVertex2f(x, y);
    glVertex2f(x + m_pixelWidth, y);
    glVertex2f(x + m_pixelWidth, y + m_pixelHeight);
    glVertex2f(x, y + m_pixelHeight);
    glEnd();
}

void Canvas::paintBackground(int x, int y, int i, int j)
{
    // 计算小方块的尺寸（让每个像素背景由多个小方块组成）
    int subPixelWidth = m_pixelWidth / 3;  // 设置每个小方块的宽度
    int subPixelHeight = m_pixelHeight / 3; // 设置每个小方块的高度

    // 绘制灰白交替的小方块
    for (int subY = 0; subY < 3; ++subY) {
        for (int subX = 0; subX < 3; ++subX) {
            // 计算灰白交替颜色
            Color bgColor = ((i + j + subX + subY) % 2 == 0) ? Color(0.9f, 0.9f, 0.9f) : Color(0.7f, 0.7f, 0.7f);

            float subXPos = x + subX * subPixelWidth;
            float subYPos = y + subY * subPixelHeight;

            glBegin(GL_QUADS);
            glColor3f(bgColor.r, bgColor.g, bgColor.b); // 设置小方块的背景颜色
            glVertex2f(subXPos, subYPos);
            glVertex2f(subXPos + subPixelWidth, subYPos);
            glVertex2f(subXPos + subPixelWidth, subYPos + subPixelHeight);
            glVertex2f(subXPos, subYPos + subPixelHeight);
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

void Canvas::expandPixelSize()
{
    if(m_pixelSizeIndex >= g_pixelSize.size() - 1)
    {
        return;
    }

    if(m_pixelSizeIndex == 18)
    {
        int i =1;
    }

    m_pixelSizeIndex++;

    m_pixelWidth = g_pixelSize[m_pixelSizeIndex];
    m_pixelHeight = g_pixelSize[m_pixelSizeIndex];
}

void Canvas::reducePixelSize()
{
    if(m_pixelSizeIndex <= 0)
    {
        return;
    }

    m_pixelSizeIndex--;

    m_pixelWidth = g_pixelSize[m_pixelSizeIndex];
    m_pixelHeight = g_pixelSize[m_pixelSizeIndex];
}
