#ifndef SPIKES_H
#define SPIKES_H

#include "Enemy.h"
#include "Player.h"

class Spikes :
	public Enemy
{
private:
	void initVariables();
	void initAnimations();
	
	unsigned damageMin;
	unsigned damageMax;

	bool activated;
	bool animate;

	Clock attackTimer;
	Int32 attackTimerMax;

public:
	Spikes(float x, float y, Texture& texture_sheet, unsigned damage_min, unsigned damage_max, EnemySpawnerTile& enemy_spawner_tile);
	virtual ~Spikes();

	//Accessors
	const unsigned& getDamageMin() const;
	const unsigned& getDamageMax() const;
	const unsigned getDamage() const;

	const bool getActivated() const;
	const void setActivated();

	//Functions
	const bool isAttack();

	void updateAnimation(const float& dt);
	void update(const float& dt, Vector2f& mouse_pos_view);

	void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox);
};

#endif