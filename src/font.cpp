#include "font.h"
#include <iostream>
#include <fstream>

Font::Font(std::string const png, std::string const fnt)
{
    PNG = png;
    init(fnt);
}

Font::~Font()
{
    int i = 0;

    // destory all alocated textures
    while (i < pages)
    {
        wolf::TextureManager::DestroyTexture(tex[i]);
        i++;
    }

    free(tex);
}

int Font::getSize() const
{
    return size;
}

int Font::getLineHeight() const
{
    return lineHeight;
}
wolf::Texture **Font::getFontsheets() const
{
    return tex;
}

void Font::init(std::string file)
{
    std::ifstream readFile(file);
    // skip first 4 lines and extract important info
    for (size_t i = 0; i < 4; i++)
    {
        getline(readFile, file);
        std::string line = "lineHeight=";
        int index = file.find(line);
        if (index != std::string::npos) // if the specified string is found in the current line
        {
            line = file.substr(file.find(line) + line.length(), 3);
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // trim white spaces
            lineHeight = std::stoi(line);
        }

        line = "pages=";
        index = file.find(line);
        if (index != std::string::npos) // if the specified string is found in the current line
        {
            line = file.substr(file.find(line) + line.length(), 2);
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // trim white spaces
            pages = std::stoi(line);
        }

        line = "size=";
        index = file.find(line);
        if (index != std::string::npos) // if the specified string is found in the current line
        {
            line = file.substr(file.find(line) + line.length(), 3);
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end()); // trim white spaces
            size = std::stoi(line);
        }
    }

    tex = (wolf::Texture **)malloc(sizeof(wolf::Texture) * pages);
    for (int i = 0; i < pages; i++)
    {
        PNG[PNG.length() - 5] = '0' + i;
        tex[i] = wolf::TextureManager::CreateTexture(PNG);
    }

    while (getline(readFile, file))
    {
        std::string delimiter = "char id=";

        std::string temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end()); // trim white spaces
        char ID = char(std::stoi(temp));

        delimiter = "x=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int x = std::stoi(temp);

        delimiter = "y=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int y = std::stoi(temp);

        delimiter = "width=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int width = std::stoi(temp);

        delimiter = "height=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int height = std::stoi(temp);

        delimiter = "xoffset=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int xoffset = std::stoi(temp);

        delimiter = "yoffset=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int yoffset = std::stoi(temp);

        delimiter = "xadvance=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int xadvance = std::stoi(temp);

        delimiter = "page=";
        temp = file.substr(file.find(delimiter) + delimiter.length(), 5);
        temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
        int page = std::stoi(temp);

        s_font font = {tex[page], x, y, width, height, xoffset, yoffset, xadvance, page};

        characters.insert(std::pair<char, s_font>(ID, font));
    }
    readFile.close();
}

s_font Font::getChar(char const character) const
{
    return characters.find(character)->second;
}