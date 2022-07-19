#include "stdafx.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
	this->cameraSpeed = 1000.f;
	this->mapPart = 0;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::initView()
{
	this->view.setSize(
		Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Broadway.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{
	ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initPauseMenu()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pmenu->addButton("MAPPART",gui::p2pY(28.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), to_string(this->mapPart));
	this->pmenu->addButton("LOAD", gui::p2pY(37.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Load");
	this->pmenu->addButton("SAVE", gui::p2pY(46.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Save");
	this->pmenu->addButton("CLEAR", gui::p2pY(55.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Clear");
	this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
	
	this->pmenu2 = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pmenu2->addButton(
		"PASSWORD",
		gui::p2pY(37.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		gui::calcCharSize(vm), "password",
		Color(200, 200, 200, 200), Color(200, 200, 200, 250), Color(200, 200, 200, 150),
		Color(70, 70, 70, 50), Color(80, 80, 80, 50), Color(60, 60, 60, 50));
	this->pmenu2->addButton("LOGIN", gui::p2pY(46.f, vm), gui::p2pX(18.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Login");
	this->pmenu2->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(18.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{
	
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 50, 50, "Resources/Images/Tiles/usedTilesheet.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
	this->initModes();

	this->paused = true;

	this->logged = false;
	this->inputting = false;
	this->showCursor = false;
	string password = "";

	if (!this->editor_theme.openFromFile("Resources/Sounds/Music/editor_theme.ogg"))
		cout << "ERROR::MENU THEME MUSIC CAN NOT OPEN\n"; // error
	this->editor_theme.setVolume(20.f);
	this->editor_theme.setLoop(true);
	this->editor_theme.play();
}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

//Functions
void EditorState::updateInput(const float & dt)
{
	if (this->logged)
		if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
		{
			if (!this->paused)
				this->pauseState();
			else
				this->unpauseState();
		}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Move view
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
		else
		{
			cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP!" << "\n";
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
		}
		else
		{
			cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN!" << "\n";
		}
	}
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}
}

void EditorState::updateGui(const float& dt)
{
	
}

void EditorState::updatePauseMenuButtons()
{
	if (logged)
	{
		stringstream str;
		str << "stage" << this->mapPart << ".mappart";

		map<string, gui::Button*> &buttons = this->pmenu->getButtons();

		if (Keyboard::isKeyPressed(Keyboard::Up) && this->getKeytime())
		{
			if (this->mapPart < 100)
				this->mapPart++;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && this->getKeytime())
		{
			if (this->mapPart > 0)
				this->mapPart--;
		}

		std::ifstream in_file;
		in_file.open(str.str());
		if (in_file.is_open())
		{
			buttons.at("MAPPART")->setText(to_string(this->mapPart));
		}
		else
		{
			buttons.at("MAPPART")->setText(to_string(this->mapPart) + "!");
		}
		in_file.close();

		if (this->pmenu->isButtonPressed("SAVE"))
			this->tileMap->saveToFile(str.str());

		if (this->pmenu->isButtonPressed("LOAD"))
			this->tileMap->loadFromFile(str.str());

		if (this->pmenu->isButtonPressed("CLEAR"))
			this->tileMap = new TileMap(this->stateData->gridSize, 50, 50, "Resources/Images/Tiles/usedTilesheet.png");

		if (this->pmenu->isButtonPressed("QUIT"))
		{
			this->editor_theme.stop();
			this->states->push(new MainMenuState(this->stateData));
			this->endState();
		}
	}
	else
	{
		map<string, gui::Button*> &buttons = this->pmenu2->getButtons();

		if (Mouse::isButtonPressed(Mouse::Left) && this->getKeytime())
		{
			this->inputting = false;
		}

		if (this->pmenu2->isButtonPressed("PASSWORD"))
		{
			this->inputting = true;
		}

		if (this->pmenu2->isButtonPressed("LOGIN"))
		{
			if (this->password == "password")
			{
				this->logged = true;
				this->paused = false;
			}
			else
			{
				this->editor_theme.stop();
				this->states->push(new MainMenuState(this->stateData));
				this->endState();
			}
		}

		if (this->pmenu2->isButtonPressed("QUIT"))
		{
			this->editor_theme.stop();
			this->states->push(new MainMenuState(this->stateData));
			this->endState();
		}

		if (this->inputting)
		{
			for (int i = 0; i <= 35; i++)
				if (this->password.size() < 8)
					if (Keyboard::isKeyPressed(Keyboard::Key(i)) && this->getKeytime())
					{
						BoardKey boardKey;
						if (Keyboard::isKeyPressed(Keyboard::Key::LShift))
						{
							this->password += boardKey.nameFromCode[i];
							cout << boardKey.nameFromCode[i] << endl;
						}
						else
						{
							string str = "";
							for (auto &chars : boardKey.nameFromCode[i])
								str += tolower(chars);
							this->password += str;
						}
					}
			if (Keyboard::isKeyPressed(Keyboard::Key::Backspace) && this->getKeytime())
				this->password = this->password.substr(0, this->password.size() - 1);

			string string = "";
			for (unsigned i = 0; i < this->password.length(); i++)
				string += "*";
			if (showCursor)
			{
				string += "|";
				showCursor = false;
			}
			else if (!showCursor)
				showCursor = true;
			buttons.at("PASSWORD")->setText(string);
		}
	}
}

void EditorState::updateModes(const float & dt)
{
	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);		
	}
	else //Paused
	{
		if (this->logged)
			this->pmenu->update(this->mousePosWindow);
		else
			this->pmenu2->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void EditorState::renderButtons(RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(RenderTarget& target)
{
	
}

void EditorState::renderModes(RenderTarget & target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, Vector2f(), true, true, true, true);
	this->tileMap->renderDeferred(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);

	this->renderGui(*target);

	this->renderModes(*target);

	if (this->paused) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		if (this->logged)
			this->pmenu->render(*target);
		else
			this->pmenu2->render(*target);
	}	
}