#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "../wolf/wolf.h"
#include "../samplefw/SampleRunner.h"
#include "sampleTextRunner.h"

class Week2: public wolf::App
{
public:
    Week2() : App("TextRenderingSystem demo")
    {
        m_sampleRunner.addSample(new SampleTextRunner(this));
    }

    ~Week2()
    {
    }

    void update(float dt) override
    {
        m_sampleRunner.update(dt);
    }

    void render() override
    {
        m_sampleRunner.render(m_width, m_height);
    }

private:
    SampleRunner m_sampleRunner;
    bool m_lastDown = false;
};

int main(int, char**) {
    Week2 week2;
    week2.run();
}