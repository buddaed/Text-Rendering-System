
#pragma once
#include "../wolf/wolf.h"
#include <string>
#include <map>


class TextTable
{
    public:
    TextTable();
    ~TextTable();

    void Load(std::string);
    void SetLanguage(std::string);
    std::string GetString(std::string) const;

    private:
    static std::map<std::string, std::string> english;
    static std::map<std::string, std::string> french;

    std::string greeting[2];
    std::string courseName[2];
    std::string language;
};