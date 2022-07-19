#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(VideoMode& vm, Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(
		Vector2f(
			static_cast<float>(vm.width), 
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2pY(9.3f, vm)
		)
	);
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(vm.width) - this->container.getSize().x - gui::p2pX(3.f, vm),
		30.f
	);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm));
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2pY(4.f, vm)
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool PauseMenu::isButtonPressed(const string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
	const string key, 
	const float y,
	const float width,
	const float height,
	const unsigned char_size, 
	const string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_size,
		Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
}

void PauseMenu::addButton(
	const string key,
	const float y,
	const float width,
	const float height,
	const unsigned char_size,
	const string text,
	const Color text_idle_color, const Color text_hover_color, const Color text_active_color,
	const Color idle_color, const Color hover_color, const Color active_color)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_size,
		text_idle_color, text_hover_color, text_active_color,
		idle_color, hover_color, active_color
	);
}

void PauseMenu::update(const Vector2i& mousePosWindow)
{
	for (auto &i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(RenderTarget & target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto &i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}