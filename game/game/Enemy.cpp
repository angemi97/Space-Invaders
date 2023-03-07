#include "Enemy.h"
#include "graphics.h"
#include "Game.h"

void Enemy::update()
{
	pos_x = starting_x + speed * sinf(graphics::getGlobalTime() / 2000.0f);

	if (sinf(graphics::getGlobalTime() / 550.0f) > 0.95) //every 1 second, enemies drop closer.
	{
		pos_y += speed / 175.0f;
	}

	shootEnemyBullet();
	if (bullet)
		bullet->update();

	if (bullet)
	{
		if (!bullet->isActive())
		{
			delete bullet;
			bullet_initialized = false;
			bullet = nullptr;
		}
	}
}

void Enemy::draw()
{

	
	br.outline_opacity = 0.0f;
	if (enemyType == 0) {
		br.texture = std::string(ASSET_PATH) + "pinkguy.png";
	}
	else if (enemyType == 1) {
		br.texture = std::string(ASSET_PATH) + "sobreroship.png";
	}
	else if (enemyType == 2) {
		br.texture = std::string(ASSET_PATH) + "beurself.png";
	}
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::resetPose();

	if (bullet)
	{
		bullet->setDebugMode(this->getDebugMode());
		bullet->draw();
	}

	//draw collision circle
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

void Enemy::init()
{
	speed = 30.0f;
	starting_x = 0;
	pos_x = -100.0f;
	pos_y = -100.0f;
	enemyType = -1;
}

void Enemy::shootEnemyBullet()
{
	rng = rand() / (float)RAND_MAX;
	if (!bullet_initialized && rng >= 0.8f && fmodf(graphics::getGlobalTime(), 2500) < 20.0f)
	{
		bullet = new Bullet();
		bullet->setPos(pos_x, pos_y);
		bullet_initialized = true;
		bullet->setSpeed(5.25f);
		bullet->playSound();
	}
}

void Enemy::setPos(float pos_x, float pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->starting_x = pos_x;
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;

	return disk;
}

Enemy::~Enemy()
{
}

Enemy::Enemy()
{
	init();
}

void Enemy::setEnemyType(int i)
{
	this->enemyType = i;
}


