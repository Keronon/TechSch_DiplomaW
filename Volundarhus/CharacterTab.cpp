#include "stdafx.h"
#include "CharacterTab.h"

CharacterTab::CharacterTab(VideoMode& vm, Font& font, Player& player)
	: Tab(vm, font, player)
{
	//Background
	this->background.setFillColor(Color(50, 50, 50, 180));
	this->background.setSize(Vector2f(
		gui::p2pX(30.f, this->vm), static_cast<float>(this->vm.height)
	));

	//Text
	this->infoText.setFont(this->font);
	this->infoText.setCharacterSize(gui::calcCharSize(this->vm, 50));
	this->infoText.setFillColor(Color::White);
	this->infoText.setPosition(
		this->background.getPosition().x + 20.f,
		this->background.getPosition().y + 20.f
	);
}

CharacterTab::~CharacterTab()
{

}

void CharacterTab::update()
{

}

void CharacterTab::render(RenderTarget * target)
{
	target->draw(background);
	target->draw(infoText);
}
