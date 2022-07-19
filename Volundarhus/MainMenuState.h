#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState :
	public State
{
private:
	//Variables
	Texture backgroundTexture;
	sf::RectangleShape background;
	Font font;

	sf::RectangleShape btnBackground;
	map<string, gui::Button*> buttons;

	gui::Button* testMapBTN;

	//Sounds
	Music menu_theme;

	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initGui();
	void resetGui();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void render(RenderTarget* target = NULL);
};

#endif
