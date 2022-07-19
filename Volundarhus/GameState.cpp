#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		IntRect(
			0, 
			0,
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);
}

//Initializer functions
void GameState::initView()
{
	this->view.setSize(
		Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
			static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Broadway.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/usedPlayersheet.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}

	if(!this->textures["RAT1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/rat1_60x64.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE";
	}

	if (!this->textures["SPIKES1_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/Traps/Spikes1_32x32.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_SPIKES1_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pmenu->addButton("RESTART", gui::p2pY(34.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Restart");
	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");

	this->endmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->endmenu->addButton("NEXT", gui::p2pY(34.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Next");
	this->endmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initShaders()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		cout << "ERROR::GAMESTATE::COULD NOT LOAD SHADER." << "\n";
	}
}

void GameState::initPlayers()
{
	if (this->mapPart == 0)
		this->player = new Player(500, 300, this->textures["PLAYER_SHEET"]);
	else
		this->player = new Player(990, 990, this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap(String map_part)
{
	this->tileMap = new TileMap(map_part);
}

void GameState::initSystems()
{
	this->tts = new TextTagSystem("Fonts/PixellettersFull.ttf");
}

void GameState::initMusicAndSounds()
{
	if (!this->main_theme.openFromFile("Resources/Sounds/Music/main_theme.ogg"))
		cout << "ERROR::MAIN THEME MUSIC CAN NOT OPEN\n"; // error
	this->main_theme.setVolume(20.f);
	this->main_theme.setLoop(true);
	this->main_theme.play();

	if (!this->death.openFromFile("Resources/Sounds/Music/death.ogg"))
		cout << "ERROR::DEATH MUSIC CAN NOT OPEN\n"; // error
	this->death.setVolume(100.f);
	this->death.setLoop(false);

	if (!endSB.loadFromFile("Resources/Sounds/Effects/end.wav"))
		cout << "ERROR::STEPS SOUND CAN NOT OPEN\n"; // error
	this->end.setVolume(100.f);
	this->end.setBuffer(endSB);

	if (!stepsSB.loadFromFile("Resources/Sounds/Effects/steps.wav"))
		cout << "ERROR::STEPS SOUND CAN NOT OPEN\n"; // error
	this->steps.setVolume(50.f);
	this->steps.setBuffer(stepsSB);

	if (!dashSB.loadFromFile("Resources/Sounds/Effects/dash.wav"))
		cout << "ERROR::STEPS SOUND CAN NOT OPEN\n"; // error
	this->dash.setVolume(50.f);
	this->dash.setBuffer(dashSB);

	if (!riseSpikesSB.loadFromFile("Resources/Sounds/Effects/rise_spikes.wav"))
		cout << "ERROR::RISE SPIKES SOUND CAN NOT OPEN\n"; // error
	this->riseSpikes.setVolume(50.f);
	this->riseSpikes.setBuffer(riseSpikesSB);

	if (!damageSpikesSB.loadFromFile("Resources/Sounds/Effects/damage_spikes.wav"))
		cout << "ERROR::DAMAGE SPIKES SOUND CAN NOT OPEN\n"; // error
	this->damageSpikes.setVolume(50.f);
	this->damageSpikes.setBuffer(damageSpikesSB);
}

//Constructors / Destructors
GameState::GameState(StateData* state_data, String map_part)
	: State(state_data)
{
	this->mapPart = stoi((string)map_part.substring(5, map_part.find('.') - 5));
	this->ended = false;

	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initShaders();

	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap(map_part);
	this->initSystems();
	this->initMusicAndSounds();

	this->tickTimer.restart();
	this->tickTimerMax = 250;
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	delete this->tts;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

const bool GameState::isTick()
{
	if (this->tickTimer.getElapsedTime().asMilliseconds() >= this->tickTimerMax)
	{
		this->tickTimer.restart();

		return true;
	}

	return false;
}

//Functions
void GameState::updateView(const float & dt)
{
	this->view.setCenter(
		floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
	);
	
	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float & dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float & dt)
{
	//Update player input
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0.f, dt);
		if (steps.getStatus() != SoundSource::Status::Playing)
			steps.play();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0.f, dt);
		if (steps.getStatus() != SoundSource::Status::Playing)
			steps.play();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
		if (steps.getStatus() != SoundSource::Status::Playing)
			steps.play();
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
		if (steps.getStatus() != SoundSource::Status::Playing)
			steps.play();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("DASH"))) && this->getKeytime() && this->player->getDashPow() > 0)
	{
		if (this->player->getMovementComponent()->getVelocity().x > 0.f)
			this->player->setPosition(this->player->getPosition().x + 40.f, this->player->getPosition().y);
		if (this->player->getMovementComponent()->getVelocity().x < 0.f)
			this->player->setPosition(this->player->getPosition().x - 40.f, this->player->getPosition().y);
		if (this->player->getMovementComponent()->getVelocity().y > 0.f)
			this->player->setPosition(this->player->getPosition().x, this->player->getPosition().y + 40.f);
		if (this->player->getMovementComponent()->getVelocity().y < 0.f)
			this->player->setPosition(this->player->getPosition().x, this->player->getPosition().y - 40.f);

		if (dash.getStatus() != SoundSource::Status::Playing)
			dash.play();
		this->player->loseDPw(1);
	}
}

void GameState::updatePlayerGUI(const float & dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("RESTART"))
	{
		this->main_theme.stop();
		stringstream str;
		str << "stage" << this->mapPart << ".mappart";
		this->states->push(new GameState(this->stateData, str.str()));
		this->endState();
	}
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->main_theme.stop();
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}

	if (this->endmenu->isButtonPressed("NEXT"))
	{
		this->main_theme.stop();
		stringstream str;
		str << "stage" << this->mapPart + 1 << ".mappart";
		this->states->push(new GameState(this->stateData, str.str()));
		this->endState();
	}
	if (this->endmenu->isButtonPressed("QUIT"))
	{
		this->main_theme.stop();
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}
}

