#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DialogPixelSetting.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitDialogControls();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitDialogControls()
{
    //将缩放按钮的对其方式设置为右对齐
    ui->horizontalLayout_2->setAlignment(ui->pushButton_hide_show, Qt::AlignRight);

    m_canvas.init(ui->openGLWidget);
    ui->openGLWidget->setCanvas(&m_canvas);
    reprintCanvse(true);
}

void MainWindow::on_pushButton_hide_show_clicked()
{
    if (ui->widget_control->isVisible()) {
        ui->widget_control->hide();  // 隐藏控制面板
        ui->pushButton_hide_show->setText("<<");  // 更新按钮文本

        ui->horizontalSpacer->changeSize(0,20,QSizePolicy::Fixed, QSizePolicy::Fixed);
        ui->verticalSpacer->changeSize(0,0,QSizePolicy::Fixed, QSizePolicy::Expanding);

    } else {
        ui->widget_control->show();  // 显示控制面板
        ui->pushButton_hide_show->setText(">>");  // 更新按钮文本

        ui->horizontalSpacer->changeSize(40,20,QSizePolicy::Expanding, QSizePolicy::Fixed);
        ui->verticalSpacer->changeSize(0,0,QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
}

void MainWindow::on_action_pixelSetting_triggered()
{
    DialogPixelSetting dlg;

    connect(&dlg, &DialogPixelSetting::printCanvse, this, &MainWindow::reprintCanvse);

    dlg.setModal(true);
    dlg.show();
    dlg.exec();
    g_config.write_config(CONFIG_FILE);
}

void MainWindow::reprintCanvse(bool shouldReprint)
{
    if(shouldReprint)
    {
        m_canvas.printPixels(g_config.m_rowNumber, g_config.m_rowNumber);
        m_canvas.render();
    }
}

