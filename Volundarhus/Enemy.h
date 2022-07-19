#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
	public Entity
{
private:
	//Variables
	EnemySpawnerTile& enemySpawnerTile;
	unsigned gainExp;

	//Initializer functions
	virtual void initVariables() = 0;
	virtual void initAnimations() = 0;

protected:
	short type;

public:
	Enemy(EnemySpawnerTile& enemy_spawner_tile);
	virtual ~Enemy();

	//Accessors
	const short& getType() const;

	const unsigned& getGainExp() const;
	EnemySpawnerTile& getEnemySpawnerTile();

	//Functions
	virtual void generateAttributes(const unsigned level);

	virtual void loseHP(const int hp);
	virtual const bool isDead() const;

	virtual const AttributeComponent* getAttributeComp() const;

	virtual void updateAnimation(const float & dt) = 0;

	virtual void update(const float & dt, Vector2f& mouse_pos_view) = 0;
	virtual void render(RenderTarget & target, Shader* shader = NULL, const Vector2f light_position = Vector2f(), const bool show_hitbox = false) = 0;
};

#endif //!ENEMY_H
