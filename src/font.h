
#pragma once
#include "../wolf/wolf.h"
#include <map>
#include <string>

struct s_font
{
    wolf::Texture *sheet;
    int x, y, width, height, xoffset, yoffset, xadvance, page;
};

class Font
{
public:
    Font(std::string const, std::string const);
    ~Font();

    void init(std::string);

    int getSize() const;
    int getLineHeight() const;
    wolf::Texture **getFontsheets() const;
    s_font getChar(char const) const;

private:
    std::map<char, s_font> characters;
    wolf::Texture **tex;
    std::string PNG;

    int pages;
    int size;
    int lineHeight;
};