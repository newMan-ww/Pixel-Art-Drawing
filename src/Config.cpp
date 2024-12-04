#include "Config.h"
#include "json.hpp"

#include <iostream>
#include <fstream>

// 为方便起见，使用库的别名
using json = nlohmann::json;

Config g_config;

Config::Config()
{

}

Config::~Config()
{
    
}

void Config::read_config(std::string fileName)
{
    std::ifstream file(fileName);
    
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开JSON文件" << std::endl;
        return;
    }
    
    // 读取文件内容到一个字符串中
    std::string jsonString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    
    // 关闭文件
    file.close();
    
    // 解析JSON字符串
    try {
        json j = json::parse(jsonString);

        m_rowNumber = j["RowNumber"].get<uint16_t>();
        m_columnNumber = j["ColumnNumber"].get<uint16_t>();

        // 解析颜色数组，并将其存入m_colors
        if (j.contains("colors")) {
            for (const auto& color : j["colors"]) {
                if (color.is_string()) {
                    m_buttonColorStr.push_back(color.get<std::string>());
                }
            }
        }
        
    } catch (const json::parse_error& e) {
        // 处理解析错误
        std::cerr << "解析JSON时出错: " << e.what() << std::endl;
        return;
    } catch (const std::exception& e) {
        // 处理其他可能的异常
        std::cerr << "发生异常: " << e.what() << std::endl;
        return;
    }
}

void Config::write_config(std::string fileName)
{
    json j;

    j["RowNumber"] = m_rowNumber;
    j["ColumnNumber"] = m_columnNumber;

    j["colors"] = m_buttonColorStr;  // 将颜色字符串数组直接写入JSON

    // 将JSON对象序列化为字符串
    std::string jsonString = j.dump(4); // 4表示缩进级别，使输出的JSON字符串更易读

    // 将字符串写入文件
    std::ofstream file(fileName);
    if (file.is_open()) {
        file << jsonString;
        file.close();
    } else {
        std::cerr << "无法打开文件以写入JSON数据" << std::endl;
        return;
    }
}