void GameState::updateTileMap(const float & dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt); 
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayer(const float & dt)
{
	// ---------------- CROSSGAME PORTS
	if (this->tileMap->checkType(this->player->getGridPosition(static_cast<int>(this->gridSize)).x, this->player->getGridPosition(static_cast<int>(this->gridSize)).y, 1, MAPEND))
	{
		this->ended = true;
		if (end.getStatus() != SoundSource::Status::Playing)
			end.play();
		this->pauseState();
	}

	// ---------------- SPIKES DAMAGING
	for (auto *enemy : this->activeEnemies)
	{
		if (enemy->getType() == SPIKES && enemy->getGlobalBounds().intersects(this->player->getGlobalBounds(true)))
		{
			if (!static_cast<Spikes*>(enemy)->getActivated() && isTick())
				static_cast<Spikes*>(enemy)->setActivated();

			if (static_cast<Spikes*>(enemy)->isAttack() && enemy->getGlobalBounds().intersects(this->player->getGlobalBounds(true)))
			{
				if (damageSpikes.getStatus() != SoundSource::Status::Playing)
					damageSpikes.play();
				this->player->loseHP(static_cast<Spikes*>(enemy)->getDamageMax());
			}
			else
				if (riseSpikes.getStatus() != SoundSource::Status::Playing && damageSpikes.getStatus() != SoundSource::Status::Playing)
					riseSpikes.play();
		}
	}

	// ---------------- OUT MAP
	if (this->tileMap->checkType(this->player->getGridPosition(static_cast<int>(this->gridSize)).x, this->player->getGridPosition(static_cast<int>(this->gridSize)).y, 1, OUTMAP))
	{
		this->player->stopVelocity();
		this->death.play();
		this->pauseState();
	}

	if (this->player->getAttributeComponent()->hp == 0)
	{
		this->death.play();
		this->pauseState();
		//this->player->getAttributeComponent()->hp = this->player->getAttributeComponent()->hpMax;
	}
}

void GameState::updateCombatAndEnemies(const float & dt)
{
	unsigned index = 0;
	for (auto *enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePosView);

		this->tileMap->updateWorldBoundsCollision(enemy, dt);
		this->tileMap->updateTileCollision(enemy, dt);
	
		//DANGEROUS!!!
		if (enemy->isDead())
		{
			this->player->gainEXP(enemy->getGainExp());
			this->tts->addTextTag(EXPERIENCE_TAG, this->player->getCenter().x, this->player->getCenter().y, static_cast<int>(enemy->getGainExp()), "", "+EXP");

			this->enemySystem->removeEnemy(index);
			--index;
		}

		++index;
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);	
	
	if (!this->paused) //Unpaused update
	{
		this->main_theme.setVolume(20.f);

		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, this->mousePosView);

		this->playerGUI->update(dt);

		//Update all enemies
		//CHANGE: Loop outside, and make functions take one enemy at a time
		this->updateCombatAndEnemies(dt);

		//Update systems
		this->tts->update(dt);

		this->updatePlayer(dt); //---------------------------------------
	}
	else //Paused update
	{
		this->main_theme.setVolume(10.f);

		stringstream str;
		str << "stage" << this->mapPart + 1 << ".mappart";

		std::ifstream in_file;
		in_file.open(str.str());

		if (this->ended && in_file.is_open())
			this->endmenu->update(this->mousePosWindow);
		else
			this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();

		in_file.close();
	}
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture, 
		this->viewGridPosition, 
		&this->core_shader,
		this->player->getCenter(),
		false
	);

	for (auto *enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
	}

	this->player->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);

	this->tileMap->renderDeferred(this->renderTexture, &this->core_shader, this->player->getCenter());

	this->tts->render(this->renderTexture);

	//Render GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) //Pause menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		if (this->ended && this->mapPart != 2)
			this->endmenu->render(this->renderTexture);
		else
			this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
