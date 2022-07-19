#ifndef TILEMAP_H
#define TILEMAP_H

#include "EnemySpawnerTile.h"
#include "RegularTile.h"
#include "EnemySystem.h"

class TileMap
{
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	Vector2i maxSizeWorldGrid;
	Vector2f maxSizeWorldF;
	int layers;
	vector<vector<vector<vector<Tile*>>>> map;
	stack<Tile*> deferredRenderStack;
	string textureFile;
	Texture tileSheet;
	RectangleShape collisionBox;
	RectangleShape entityBox;
	RectangleShape outmapBox;
	RectangleShape createBorder;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	void resizeMap();

public:
	TileMap(float gridSize, int width, int height, string texture_file);
	TileMap(const string file_name);
	virtual ~TileMap();

	//Accessors
	const bool tileEmpty(const int x, const int y, const int z) const;
	const Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;
	const Vector2i& getMaxSizeGrid() const;
	const Vector2f& getMaxSizeF() const;
	void setMaxSizeGrid(Vector2i max_size_grid);

	//Functions
	void addTile(const int x, const int y, const int z, const IntRect& texture_rect, const bool& collision, const short& type);
	void addTile(const int x, const int y, const int z, const IntRect & texture_rect,
		const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_md);
	void removeTile(const int x, const int y, const int z, const int type = -1);
	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	const bool checkType(const int x, const int y, const int z, const int type) const;

	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateTileCollision(Entity* entity, const float& dt);
	void updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
	void update(Entity * entity, const float & dt);

	void render(
		RenderTarget& target,
		const Vector2i& gridPosition, 
		Shader* shader = NULL, 
		const Vector2f playerPosition = Vector2f(),
		const bool show_collision = false,
		const bool show_enemy_spawners = false,
		const bool show_outmap = false,
		const bool show_create_border = false
	);
	void renderDeferred(RenderTarget& target, Shader* shader = NULL, const Vector2f playerPosition = Vector2f());
};

#endif