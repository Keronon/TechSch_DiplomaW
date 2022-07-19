#ifndef PLAYERGUITABS_H
#define PLAYERGUITABS_H

#include "CharacterTab.h"

class PlayerGUITabs
{
private:
	CharacterTab characterTab;

	VideoMode& vm;
	Font& font;
	Player& player;
	
public:
	PlayerGUITabs(VideoMode& vm, Font& font, Player& player);
	virtual ~PlayerGUITabs();

	void update();
	void render(RenderTarget* target);
};

#endif