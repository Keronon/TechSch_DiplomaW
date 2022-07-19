#include "stdafx.h"
#include "PlayerGUITabs.h"

PlayerGUITabs::PlayerGUITabs(VideoMode& vm, Font& font, Player& player)
	: vm(vm), font(font), player(player),
	characterTab(vm, font, player)
{

}

PlayerGUITabs::~PlayerGUITabs()
{

}

void PlayerGUITabs::update()
{

}

void PlayerGUITabs::render(RenderTarget * target)
{
	this->characterTab.render(target);
}
