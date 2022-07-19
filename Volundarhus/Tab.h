#ifndef TAB_H
#define TAB_H

#include "Player.h"
#include "Gui.h"

class Tab
{
protected:
	VideoMode& vm;
	Font& font;
	Player& player;

public:
	Tab(VideoMode& vm, Font& font, Player& player);
	virtual ~Tab();

	virtual void update() = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif