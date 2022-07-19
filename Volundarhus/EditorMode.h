#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "Gui.h"

class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:
	EditorStateData() {};

	//Variables
	View* view;
	
	Font* font;

	float* keytime;
	float* keytimeMax;

	map<string, int>* keybinds;

	Vector2i* mousePosScreen;
	Vector2i* mousePosWindow;
	Vector2f* mousePosView;
	Vector2i* mousePosGrid;
};

class EditorMode
{
private:

protected:
	StateData* stateData;
	EditorStateData* editorStateData;
	TileMap* tileMap;

public:
	EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~EditorMode();

	//Functions
	const bool getKeytime(float keytime = 0.f);

	virtual void updateInput(const float& dt) = 0;
	virtual void updateGui(const float& dt) = 0;
	virtual void update(const float& dt) = 0;

	virtual void renderGui(RenderTarget& target) = 0;
	virtual void render(RenderTarget& target) = 0;
};

#endif //!EDITORMODE_H