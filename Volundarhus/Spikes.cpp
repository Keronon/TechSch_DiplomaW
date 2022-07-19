#include "stdafx.h"
#include "Spikes.h"

// Initializer functions
void Spikes::initVariables()
{
	this->type = 1;

	this->damageMin = 1;
	this->damageMax = 2;

	this->activated = false;
	this->animate = false;

	//Timer
	this->attackTimerMax = 200;
}

void Spikes::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", this->attackTimerMax/20.f, 0, 0, 2, 0, 32, 32);
}

//Constructors / Destructors
Spikes::Spikes(float x, float y, Texture& texture_sheet, unsigned damage_min, unsigned damage_max, EnemySpawnerTile& enemy_spawner_tile)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();

	this->damageMin = damage_min;
	this->damageMax = damage_max;

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 32.f, 32.f);
	this->createMovementComponent(0.f, 0.f, 0.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->setPosition(x, y);
	this->initAnimations();
}

Spikes::~Spikes()
{

}

//Accessors
const unsigned & Spikes::getDamageMin() const
{
	return this->damageMin;
}

const unsigned & Spikes::getDamageMax() const
{
	return this->damageMax;
}

const unsigned Spikes::getDamage() const
{
	return rand() % (this->damageMax - this->damageMin + 1) + (this->damageMin);
}

const bool Spikes::getActivated() const
{
	return this->activated;
}

const void Spikes::setActivated()
{
	this->activated = true;
	this->animate = true;
	this->attackTimer.restart();
}

const bool Spikes::isAttack()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();

		if (this->activated)
		{
			this->activated = false;
			return true;
		}
	}

	return false;
}

void Spikes::updateAnimation(const float & dt)
{
	if (this->animate)
	{
		this->animationComponent->play("IDLE", dt);
		if (this->animationComponent->isDone("IDLE"))
		{
			this->animate = false;
			this->activated = false;
		}
	}
	else
		this->attackTimer.restart();
}

void Spikes::update(const float & dt, Vector2f& mouse_pos_view)
{
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}

void Spikes::render(RenderTarget & target, Shader* shader, const Vector2f light_position, const bool show_hitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);
}