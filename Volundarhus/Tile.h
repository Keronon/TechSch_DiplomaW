#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING, MAPEND, ENEMYSPAWNER, DOODAD, OUTMAP};

class Tile
{
private:

protected:
	Sprite shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(short type, int grid_x, int grid_y, float gridSizeF, 
		const Texture& texture, const IntRect& texture_rect,
		const bool collision);
	virtual ~Tile();

	//Accessors
	const short& getType() const;
	virtual const bool & getCollision() const;

	//Functions
	virtual const Vector2f& getPosition() const;
	virtual const FloatRect getGlobalBounds() const;
	virtual const bool intersects(const FloatRect bounds) const;
	virtual const string getAsString() const = 0;

	virtual void update() = 0;
	virtual void render(RenderTarget& target, Shader* shader = NULL, const Vector2f player_position = Vector2f()) = 0;
};

#endif