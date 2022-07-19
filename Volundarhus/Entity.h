#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

class Entity
{
private:
	void initVariables();

protected:

	Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(Texture& texture);
	void createHitboxComponent(Sprite& sprite, 
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	//Accessors
	virtual const AttributeComponent* getAttributeComponent() const;

	virtual const Vector2f& getPosition() const;
	virtual const Vector2f getCenter() const;
	virtual const Vector2i getGridPosition(const int gridSizeI) const;
	virtual const FloatRect getGlobalBounds(bool forTiles = false) const;
	virtual const FloatRect getNextPositionBounds(const float& dt) const;

	//Modifiers
	virtual void setPosition(const float x, const float y);
	
	//Functions
	virtual void move(const float x, const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	//Calculations
	virtual const float getDistance(const Entity& entity) const;

	virtual void update(const float& dt, Vector2f& mouse_pos_view) = 0;
	virtual void render(RenderTarget& target, Shader* shader, const Vector2f light_position, const bool show_hitbox) = 0;
};

#endif

