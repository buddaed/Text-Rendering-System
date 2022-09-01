#include "textTable.h"
#include <iostream>
#include <fstream>

std::map<std::string, std::string> TextTable::english;
std::map<std::string, std::string> TextTable::french;

TextTable::TextTable()
{
    //default language
    language = "English";
}

TextTable::~TextTable()
{

}

void TextTable::Load(std::string file)
{
    std::ifstream readFile(file);
    int index;
    std::string sentence, type;

    getline(readFile, file); //skip first line
    
    while (getline(readFile, file))
    {
        type = file.substr(0, file.find("\t"));
        file.erase(0, file.find("\t")+1);
        sentence = file.substr(0, file.find("\t"));
        english.insert(std::pair<std::string, std::string>(type, sentence));

        file.erase(0, file.find("\t")+1);
        sentence = file.substr(0, file.find("\t"));
        french.insert(std::pair<std::string, std::string>(type, sentence)); 
    }

}

void TextTable::SetLanguage(std::string inLanguage)
{
    language = inLanguage;
}

std::string TextTable::GetString(std::string string) const
{
    if (language.compare("English") == 0)
    {
        return english.find(string)->second;
    }
    else
    {
        return french.find(string)->second;
    }  
}