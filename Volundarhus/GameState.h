#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TextTagSystem.h"

class GameState :
	public State
{
private:
	View view;
	Vector2i viewGridPosition;
	RenderTexture renderTexture;
	Sprite renderSprite;

	Font font;
	PauseMenu* pmenu;

	Shader core_shader;

	Player* player;
	PlayerGUI* playerGUI;
	Texture texture;
	
	vector<Enemy*> activeEnemies;
	EnemySystem *enemySystem;

	TileMap* tileMap;

	unsigned mapPart;
	PauseMenu* endmenu;
	bool ended;

	Clock tickTimer;
	Int32 tickTimerMax;

	//Systems
	TextTagSystem* tts;

	//Sounds
	Music main_theme;
	Music death;

	SoundBuffer endSB;
	Sound end;
	SoundBuffer stepsSB;
	Sound steps;
	SoundBuffer dashSB;
	Sound dash;
	SoundBuffer riseSpikesSB;
	Sound riseSpikes;
	SoundBuffer damageSpikesSB;
	Sound damageSpikes;

	//Functions
	void initDeferredRender();
	void initView();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initShaders();
	void initPlayers();
	void initPlayerGUI();
	void initEnemySystem();
	void initTileMap(String map_part);
	void initSystems();
	void initMusicAndSounds();

public:
	GameState(StateData* state_data, String map_part);
	virtual ~GameState();

	const bool isTick();
	//Functions
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void updatePlayer(const float& dt);
	void updateCombatAndEnemies(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif