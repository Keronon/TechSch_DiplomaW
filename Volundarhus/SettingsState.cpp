#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
	this->modes = VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Broadway.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
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

void SettingsState::initGui()
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

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/settingsBackground.jpg"))
	{
		throw "ERROR::SETTINGS_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Buttons
	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(5.f, vm), gui::p2pY(72.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(5.f, vm), gui::p2pY(81.5f, vm),
		gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	//Modes
	vector<string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(to_string(i.width) + 'x' + to_string(i.height));
	}

	//Resolution Drop down lists
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm),
		font, modes_str.data(), modes_str.size()
	);

	//Fullscreen buttons
	this->buttons["ON"] = new gui::Button(
		gui::p2pX(41.5f, vm), gui::p2pY(49.f, vm),
		gui::p2pX(5.f, vm), gui::p2pY(4.5f, vm),
		&this->font, "On", gui::calcCharSize(vm),
		Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["OFF"] = new gui::Button(
		gui::p2pX(47.f, vm), gui::p2pY(49.f, vm),
		gui::p2pX(5.f, vm), gui::p2pY(4.5f, vm),
		&this->font, "Off", gui::calcCharSize(vm),
		Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	//Text init
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
	this->optionsText.setFillColor(Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \n\nFullscreen \n\n "
	);
}

void SettingsState::resetGui()
{
	/*	Clears the GUI elements and re-initialises the GUI.
	 
		@return void	*/

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();

	if (!this->settings_theme.openFromFile("Resources/Sounds/Music/settings_theme.ogg"))
		cout << "ERROR::MENU THEME MUSIC CAN NOT OPEN\n"; // error
	this->settings_theme.setVolume(20.f);
	this->settings_theme.setLoop(true);
	this->settings_theme.play();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it; it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	
	auto it2 = this->dropDownLists.begin();
	for (it2; it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
	/*Updates all the gui elements in the state and handle their functionlaity.*/
	//Buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Button functionality
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->settings_theme.stop();
		this->states->push(new MainMenuState(this->stateData));
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		unsigned short style;
		if (this->stateData->gfxSettings->fullscreen) style = Style::Fullscreen;
		else style = Style::Default;

		//TEST REMOVE LATER
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, style);

		this->resetGui();
	}

	//Fullscreen sets
	if (this->buttons["ON"]->isPressed())
	{
		this->stateData->gfxSettings->fullscreen = true;
		this->buttons["ON"]->setText("ON");
		this->buttons["OFF"]->setText("");
	}
	if (this->buttons["OFF"]->isPressed())
	{
		this->stateData->gfxSettings->fullscreen = false;
		this->buttons["ON"]->setText("");
		this->buttons["OFF"]->setText("OFF");
	}

	//Dropdown lists
	for (auto &it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}

	//Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingsState::renderGui(RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	//REMOVE LATER!!!
	Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}