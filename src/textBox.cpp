#include "textBox.h"
#include "font.h"

TextBox::TextBox(Font *const inFont, const std::string str, const float width, const float height)
{
    // Only init if not already done
    if (!program)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        sentence = str;
        font = inFont;
        textBoxWidth = width;
        textBoxHeight = height;

        _init();

        program = wolf::ProgramManager::CreateProgram("data/textBox.vsh", "data/textBox.fsh");
    }
}

TextBox::~TextBox()
{
    int i = 0;

    while (i < pagecount)
    {
        wolf::BufferManager::DestroyBuffer(vertBuf[i]);
        free(vertices[i]);
        delete dec[i];
        i++;
    }

    free(vertBuf);
    free(dec);
    free(vertices);
    // free(tex); gets freed in font.cpp

    delete[] pageCharCount;

    wolf::ProgramManager::DestroyProgram(program);
}

void TextBox::_init()
{
    pagecount = 0;

    _CountPages();

    // clear mem to avoid leak
    if (dirty)
    {
        int i = 0;

        while (i < pagecount)
        {
            wolf::BufferManager::DestroyBuffer(vertBuf[i]);
            free(vertices[i]);
            delete dec[i];
            i++;
        }

        free(vertBuf);
        free(dec);
        free(vertices);

        delete[] pageCharCount;
    }

    // allocate needed memory space
    pageCharCount = new int[pagecount];
    vertices = (Vertex **)malloc(sizeof(Vertex *) * pagecount);
    vertBuf = (wolf::VertexBuffer **)malloc(sizeof(wolf::VertexBuffer) * pagecount);
    dec = (wolf::VertexDeclaration **)malloc(sizeof(wolf::VertexDeclaration) * pagecount);
    tex = (wolf::Texture **)malloc(sizeof(wolf::Texture *) * pagecount);

    for (int i = 0; i < pagecount; i++)
    {
        pageCharCount[i] = 0;
    }

    for (int i = 0; i < sentence.length(); i++)
    {
        int j = font->getChar(sentence[i]).page % pagecount;
        pageCharCount[j]++;
    }

    for (int i = 0; i < pagecount; i++)
    {
        vertices[i] = (Vertex *)malloc(sizeof(Vertex) * 6 * pageCharCount[i]);
    }

    _ConstructQuads();

    for (int i = 0; i < pagecount; i++)
    {
        vertBuf[i] = wolf::BufferManager::CreateVertexBuffer(vertices[i], sizeof(Vertex) * 6 * pageCharCount[i]);
        dec[i] = new wolf::VertexDeclaration();
        dec[i]->Begin();
        dec[i]->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        dec[i]->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        dec[i]->SetVertexBuffer(vertBuf[i]);
        dec[i]->End();
        tex = font->getFontsheets();
    }
}

void TextBox::SetHorizontalAlignment(alignment inAlign)
{
    hAlignment = inAlign;
    dirty = true;
}

void TextBox::SetVerticalAlignment(alignment inAlign)
{
    vAlignment = inAlign;
    dirty = true;
}

void TextBox::_CountPages()
{
    std::string pages = "";

    for (int i = 0; i < sentence.length(); i++)
    {
        std::string temp = std::to_string(font->getChar(sentence[i]).page);
        if (pages.find(temp) == std::string::npos)
        {
            pagecount++;
            pages += temp;
        }
    }
}

void TextBox::setPosition(const glm::vec3 &inPos)
{
    pos = inPos;
}

void TextBox::SetColor(glm::vec4 inColor)
{
    color = inColor;
}

int TextBox::_CalcLineLength(std::string const sentence, int i) const
{
    float cursorX = 0;

    for (i; i < sentence.length(); i++)
    {
        if (cursorX + font->getChar(sentence[i]).xadvance > textBoxWidth)
        {
            return cursorX;
        }
        cursorX += font->getChar(sentence[i]).xadvance;
    }

    return cursorX;
}

int TextBox::_CalcNumOfLines(std::string const sentence) const
{
    int lines = 0;
    float cursorX = 0;

    for (int i = 0; i < sentence.length(); i++)
    {
        if (cursorX + font->getChar(sentence[i]).xadvance > textBoxWidth)
        {
            lines++;
            cursorX = 0;
        }
        cursorX += font->getChar(sentence[i]).xadvance;
    }

    return lines;
}

void TextBox::SetText(std::string line)
{
    if (sentence != line)
    {
        dirty = true;
        sentence = line;
    }
}

