#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(1.6f, this->vm);
	float height = gui::p2pY(2.8f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.9f, this->vm);

	this->levelBarBack.setSize(Vector2f(width, height));
	this->levelBarBack.setFillColor(Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 150));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm), 
		this->levelBarBack.getPosition().y + gui::p2pY(0.5f, this->vm)
	);
}

void PlayerGUI::initEXPBar()
{
	this->expBar = new gui::ProgressBar(
		1.f, 5.6f, 10.4f, 1.9f,
		this->player->getAttributeComponent()->expNext,
		Color::Blue, Color(0, 0, 150, 255), 220,
		this->vm, &this->font);
}

void PlayerGUI::initHPBar()
{
	this->hpBar = new gui::ProgressBar(
		1.f, 3.f, 15.f, 4.5f, 
		this->player->getAttributeComponent()->hpMax,
		Color::Red, Color(150, 0, 0, 255), 90,
		this->vm, &this->font);

	this->dashPowTexture.loadFromFile("Resources/Images/Gui/dashPow.png");
	this->dashPowSprite.setTexture(dashPowTexture);
	this->dashPowSprite.setScale(1.6f, 1.6f);
	this->dashPowSprite.setPosition(gui::p2pX(1.1f, this->vm), gui::p2pY(10.0f, this->vm));

	this->dashPowText.setFont(this->font);
	this->dashPowText.setCharacterSize(32);
	this->dashPowText.Bold;
	this->dashPowText.setFillColor(Color::White);
	this->dashPowText.setPosition(
		this->dashPowSprite.getPosition().x + 40.f,
		this->dashPowSprite.getPosition().y - 5.f
	);
	this->dashPowText.setString(this->player->getDashPow());
}

void PlayerGUI::initPlayerTabs(VideoMode& vm, Font& flont, Player& player)
{
	this->playerTabs = new PlayerGUITabs(vm, font, player);
}

PlayerGUI::PlayerGUI(Player* player, VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
	this->initPlayerTabs(vm, font, *player);
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
	delete this->playerTabs;
}

//Functions
void PlayerGUI::updateLevelBar()
{
	this->levelBarString = to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
}

void PlayerGUI::updateHPBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);
	this->dashPowText.setString(to_string(this->player->getDashPow()));
}

void PlayerGUI::update(const float & dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderLevelBar(RenderTarget & target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(RenderTarget & target)
{
	this->expBar->render(target);
}

void PlayerGUI::renderHPBar(RenderTarget & target)
{
	this->hpBar->render(target);
	target.draw(this->dashPowSprite);
	target.draw(this->dashPowText);
}


void PlayerGUI::render(RenderTarget & target)
{
	this->renderHPBar(target);
}
