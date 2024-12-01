#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "Canvas.h"

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MyOpenGLWidget(QWidget *parent = nullptr);
    ~MyOpenGLWidget();

    void setCanvas(Canvas* canvas);

     void paintGL() override;

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *event) override;    // 添加鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event) override;     // 添加鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event) override;  // 添加鼠标释放事件
    void wheelEvent(QWheelEvent *event) override;          //鼠标滚轮事件

private:
    bool isValidIndex(int row, int col);

private:
    // 添加 Canvas 对象
    Canvas* m_canvas;
    bool m_isDragging;  // 用于标记是否正在拖动
    QPoint m_lastPos;   // 记录鼠标上次的位置，用来控制拉拽位置
    QPoint m_pressPos;   // 记录鼠标上次的位置，用来控制鼠标释放时要不要改变像素点颜色

    bool m_isRightClicking = false;//记录鼠标右键是否被按下

    int m_init_x;     //初始的x轴长度
    int m_init_y;     //初始的y轴长度
    float m_magnification_x = 1.0;  //x轴方向上的倍率，用来帮助界面被拉伸时，找到正确的像素点索引
    float m_magnification_y = 1.0;  //y轴方向上的倍率，用来帮助界面被拉伸时，找到正确的像素点索引
};

#endif // MYOPENGLWIDGET_H

