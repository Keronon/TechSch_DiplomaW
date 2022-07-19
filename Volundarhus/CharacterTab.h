#ifndef CHARACTERTAB_H
#define CHARACTERTAB_H

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	sf::RectangleShape background;
	Text infoText;

public:
	CharacterTab(VideoMode& vm, Font& font, Player& player);
	~CharacterTab();

	void update();
	void render(RenderTarget* target);
};

#endif