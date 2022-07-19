#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "Gui.h"

class SettingsState :
	public State
{
private:
	//Variables
	Texture backgroundTexture;
	sf::RectangleShape background;
	Font font;

	map<string, gui::Button*> buttons;
	map<string, gui::DropDownList*> dropDownLists;

	Text optionsText;

	vector<VideoMode> modes;

	//Sounds
	Music settings_theme;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	//Accessors

	//Functions
	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void update(const float& dt);
	void renderGui(RenderTarget& target);
	void render(RenderTarget* target = NULL);
};

#endif