#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"

#include "BoardKey.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;

enum EditorModes {DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE};

class EditorState :
	public State
{
private:
	unsigned mapPart;

	bool logged;
	bool inputting;
	bool showCursor;

	string password;
	PauseMenu* pmenu2;

	//Variables
	EditorStateData editorStateData;

	View view;
	float cameraSpeed;

	Font font;
	PauseMenu* pmenu;

	map<string, gui::Button*> buttons;

	TileMap* tileMap;

	vector<EditorMode*> modes;
	unsigned activeMode;

	//Sounds
	Music editor_theme;

	//Functions
	void initVariables();
	void initEditorStateData();
	void initView();
	void initFonts();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();
	void initModes();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	//Functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);

	void updatePauseMenuButtons();
	const bool getShowCursorTimer();

	void updateModes(const float& dt);
	void update(const float& dt);
	void renderButtons(RenderTarget& target);
	void renderGui(RenderTarget& target);
	void renderModes(RenderTarget& target);
	void render(RenderTarget* target = NULL);
};

#endif

