#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <string>

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
};

extern Config g_config;

#endif