#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DialogPixelSetting.h"
#include "Config.h"
#include "GrayWhiteButton.h"

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
    ui->label_color->setStyleSheet("QLabel { background-color: white; }");

    m_canvas.init(ui->openGLWidget);
    m_canvas.setCanvasSize(g_config.m_rowNumber, g_config.m_rowNumber);
    m_canvas.initColor(g_config.m_colorStr);
    ui->openGLWidget->setCanvas(&m_canvas);

    initColorButton();
}

void MainWindow::initColorButton()
{
    std::vector<std::string> colorStr = g_config.m_colorStr;
    // 在 colorStr 的开头插入一个灰白渐变的按钮
    colorStr.insert(colorStr.begin(), "#C0C0C0");  // 灰色，作为默认渐变色的代表

    for (int i = 0; i < colorStr.size(); ++i) {
        // 创建按钮
        QPushButton *colorButton = nullptr;  

        if (i == 0) {
            colorButton = new GrayWhiteButton(this);   //使用 GrayWhiteButton
        } else {
            // 其他按钮使用 colorStr 中的颜色
            colorButton = new QPushButton(this);
            colorButton->setStyleSheet("background-color: " + QString::fromStdString(colorStr[i]));
        }

        // 将按钮添加到布局
        ui->gridLayout_colors->addWidget(colorButton, i / 5, i % 5);  // 每行最多显示5个按钮

        // 连接点击事件
        connect(colorButton, &QPushButton::clicked, this, [this, i]() {
            onColorClicked(i);  // 传递颜色的索引
        });
    }
}

void MainWindow::onColorClicked(int colorIndex)
{
    m_canvas.setPainterColor(colorIndex);
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
        m_canvas.setCanvasSize(g_config.m_rowNumber, g_config.m_rowNumber);
        m_canvas.render();
    }
}

