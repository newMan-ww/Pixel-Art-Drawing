#include "MyOpenGLWidget.h"
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景色
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width(), 0, height(), -1, 1); // 设置投影坐标系范围
    glMatrixMode(GL_MODELVIEW);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
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
        m_isDragging = true;
        m_lastPos = event->pos(); // 记录鼠标按下时的位置
    }
}

// 处理鼠标移动事件
void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        QPoint delta = event->pos() - m_lastPos; // 计算鼠标移动的偏移量
        m_lastPos = event->pos();  // 更新最后的鼠标位置

        // 更新画布的位置
        if (m_canvas) {
            m_canvas->moveCanvas(delta.x(), delta.y()); // 将偏移量传递给Canvas
        }
        update();  // 重新绘制
    }
}

// 处理鼠标释放事件
void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false; // 停止拖动
    }
}
