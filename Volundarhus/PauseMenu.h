#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include"Gui.h"

class Gui;

class PauseMenu
{
private:
	Font& font;
	Text menuText;

	RectangleShape background;
	RectangleShape container;

	map<string, gui::Button*> buttons;

	//Private Functions

public:
	PauseMenu(VideoMode& vm, Font& font);
	virtual ~PauseMenu();

	//Accessor
	map<string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const string key);
	void addButton(const string key, 
		const float y, 
		const float width,
		const float height,
		const unsigned char_size, 
		const string text);
	void addButton(const string key, 
		const float y, 
		const float width,
		const float height,
		const unsigned char_size, 
		const string text,
		const Color text_idle_color, const Color text_hover_color, const Color text_active_color,
		const Color idle_color, const Color hover_color, const Color active_color);
	void update(const Vector2i& mousePosWindow);
	void render(RenderTarget& target);
};

#endif