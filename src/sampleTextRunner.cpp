#include "sampleTextRunner.h"

SampleTextRunner::~SampleTextRunner()
{
	printf("Destroying Text Sample\n");
	delete textTable;
	delete font1;
	delete font2;
	delete font3;
	delete textBox1;
	delete textBox2;
	delete textBox3;
}

void SampleTextRunner::init()
{
	textTable = new TextTable();
	textTable->Load("data/text.dat");
	textTable->SetLanguage("English");
	std::string str = textTable->GetString("str_course_name");

	font1 = new Font("data/Aerialsize50_0.png", "data/Aerialsize50.fnt");
	textBox1 = new TextBox(font1, str, 400.0f, 200.0f);
	textBox1->SetColor(glm::vec4(1, 0, 0, 1));
	textBox1->SetHorizontalAlignment(AL_center);
	textBox1->SetText("horizontal  centered text");

	font2 = new Font("data/AerialSize32_0.png", "data/AerialSize32.fnt");
	textBox2 = new TextBox(font2, str, 400.0f, 200.0f);
	textBox2->setPosition(glm::vec3(0, -200, 0));
	textBox2->SetVerticalAlignment(AL_bottom);
	textBox2->SetColor(glm::vec4(0, 1, 0, 1));
	textBox2->SetText("bottom to top vertical alignment");

	font3 = new Font("data/AerialSize24_0.png", "data/AerialSize24.fnt");
	textBox3 = new TextBox(font3, str, 400.0f, 200.0f);
	textBox3->SetHorizontalAlignment(AL_right);
	textBox3->setPosition(glm::vec3(0, -400, 0));
	textBox3->SetColor(glm::vec4(1, 0, 1, 1));
	textBox3->SetText("right aligned text");
}

void SampleTextRunner::update(float dt)
{
	textBox1->update();
	textBox2->update();
	textBox3->update();
}

void SampleTextRunner::render(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(1, 0, 1), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
	const glm::mat4 projMatrix = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, 0.1f, 1000.0f);

	textBox1->render(viewMatrix, projMatrix);
	textBox2->render(viewMatrix, projMatrix);
	textBox3->render(viewMatrix, projMatrix);
}
