#include "Player.h"
#include "graphics.h"
#include "GameObject.h"
#include "Game.h"
#include "Bullet.h"

void Player::update()
{
	

	// WASD 
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f; // pros ta aristera, giafto kai -=
	}

	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (!bullet_initialized && graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		bullet = new Bullet();
		bullet->setBullet(true);
		bullet->setPos(pos_x, CANVAS_HEIGHT - 70);
		bullet_initialized = true;
		bullet->playSound();
	}

	if (bullet)
	{
		if (!bullet->isActive())
		{
			delete bullet;
			bullet_initialized = false;
			bullet = nullptr;
		}
	}

	if (bullet)
		bullet->update();

	//gia na mi vgainei apo ta oria tou kamva
	if (pos_x < 50) pos_x = 50;
	if (pos_x > CANVAS_WIDTH-50) pos_x = CANVAS_WIDTH-50;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/250); // gia na anavosvinei


	br.outline_opacity = 0.0f;

	br.texture = "";
	br.fill_color[0] = 1.0f; //RED
	br.fill_color[1] = 0.5f + glow*0.5f; //GREEN gia na anavosvinei
	br.fill_color[2] = 0.0f; //BLUE
	
	br.fill_secondary_color[0] = 0.3f; //RED
	br.fill_secondary_color[1] = 0.1f; //GREEN
	br.fill_secondary_color[2] = 0.0f; //BLUE
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(height, height);
	graphics::drawDisk(pos_x, pos_y + 35 * height, 20, br);
	br.fill_color[0] = 1.0f; 
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_secondary_color[0] = 1.0f;
	br.fill_secondary_color[1] = 1.0f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = false;
	graphics::resetPose();

	br.fill_opacity = 1.0f; // epanafora opacity
	br.texture = std::string(ASSET_PATH) + "theblueone.png";
	graphics::drawRect(pos_x, pos_y, size, size, br);
	graphics::resetPose(); // set orientation kai scale sto arxiko

	// debugging for collision.
	if (this->getDebugMode()) 
	{
		graphics::Brush brDebug;
		brDebug.outline_opacity = 1.0f;
		brDebug.texture = "";
		brDebug.fill_color[0] = 0.3f;
		brDebug.fill_color[1] = 1.0f;
		brDebug.fill_color[2] = 0.3f;
		brDebug.fill_opacity = 0.3f;
		brDebug.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brDebug);
	}


	if (bullet)
	{
		bullet->setDebugMode(this->getDebugMode());
		bullet->draw();
	}

}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size * 0.5f;

	return disk;
}
