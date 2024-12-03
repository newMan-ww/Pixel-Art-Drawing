#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DialogPixelSetting.h"
#include "Config.h"
#include "GrayWhiteButton.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>

std::vector<uint16_t> g_margin = {0, 1, 2, 3};
 
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
    ui->label_function->setStyleSheet("QLabel { background-color: white; }");
    ui->label_line->setStyleSheet("QLabel { background-color: white; }");

    m_canvas.init(ui->openGLWidget);
    m_canvas.setCanvasSize(g_config.m_rowNumber, g_config.m_columnNumber);
    m_canvas.initColor(g_config.m_colorStr);
    ui->openGLWidget->setCanvas(&m_canvas);

    ui->checkBox_row->setChecked(true);
    ui->checkBox_col->setChecked(true);
    ui->checkBox_display->setChecked(true);

    for(int i =0; i < g_margin.size(); i++)
    {
        ui->comboBox_margin->addItem(QString::number(g_margin[i]));
    }
    ui->comboBox_margin->setCurrentIndex(0);

    initColorButton();
}

void MainWindow::initColorButton()
{
    // 移除布局中的所有控件
    for (int i = ui->gridLayout_colors->count() - 1; i >= 0; --i) {
        QLayoutItem* item = ui->gridLayout_colors->itemAt(i);
        if (item) {
            QWidget* widget = item->widget();
            if (widget) {
                ui->gridLayout_colors->removeWidget(widget);  // 从布局中移除控件
                widget->setParent(nullptr);    // 取消控件与布局的父子关系
            }
        }
    }

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
        m_canvas.setCanvasSize(g_config.m_rowNumber, g_config.m_columnNumber);
        m_canvas.render();
    }
}


void MainWindow::on_checkBox_row_clicked(bool checked)
{
    m_canvas.setShowRowLine(checked);  
    m_canvas.render();
    ui->openGLWidget->update();
}


void MainWindow::on_checkBox_col_clicked(bool checked)
{
    m_canvas.setShowColLine(checked);  
    m_canvas.render();
    ui->openGLWidget->update();
}


void MainWindow::on_checkBox_display_clicked(bool checked)
{
    m_canvas.setShowRowLine(checked);
    m_canvas.setShowColLine(checked);  
    m_canvas.render();
    ui->openGLWidget->update();
}


void MainWindow::on_comboBox_margin_currentIndexChanged(int index)
{
    m_canvas.setMargin(g_margin[index]);
    m_canvas.render();
    ui->openGLWidget->update();
}


void MainWindow::on_pushButton_import_txt_clicked()
{
    // 弹出文件选择对话框，让用户选择要加载的txt文件
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "./", "Text Files (*.txt)");

    // 如果用户取消了选择文件，则返回
    if (fileName.isEmpty()) {
        return;
    }

    // 打开文件流进行读取
    std::ifstream inFile(fileName.toStdString());

    // 判断文件是否打开成功
    if (!inFile.is_open()) {
        QMessageBox::warning(this, "打开失败", "无法打开文件进行读取！");
        return;
    }

    // 读取行列信息
    int row = 0, col = 0;
    std::string line;
    if (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string tmp;
        if (ss >> tmp >> row) {
            // 读取行数成功
        }
    }
    if (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string tmp;
        if (ss >> tmp >> col) {
            // 读取列数成功
        }
    }

    std::vector<std::string> colors;
    // 读取颜色信息
    if (std::getline(inFile, line)) {
        if (line == "Colors:") {  // 找到 Colors: 部分
            while (std::getline(inFile, line)) {
                if (line.empty()) {
                    break;  // 如果遇到空行，结束颜色部分
                }
                colors.push_back(line);  // 存储颜色
            }
        }
    }

    // 读取像素颜色信息
    std::vector<uint16_t> pixels;
    if (std::getline(inFile, line)) {
        if (line == "Pixels:") {  // 找到 Pixels: 部分
            while (std::getline(inFile, line)) {
                if (line.empty()) {
                    break;  // 如果遇到空行，结束像素数据部分
                }
                uint16_t pixelColor = std::stoi(line);  // 将像素颜色转换为整数
                pixels.push_back(pixelColor);  // 存储像素颜色
            }
        }
    }

    // 检查解析的数据是否正确
    if (pixels.size() != (row * col)) {
        QMessageBox::warning(this, "数据错误", "文件中的数据格式不正确！");
        return;
    }

    // 关闭文件
    inFile.close();

    // 将解析的数据应用到画布（Canvas）上
    g_config.m_rowNumber = row;
    g_config.m_columnNumber = col;
    g_config.m_colorStr = colors;

    m_canvas.setCanvasSize(g_config.m_rowNumber, g_config.m_columnNumber);
    m_canvas.initColor(g_config.m_colorStr);
    m_canvas.setPixelSize(row * col);
    for(int i = 0; i < (row * col); i++)
    {
        m_canvas.setPixelColor(i, pixels[i]);
    }

    ui->openGLWidget->update();
}


void MainWindow::on_pushButton_export_txt_clicked()
{
    int row = m_canvas.getRow();
    int col = m_canvas.getCol();

    // 获取颜色列表和像素颜色
    std::vector<std::string> colors = g_config.m_colorStr;
    std::vector<uint16_t> pixels = m_canvas.getPixelColors();

    // 如果像素数据的大小与画布的行列数不一致
    if (pixels.size() != (row * col)) {
        // 弹出错误提示框
        QMessageBox::warning(this, "数据错误", "像素数据与画布大小不匹配！");
        return;
    }

    // 弹出文件保存对话框，选择文件保存路径
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "./", "Text Files (*.txt)");

    // 如果用户取消了保存，fileName 会是空字符串
    if (fileName.isEmpty()) {
        return;
    }

    // 打开文件流进行写入
    std::ofstream outFile(fileName.toStdString());

    // 判断文件是否打开成功
    if (!outFile.is_open()) {
        QMessageBox::warning(this, "保存失败", "无法打开文件进行写入！");
        return;
    }

    // 写入行列信息
    outFile << "Rows: " << row << "\n";
    outFile << "Cols: " << col << "\n";

    // 写入颜色信息
    outFile << "Colors:\n";
    for (const auto& color : colors) {
        outFile << color << "\n";
    }

    outFile << "\n";  // 在颜色信息后添加空白行

    // 写入像素颜色数据
    outFile << "Pixels:\n";
    for (size_t i = 0; i < pixels.size(); ++i) {
        outFile << pixels[i] << "\n";
    }

    // 关闭文件
    outFile.close();

    // 弹出提示框告知用户保存成功
    QMessageBox::information(this, "保存成功", "数据已成功保存到文件！");
}


void MainWindow::on_pushButton_import_pic_clicked()
{

}


void MainWindow::on_pushButton_export_pic_clicked()
{

}

