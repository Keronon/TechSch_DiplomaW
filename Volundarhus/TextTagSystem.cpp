#include "stdafx.h"
#include "TextTagSystem.h"

//Private functions
void TextTagSystem::initVariables()
{

}

void TextTagSystem::initFonts(string font_file)
{
	if (!this->font.loadFromFile(font_file))
		cout << "ERROR::TEXTTAGSYSTEM::CONSTRUCTOR::Failed to load font " << font_file << "\n";
}

void TextTagSystem::initTagTemplates()
{
	this->tagTemplates[DEFAULT_TAG] =
		new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, Color::White, 40, 100.f, 200.f);
	this->tagTemplates[NEGATIVE_TAG] =
		new TextTag(this->font, "", 100.f, 100.f, 0.f, 1.f, Color::Red, 40, 100.f, 250.f);
	this->tagTemplates[EXPERIENCE_TAG] =
		new TextTag(this->font, "", 100.f, 100.f, 0.f, -1.f, Color::Cyan, 55, 150.f, 250.f);
}

//Constructor / Destructor
TextTagSystem::TextTagSystem(string font_file)
{
	this->initFonts(font_file);
	this->initVariables();
	this->initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
	//Clean up tags
	for (auto *tag : this->tags)
	{
		delete tag;
	}

	//Clean up templates
	for (auto &tag : this->tagTemplates)
	{
		delete tag.second;
	}
}

//Functions
void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const string str, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss << prefix << " " << str << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const int i, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss << prefix << " " << i << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::addTextTag(const unsigned tag_type, const float pos_x, const float pos_y, const float f, const string prefix = "", const string postfix = "")
{
	stringstream ss;
	ss << prefix << " " << f << " " << postfix;
	this->tags.push_back(new TextTag(this->tagTemplates[tag_type], pos_x, pos_y, ss.str()));
}

void TextTagSystem::update(const float & dt)
{
	for (size_t i = 0; i < this->tags.size(); i++)
	{
		this->tags[i]->update(dt);

		if (this->tags[i]->isExpired())
		{
			delete this->tags[i];
			this->tags.erase(this->tags.begin() + i);
		}
	}
}

void TextTagSystem::render(RenderTarget & target)
{
	for (auto&tag : this->tags)
	{
		tag->render(target);
	}
}
