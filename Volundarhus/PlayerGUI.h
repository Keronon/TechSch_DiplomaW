#pragma once

#include "PlayerGUITabs.h"

class PlayerGUI
{
private:
	Text dashPowText;
	Texture dashPowTexture;
	Sprite dashPowSprite;

	Player* player;

	VideoMode& vm;
	Font font;

	//Level bar
	string levelBarString;
	Text levelBarText;
	sf::RectangleShape levelBarBack;

	//EXP Bar
	gui::ProgressBar* expBar;

	//HP Bar
	gui::ProgressBar* hpBar;

	//Player GUI Tabs
	PlayerGUITabs* playerTabs;

	void initFont();
	void initLevelBar();
	void initEXPBar();
	void initHPBar();
	void initPlayerTabs(VideoMode& vm, Font& flont, Player& player);

public:
	PlayerGUI(Player* player, VideoMode& vm);
	virtual ~PlayerGUI();

	//Functions
	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();

	void update(const float& dt);

	void renderLevelBar(RenderTarget & target);
	void renderEXPBar(RenderTarget & target);
	void renderHPBar(RenderTarget & target);
	void render(RenderTarget& target);
};

