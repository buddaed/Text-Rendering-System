#pragma once
#include "font.h"

enum alignment
{
    AL_left = 0,
    AL_right,
    AL_center,
    AL_top,
    AL_Vcenter,
    AL_bottom,
};

struct Vertex
{
    float x, y, z, u, v;
};

class TextBox
{
public:
    TextBox(Font *const, std::string const, float const, float const);
    ~TextBox();

    void update();
    void render(const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix);

    void setPosition(const glm::vec3 &pos);
    void SetHorizontalAlignment(alignment);
    void SetVerticalAlignment(alignment);
    void SetText(std::string);
    void SetColor(glm::vec4);

    void _ConstructQuads() const;
    void _init();
    void _CountPages();
    int _CalcLineLength(std::string const, int) const;
    int _CalcNumOfLines(std::string const) const;

private:
    Font *font;
    std::string sentence;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 color = glm::vec4(1, 1, 1, 1);
    Vertex **vertices;
    alignment hAlignment = AL_left;
    alignment vAlignment = AL_Vcenter;

    wolf::VertexBuffer **vertBuf = 0;
    wolf::VertexDeclaration **dec;
    wolf::Program *program = 0;
    wolf::Texture **tex;

    int pagecount;
    int *pageCharCount;
    bool dirty = false;
    float textBoxWidth, textBoxHeight;
};