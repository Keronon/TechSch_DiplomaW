#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(vector<Enemy*>& activeEnemies,
	map<string, Texture>& textures)
	: textures(textures), activeEnemies(activeEnemies)
{

}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner_tile));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::SPIKES:
		this->activeEnemies.push_back(new Spikes(xPos, yPos, this->textures["SPIKES1_SHEET"], 0, 1, enemy_spawner_tile));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	default:
		cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float & dt)
{

}

void EnemySystem::render(RenderTarget * target)
{

}
