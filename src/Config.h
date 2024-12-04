#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>
#include <vector>

#define CONFIG_FILE "config.json"

class Config
{
public: 
    Config();
    ~Config();

public:
    void read_config(std::string file);

    void write_config(std::string file);

public:
    uint16_t m_rowNumber;
    uint16_t m_columnNumber;

    std::vector<std::string> m_buttonColorStr;
    std::vector<std::string> m_CanvasColorStr;
};

extern Config g_config;

#endif