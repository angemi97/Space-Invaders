#pragma once
#include "GameObject.h"
#include "Config.h"
#include "graphics.h"

class Bullet : public GameObject, public Collidable
{
	float speed;
	float pos_x, pos_y;
	float size = 25.0f;
	bool active = true;
	bool isPlayerBullet = false;
	graphics::Brush br;
	bool debugMode = false;
public:
	void update() override;
	void draw() override;
	void init() override;
	void playSound();
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	bool isActive() { return active; }
	void setActive(bool f) { active = f; }
	void setDebugMode(bool mode) { debugMode = mode; }
	void setSpeed(float sp) { speed = sp; }
	bool getDebugMode() { return debugMode; }
	void setPos(float pos_x, float pos_y);
	void setBullet(bool b) { isPlayerBullet = b; }
	Disk getCollisionHull() const override;
	Bullet();
	~Bullet();
};