#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Entity;

class Player :
	public Entity
{
private:
	//Variables
	Inventory* inventory;

	unsigned dashPow;

	//Initializer functions
	void initVariables();
	void initComponents();
	void initAnimations();
	void initInventory();

public:
	Player(float x, float y, Texture& texture_sheet);
	virtual ~Player();
	
	//Accessors
	AttributeComponent* getAttributeComponent();
	MovementComponent* getMovementComponent();

	unsigned getDashPow();

	//Functions
	void loseDPw(const int dpw);
	void gainDPw(const int dpw);

	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);

	void updateAnimation(const float& dt);
	void update(const float& dt, Vector2f& mouse_pos_view);

	void render(RenderTarget& target, Shader* shader = NULL, const Vector2f light_position = Vector2f(), const bool show_hitbox = false);
};

#endif