#include "Bullet.h"
#include "graphics.h"
#include "Game.h"

void Bullet::update()
{
	if (isPlayerBullet)
	{
		pos_y -= speed;

		if (pos_y < 0)
			active = false;
	}
	else
	{
		pos_y += speed / 3.0f;

		if (pos_y > CANVAS_HEIGHT)
			active = false;
	}

}

void Bullet::playSound()
{
	if (isPlayerBullet)
	{
		graphics::playSound(std::string(ASSET_PATH) + "shoot.mp3", 0.5f, false);
	}
	else
	{
		graphics::playSound(std::string(ASSET_PATH) + "shoot.mp3", 0.02f, false);
	}
	
}

void Bullet::draw()
{
	br.outline_opacity = 0.0f;
	if (!isPlayerBullet)
	{
		br.texture = std::string(ASSET_PATH) + "enemyBullet.png";
	}
	else
	{
		br.texture = std::string(ASSET_PATH) + "playerBullet.png";
	}

	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::resetPose();
	
	if (this->getDebugMode()) {
		graphics::Brush brDebug;
		brDebug.outline_opacity = 1.0f;
		brDebug.texture = "";
		brDebug.fill_color[0] = 1.0f;
		brDebug.fill_color[1] = 0.3f;
		brDebug.fill_color[2] = 0.3f;
		brDebug.fill_opacity = 0.3f;
		brDebug.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brDebug);
	}

}

void Bullet::init()
{
	speed = 2.25f;
}

void Bullet::setPos(float pos_x, float pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;

	return disk;
}

Bullet::Bullet()
{
	init();
}

Bullet::~Bullet()
{
}
