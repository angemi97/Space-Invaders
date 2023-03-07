#pragma once
#include "GameObject.h"
#include "Config.h"
#include "graphics.h"
#include "Bullet.h"

class Player : public GameObject, public Collidable
{
	Bullet* bullet = nullptr;
	float speed = 1.15f;
	float pos_x = CANVAS_WIDTH/2 , pos_y= CANVAS_HEIGHT-70;
	float height = 1.0f;
	float size = 70.0f;
	float life = 1.0f;
	graphics::Brush br;
	bool debugMode = false;
	bool bullet_initialized = false;
public:
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	void setDebugMode(bool mode) { debugMode = mode; }
	bool getDebugMode() { return debugMode; }
	float getRemainingLife() const { return life; }
	Disk getCollisionHull() const override;
	Bullet* getBullet() { return bullet; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); } //life = max value of (0, life)
};