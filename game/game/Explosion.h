#pragma once
#include "GameObject.h"
#include "Config.h"
#include "graphics.h"

class Explosion : public GameObject
{
	float pos_x, pos_y;
	float size = 40.0f;
	float starting_time;
	bool active = true;
	graphics::Brush br;
public:
	void update() override;
	void draw() override;
	void init() override;
	void playSound();
	bool isActive() { return active; }
	void setActive(bool f) { active = f; }
	void setPos(float pos_x, float pos_y);
	Explosion();
	~Explosion();
};