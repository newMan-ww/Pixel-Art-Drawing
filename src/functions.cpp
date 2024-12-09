#include "functions.h"
#include <windows.h>


std::string GBKToUTF8(const std::string& gbkStr)
{
    int wideSize = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, nullptr, 0);
    if (wideSize == 0) {
        return "";
    }

    std::wstring wideStr(wideSize, 0);
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, &wideStr[0], wideSize);

    int utf8Size = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Size == 0) {
        return "";
    }

    std::string utf8Str(utf8Size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], utf8Size, nullptr, nullptr);

    return utf8Str;
}

std::string UTF8ToGBK(const std::string& utf8Str)
{
    int wideSize = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    if (wideSize == 0) {
        return "";
    }

    std::wstring wideStr(wideSize, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wideStr[0], wideSize);

    int gbkSize = WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (gbkSize == 0) {
        return "";
    }

    std::string gbkStr(gbkSize, 0);
    WideCharToMultiByte(CP_ACP, 0, wideStr.c_str(), -1, &gbkStr[0], gbkSize, nullptr, nullptr);

    return gbkStr;
}