#ifndef REGULARTILE_H
#define REGULARTILE_H

#include "Tile.h"

class RegularTile :
	public Tile
{
private:

protected:

public:
	RegularTile(short type, int grid_x, int grid_y, float gridSizeF,
		const Texture& texture, const IntRect& texture_rect,
		bool collision = false);

	virtual ~RegularTile();

	//Functions
	virtual const string getAsString() const;

	virtual void update();
	virtual void render(RenderTarget& target, Shader* shader = NULL, const Vector2f player_position = Vector2f());
};

#endif //!REGULARTILE_H
