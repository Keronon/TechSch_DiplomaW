#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"

class Tile;

class EnemySpawnerTile 
	: public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	Clock enemySpawnTimer;
	Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool spawned;

public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
		const Texture& texture, const IntRect& texture_rect,
		int enemy_type, int enemy_amount, Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();

	//Accessors
	virtual const string getAsString() const;
	const bool& getSpawned() const;
	const int& getEnemyType() const;
	const int& getEnemyAmount() const;
	const int& getEnemyCounter() const;

	//Modifiers
	void setSpawned(const bool spawned);

	//Functions
	const bool canSpawn() const;
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(RenderTarget & target, Shader* shader = NULL, const Vector2f player_position = Vector2f());
};

#endif //!ENEMYSPAWNERTTILE_H