#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Broadway.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initGui()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(
		Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/mainMenuBackground.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Button background
	this->btnBackground.setSize(
		Vector2f(
			static_cast<float>(vm.width / 5), 
			static_cast<float>(vm.height)
		)
	);

	this->btnBackground.setPosition(vm.width - this->btnBackground.getSize().x - gui::p2pX(1.f, vm), 0.f);
	this->btnBackground.setFillColor(Color(10, 10, 10, 220));

	//Buttons
	this->testMapBTN = new gui::Button(
		this->btnBackground.getPosition().x + gui::p2pX(1.f, vm),
		this->btnBackground.getPosition().y + gui::p2pY(1.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Test part", gui::calcCharSize(vm),
		Color(150, 150, 150, 100), Color(255, 255, 255, 155), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);

	this->buttons["NEW_GAME_STATE"] = new gui::Button(
		this->btnBackground.getPosition().x + gui::p2pX(1.f, vm),
		this->btnBackground.getPosition().y + gui::p2pY(30.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 10), Color(150, 150, 150, 10), Color(20, 20, 20, 10)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		this->btnBackground.getPosition().x + gui::p2pX(1.f, vm),
		this->btnBackground.getPosition().y + gui::p2pY(40.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Settings", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 10), Color(150, 150, 150, 10), Color(20, 20, 20, 10));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		this->btnBackground.getPosition().x + gui::p2pX(1.f, vm),
		this->btnBackground.getPosition().y + gui::p2pY(50.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 10), Color(150, 150, 150, 10), Color(20, 20, 20, 10));

	this->buttons["EXIT_STATE"] = new gui::Button(
		this->btnBackground.getPosition().x + gui::p2pX(1.f, vm),
		this->btnBackground.getPosition().y + gui::p2pY(80.f, vm),
		gui::p2pX(18.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(100, 100, 100, 10), Color(150, 150, 150, 10), Color(20, 20, 20, 10));
}

void MainMenuState::resetGui()
{
	/*	Clears the GUI elements and re-initialises the GUI.
	 
		@return void	*/
	
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->resetGui();

	if (!this->menu_theme.openFromFile("Resources/Sounds/Music/menu_theme.ogg"))
		cout << "ERROR::MENU THEME MUSIC CAN NOT OPEN\n"; // error
	this->menu_theme.setVolume(30.f);
	this->menu_theme.setLoop(true);
	this->menu_theme.play();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float & dt)
{
	
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//extra BTNs
	this->testMapBTN->update(this->mousePosWindow);

	if (this->testMapBTN->isPressed())
	{
		this->menu_theme.stop();
		this->states->push(new GameState(this->stateData, "stage0.mappart"));
		this->endState();
	}

	//New game
	if (this->buttons["NEW_GAME_STATE"]->isPressed())
	{
		this->menu_theme.stop();
		this->states->push(new GameState(this->stateData, "stage1.mappart"));
		this->endState();
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->menu_theme.stop();
		this->states->push(new SettingsState(this->stateData));
		this->endState();
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->menu_theme.stop();
		this->states->push(new EditorState(this->stateData));
		this->endState();
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
	this->testMapBTN->render(target);
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->btnBackground);

	this->renderButtons(*target);

	//REMOVE LATER!!!
	//Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}
