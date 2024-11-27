#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "Canvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_hide_show_clicked();

    void on_action_pixelSetting_triggered();

    void reprintCanvse(bool shouldReprint);

private:
    void InitDialogControls();

private:
    bool m_isDragging;  // 用于标记是否正在拖动
    QPoint m_lastPos;   // 记录鼠标上次的位置

private:
    Ui::MainWindow *ui;
    Canvas m_canvas;
};

#endif // MAINWINDOW_H
