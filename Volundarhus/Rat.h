#ifndef RAT_H
#define RAT_H

#include "Enemy.h"

class Rat :
	public Enemy
{
private:
	void initVariables();
	void initAnimations();
	void initGUI();

	sf::RectangleShape hpBar;

public:
	Rat(float x, float y, Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile);
	virtual ~Rat();

	//Functions
	void updateAnimation(const float& dt);
	void update(const float& dt, Vector2f& mouse_pos_view);

	void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox);
};

#endif //!RAT_H