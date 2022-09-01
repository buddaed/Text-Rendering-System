#pragma once
#include "../wolf/wolf.h"
#include "font.h"
#include "textTable.h"
#include "textBox.h"
#include "../samplefw/Sample.h"

class SampleTextRunner: public Sample
{
public:
    SampleTextRunner(wolf::App* app) : Sample(app,"Text") {}
    ~SampleTextRunner();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    Font* font1;
    Font* font2;
    Font* font3;
    TextBox* textBox1;
    TextBox* textBox2;
    TextBox* textBox3;
    TextTable* textTable;
};