void TextBox::_ConstructQuads() const
{
    int lineLength;
    float cursorX;
    float cursorY;
    float lineHeight = font->getLineHeight();

    int *pindex = new int[pagecount];
    Vertex *vArray;

    // left horizontal alignment
    if (hAlignment == AL_left)
    {
        cursorX = 0;
    }
    // right horizontal alignment
    else if (hAlignment == AL_right)
    {
        lineLength = _CalcLineLength(sentence, 0);
        cursorX = textBoxWidth - lineLength;
    }
    // centered horizontal alignment
    else
    {
        lineLength = _CalcLineLength(sentence, 0);
        cursorX = textBoxWidth / 2 - lineLength / 2;
    }

    // top down vertical alignment
    if (vAlignment == AL_top)
    {
        cursorY = textBoxHeight - font->getSize();
    }
    // centered vertical alignment
    else if (vAlignment == AL_Vcenter)
    {
        cursorY = (textBoxHeight - (_CalcNumOfLines(sentence) - lineHeight)) / 2;
    }
    // bottom down vertical alignment
    else if (vAlignment == AL_bottom)
    {
        cursorY = _CalcNumOfLines(sentence) * lineHeight;
    }

    // init array
    for (int i = 0; i < pagecount; i++)
    {
        pindex[i] = 0;
    }

    // position quads vertices
    for (int i = 0; i < sentence.length(); i++)
    {
        float u = font->getChar(sentence[i]).x;
        float v = font->getChar(sentence[i]).y;
        float width = font->getChar(sentence[i]).width;
        float height = font->getChar(sentence[i]).height;
        float xoffset = font->getChar(sentence[i]).xoffset;
        float yoffset = 0;
        int page = font->getChar(sentence[i]).page % pagecount;

        // adjust height specifically for problematic letters
        if (sentence[i] == 'g' || sentence[i] == 'j' || sentence[i] == 'p' || sentence[i] == 'q' || sentence[i] == 'y')
        {
            yoffset = -font->getChar(sentence[i]).yoffset / 2;
        }

        if (cursorX + font->getChar(sentence[i]).xadvance > textBoxWidth)
        {
            switch (hAlignment)
            {
            case 1:
                lineLength = _CalcLineLength(sentence, i);
                cursorX = textBoxWidth - lineLength;
                cursorY -= lineHeight;
                break;

            case 2:
                lineLength = _CalcLineLength(sentence, i);
                cursorX = textBoxWidth / 2 - lineLength / 2;
                cursorY -= lineHeight;
                break;

            default:
                cursorX = 0;
                cursorY -= lineHeight;
            }
        }

        vArray = vertices[page];

        vArray[pindex[page]++] = {cursorX + xoffset, cursorY + yoffset, 0, u / 255, (v + height) / 255};                   // bottom left
        vArray[pindex[page]++] = {cursorX + xoffset, cursorY + height + yoffset, 0, u / 255, v / 255};                     // top left
        vArray[pindex[page]++] = {cursorX + width + xoffset, cursorY + height + yoffset, 0, (u + width) / 255, v / 255};   // top right
        vArray[pindex[page]++] = {cursorX + width + xoffset, cursorY + height + yoffset, 0, (u + width) / 255, v / 255};   // top right
        vArray[pindex[page]++] = {cursorX + width + xoffset, cursorY + yoffset, 0, (u + width) / 255, (v + height) / 255}; // bottom right
        vArray[pindex[page]++] = {cursorX + xoffset, cursorY + yoffset, 0, u / 255, (v + height) / 255};                   // bottom left

        cursorX += font->getChar(sentence[i]).xadvance;
    }

    delete[] pindex;
}

void TextBox::update()
{
    if (dirty)
    {
        _init();
        dirty = false;
    }
}

void TextBox::render(const glm::mat4 &viewMatrix, const glm::mat4 &projMatrix)
{
    glm::mat4 worldMatrix = glm::scale(glm::vec3(1, 1, 1));
    worldMatrix = glm::translate(pos) * worldMatrix;

    // Bind Uniforms
    program->SetUniform("projection", projMatrix);
    program->SetUniform("view", viewMatrix);
    program->SetUniform("world", worldMatrix);
    program->SetUniform("color", color);
    program->SetUniform("texture1", 0);

    //  Use shader program.
    program->Bind();

    for (int i = 0; i < pagecount; i++)
    {
        if (pagecount < 2)
        {
            int page = font->getChar(sentence[0]).page;
            tex[page]->Bind();
        }
        else
        {
            tex[i]->Bind();
        }

        dec[i]->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6 * pageCharCount[i]);
    }
}