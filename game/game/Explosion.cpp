#include "Explosion.h"

void Explosion::update()
{
	if (graphics::getGlobalTime() - starting_time > 50.0f)
		active = false;
}

void Explosion::draw()
{
	br.outline_opacity = 0.0f;
	br.texture = std::string(ASSET_PATH) + "boom1.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
}

void Explosion::init()
{
	starting_time = graphics::getGlobalTime();
}

void Explosion::playSound()
{
	graphics::playSound(std::string(ASSET_PATH) + "Explosion.mp3", 0.15f, false);
}

void Explosion::setPos(float pos_x, float pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

Explosion::Explosion()
{
	init();
}

Explosion::~Explosion()
{
}
