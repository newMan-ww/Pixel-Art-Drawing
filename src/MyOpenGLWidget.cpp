﻿#include "MyOpenGLWidget.h"
#include <QMouseEvent>

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), m_canvas(nullptr), m_isDragging(false)
{
}

MyOpenGLWidget::~MyOpenGLWidget()
{
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f); // 设置背景色
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width(), 0, height(), -1, 1); // 设置投影坐标系范围
    glMatrixMode(GL_MODELVIEW);

    m_init_x = width();
    m_init_y = height();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    m_magnification_x = (float)w / m_init_x;
    m_magnification_y = (float)h / m_init_y;
}

void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // 清空当前屏幕

    if (m_canvas) {
        m_canvas->render(); // 渲染像素
    }
}

void MyOpenGLWidget::setCanvas(Canvas* canvas)
{
    m_canvas = canvas;
}

// 处理鼠标按下事件
void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 先处理点击操作，避免拖拽状态影响颜色修改
        if (!m_isDragging) {

            // 设置拖拽模式
            m_isDragging = true;
            m_lastPos = event->pos(); // 记录鼠标按下时的位置
            m_pressPos = event->pos();
        }
    }
    else if (event->button() == Qt::RightButton) {
        // 右键按下时，开始右键长按
        m_isRightClicking = true;
    }
}

// 处理鼠标移动事件
void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
        if (m_isDragging) {
        // 计算鼠标移动的距离
        int deltaX = abs(event->pos().x() - m_pressPos.x());
        int deltaY = abs(event->pos().y() - m_pressPos.y());

        // 如果鼠标移动的距离大于 3 像素，才开始拖拽
        if (deltaX > 3 || deltaY > 3) {
            QPoint delta = event->pos() - m_lastPos; // 计算鼠标移动的偏移量
            m_lastPos = event->pos();  // 更新最后的鼠标位置

            // 更新画布的位置
            if (m_canvas) {
                m_canvas->moveCanvas(delta.x(), delta.y()); // 将偏移量传递给Canvas
            }
            update();  // 重新绘制
        }
    }

    //鼠标右键在按下过程中，碰到那个像素点的区域，就改变对应颜色
    if (m_isRightClicking) {
        // 右键长按并移动时，实时更新像素颜色
        int x = event->x();
        int y = event->y();

        x /= m_magnification_x;
        y /= m_magnification_y;

        // 计算相对画布的坐标（偏移量）
        x -= m_canvas->getoffsetX();
        y += m_canvas->getoffsetY();

        y = height() / m_magnification_y - y;  // OpenGL 的 y 坐标从底部开始增大

        // 计算鼠标当前位置对应的像素块的行列
        int row = y / (m_canvas->getPixelHeight() + m_canvas->getMargin());
        int col = x / (m_canvas->getPixelWidth() + m_canvas->getMargin());

        if (!isValidIndex(row, col)) {
            return;
        }

        // 获取该像素块的索引
        int pixelIndex = row * m_canvas->getCol() + col;

        // 设置该像素块的颜色（使用画笔颜色作为点击时的颜色）
        m_canvas->setPixelColor(pixelIndex, m_canvas->getPainterColor());

        // 更新画布并重新绘制
        if (m_canvas) {
            m_canvas->render();
            update();  // 触发窗口重绘
        }
    }
}

// 处理鼠标释放事件
void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        m_isDragging = false; // 停止拖动

        // 计算鼠标释放时的偏移量
        int deltaX = abs(event->pos().x() - m_pressPos.x());
        int deltaY = abs(event->pos().y() - m_pressPos.y());

        if(deltaX <= 3 && deltaY <= 3)
        {
            // 计算点击的位置
            int x = event->x(); 
            int y = event->y();

            x /= m_magnification_x;
            y /= m_magnification_y;

            // 计算相对画布的坐标（偏移量）
            x -= m_canvas->getoffsetX();
            y += m_canvas->getoffsetY();

            y = height() / m_magnification_y - y;  // OpenGL 的 y 坐标从底部开始增大

            // 计算点击的是哪一个像素块的行列
            int row = y / (m_canvas->getPixelHeight() + m_canvas->getMargin());
            int col = x / (m_canvas->getPixelWidth() + m_canvas->getMargin());

            if(!isValidIndex(row,col))
            {
                return;
            }

            // 获取该像素块的索引
            int pixelIndex = row * m_canvas->getCol() + col;

            // 设置该像素块的颜色（使用画笔颜色作为点击时的颜色）
            m_canvas->setPixelColor(pixelIndex, m_canvas->getPainterColor());

            // 更新画布并重新绘制
            if (m_canvas) {
                m_canvas->render();
                update();  // 触发窗口重绘
            }
        }
    }
    else if (event->button() == Qt::RightButton) {
        // 停止右键长按
        m_isRightClicking = false;
    }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    // 判断滚轮的方向
    if (event->angleDelta().y() > 0) {
        // 滚轮向上滚动，放大像素
        if (m_canvas) {
            m_canvas->expandPixelSize();
        }
    } else {
        // 滚轮向下滚动，缩小像素
        if (m_canvas) {
            m_canvas->reducePixelSize();
        }
    }

    // 更新 OpenGL 渲染
    update();  // 触发窗口重绘
}

bool MyOpenGLWidget::isValidIndex(int row, int col)
{
    return row < m_canvas->getRow() && row >= 0 && col < m_canvas->getCol() && col >= 0;
}
