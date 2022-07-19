#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Rat.h"
#include "Spikes.h"

enum EnemyTypes {RAT = 0, SPIKES = 1};

class EnemySystem
{
private:
	map<string, Texture>& textures;
	vector<Enemy*>& activeEnemies;

public:
	EnemySystem(vector<Enemy*>& activeEnemies, 
		map<string, Texture>& textures);
	virtual ~EnemySystem();

	//Accessors

	//Modifiers

	//Functions
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile);
	void removeEnemy(const int index);

	void update(const float& dt);
	void render(RenderTarget* target);
};

#endif //!ENEMYSYSTEM_H