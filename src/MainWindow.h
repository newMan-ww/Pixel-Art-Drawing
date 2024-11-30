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

    void on_checkBox_row_clicked(bool checked);

    void on_checkBox_col_clicked(bool checked);

    void on_checkBox_display_clicked(bool checked);

    void on_comboBox_margin_currentIndexChanged(int index);

private:
    void InitDialogControls();

    void initColorButton();

    void onColorClicked(int colorIndex);

private:
    Ui::MainWindow *ui;
    Canvas m_canvas;
};

#endif // MAINWINDOW_H
