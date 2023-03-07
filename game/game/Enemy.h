#pragma once
#include "GameObject.h"
#include "Config.h"
#include "graphics.h"
#include "Bullet.h"

class Enemy : public GameObject, public Collidable
{
	float speed;
	float starting_x;
	float pos_x, pos_y;
	float size = 40.0f;
	int enemyType;
	int hp = 1;
	bool active = true;
	graphics::Brush br;
	bool debugMode = false;
	Bullet* bullet = nullptr;
	bool bullet_initialized = false;
	
public:
	float rng = 0.0f;
	void shootEnemyBullet();
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	bool isActive() { return active; }
	void setDebugMode(bool mode) { debugMode = mode; }
	bool getDebugMode() { return debugMode; }
	void setPos(float pos_x, float pos_y);
	void setEnemyType(int i);
	Disk getCollisionHull() const override;
	Bullet* getBullet() { return bullet; }
	Enemy();
	~Enemy();
};