#include "Game.h"
#include "graphics.h"
#include "Config.h"

void Game::spawnEnemies()
{
	if (getEnemiesKilled() != 0 && fmodf(getEnemiesKilled(), 30.0f) == 0.0f)
	{
		delete army;
		army = nullptr;
		enemy_initialized = false;
	}
	if (!enemy_initialized && graphics::getGlobalTime() > 2000) // emfanizetai meta apo 1sec.
	{
		army = new Enemy *[30];
		for (int i = 0; i < 30; i++) {
			army[i] = new Enemy(); // derefference of "this".
			if (i < 10) {
				army[i]->setPos(50.0f + (i % 10) * 100, 50.0f);
				army[i]->setEnemyType(0);
			}
			else if (i < 20) {
				army[i]->setPos(50.0f + (i % 10) * 100, 150.0f);
				army[i]->setEnemyType(1);
			}
			else if (i < 30) {
				army[i]->setPos(50.0f + (i % 10) * 100, 250.0f);
				army[i]->setEnemyType(2);
			}

		}
		enemy_initialized = true;
	}

}

void Game::drawEnemies()
{
	if (army) {
		for (int i = 0; i < 30; i++) { // i < army.length
			
			if (army[i]) 
			{
				army[i]->setDebugMode(this->getDebugMode());
				army[i]->draw();
			}
		}
	}
}

bool Game::checkEnemyCollision(Enemy* enemy, bool isPlayer)
{
	
	if (!isPlayer)
	{
		if (!player->getBullet() || !enemy) //if one of them doesn't exist ... 
		{
			return false;
		}

		Disk d1 = player->getBullet()->getCollisionHull();
		Disk d2 = enemy->getCollisionHull();

		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrtf(dx * dx + dy * dy) < d1.radius + d2.radius)
		{
			player->getBullet()->setActive(false);
			return true;
		}
		else
			return false;
	}
	else
	{
		if (!enemy|| !enemy->getBullet()) //if one of them doesn't exist ... 
		{
			return false;
		}

		Disk d1 = enemy->getBullet()->getCollisionHull();
		Disk d2 = player->getCollisionHull();

		float dx = d1.cx - d2.cx;
		float dy = d1.cy - d2.cy;

		if (sqrtf(dx * dx + dy * dy) < d1.radius + d2.radius)
		{
			enemy->getBullet()->setActive(false);
			return true;
		}
		else
			return false;
	}
}

bool Game::checkArmyPosition(Enemy* enemy)
{
	if (enemy->getCollisionHull().cy + enemy->getCollisionHull().radius > CANVAS_HEIGHT - 140)
	{
		return true;
	}
	return false;
}


void Game::updateStartScreen()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	if (ms.button_left_pressed)
	{
		status = STATUS_PLAYING;
	}

	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
}

void Game::updateLevelScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000) // emfanizetai meta apo 1sec.
	{
		player = new Player(); //derefference of "this".
		player_initialized = true;
	}

	spawnEnemies();
	


	if (player)
		player->update();

	if (army) { //checking if array of pointers (army) exists.
		for (int i = 0; i < 30; i++) {
			if (army[i]) // checking if a pointer (member of the army) exists.
				army[i]->update();
		}
	}
	for (int i = 0; i < 30; i++) 
	{
		if (army && army[i])
		{
			if (checkEnemyCollision(army[i], false)) 
			{
				explosion = new Explosion();
				explosion->setPos(army[i]->getPosX(), army[i]->getPosY());
				explosion->playSound();
				delete army[i]; //prepei na vrei i xristina efe krousis (ekriksi + ixos). kainourio gameObject, emfanizetai otan pethainei kapoio enemy
				//paizei to animation kai to svinoume.
				army[i] = nullptr;
				enemyKill();
			}
			if (checkEnemyCollision(army[i], true))
			{
				player->drainLife(0.2f);
				playerExplosion = new Explosion();
				playerExplosion->setPos(player->getPosX(), player->getPosY());
				playerExplosion->playSound();
			}
			if (army[i] && checkArmyPosition(army[i]))
			{
				player->drainLife(1.0f);
			}
		}
	}

	if (explosion && !explosion->isActive())
	{
		delete explosion;
		explosion = nullptr;
	}

	if (playerExplosion && !playerExplosion->isActive())
	{
		delete playerExplosion;
		playerExplosion = nullptr;
	}

	if (explosion)
		explosion->update();

	if (playerExplosion)
		playerExplosion->update();

	if (player && player->getRemainingLife() <= 0.0f)
	{
		status = STATUS_END;
	}

}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		//reseting before restarting the game.
		
		enemiesKilled = 0.0f;
		player_initialized = false;
		enemy_initialized = false;
		if (player)
		{
			delete player;
			player = nullptr;
		}
		if (explosion)
		{
			delete explosion;
			explosion = nullptr;
		}
		if (playerExplosion)
		{
			delete playerExplosion;
			playerExplosion = nullptr;
		}
		for (int i = 0; i < 30; i++) {
			if (army[i])
				delete army[i];
				army[i] = nullptr;
		}
		if (army)
		{
			delete army;
			army = nullptr;
		}
		status = STATUS_PLAYING;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Press ENTER to start!"); // 6 akeraia psifia, 2 dekadika (meionoume thorivo apo tis sintetagmenes)
	graphics::drawText(CANVAS_WIDTH/2 - 120, CANVAS_HEIGHT/2, 30, info, br);

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	graphics::drawDisk(window2CanvasX(ms.cur_pos_x), window2CanvasY(ms.cur_pos_y),10,br);
}

void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	

	//draw player
	if (player)
	{
		player->setDebugMode(this->getDebugMode());
		player->draw();
	}

	drawEnemies();

	if (explosion)
	{
		explosion->draw();
	}

	if (playerExplosion)
	{
		playerExplosion->draw();
	}

	drawUI();
}

void Game::drawEndScreen()
{
	if (enemiesKilled > maxEnemiesKilled)
	{
		maxEnemiesKilled = enemiesKilled;
	}

	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Score: %6.0f", getEnemiesKilled() * 100.0f); // 6 akeraia psifia, 2 dekadika (meionoume thorivo apo tis sintetagmenes)
	graphics::drawText(CANVAS_WIDTH / 2 - 70.0f, CANVAS_HEIGHT / 2, 30, info, br);
	sprintf_s(info, "Press Enter to try again!");
	graphics::drawText(CANVAS_WIDTH / 2 - 140.0f, CANVAS_HEIGHT / 2 + 30, 30, info, br);
	sprintf_s(info, "Highest score: %6.0f", getMaxEnemiesKilled() * 100.0f);
	graphics::drawText(CANVAS_WIDTH / 2 - 100.0f, CANVAS_HEIGHT / 2 + 60, 30, info, br);
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_END)
	{
		updateEndScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevelScreen();
		
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_END)
	{
		drawEndScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevelScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "bitstream.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "song.mp3", 0.4f, true, 4000);
}

void Game::drawUI()
{
	graphics::Brush br;
	// UI/info layer (sto telos gia na einai pano apo ola ta alla)
	if (player && debug_mode)
	{
		char info[40];
		sprintf_s(info, "(%6.2f, %6.2f, %6.2f)", player->getPosX(), player->getPosY(), graphics::getGlobalTime()); // 6 akeraia psifia, 2 dekadika (meionoume thorivo apo tis sintetagmenes)
		graphics::drawText(50, 70, 15, info, br);
	}
	char scoreInfo[40];
	sprintf_s(scoreInfo, "Score: %6.0f", getEnemiesKilled() * 100.0f);
	graphics::drawText(CANVAS_WIDTH - 120, CANVAS_HEIGHT - 30, 25, scoreInfo, br);

	float player_life = player ? player->getRemainingLife() : 0.0f; //if player exists, get his remaining life.

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f; // grammiki paremvoli, oso to player_life meionetai to kokkino ginetai pio entono.
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f; // orizontio gradient.
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(220 - 100 - ((1.0f - player_life) * 120 / 2), CANVAS_HEIGHT - 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f; //xoris gemisma.
	graphics::drawRect(220 - 100, CANVAS_HEIGHT - 30, 120, 20, br);
}

float Game::window2CanvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2CanvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}

	if (army)
	{
		for (int i = 0; i < 30; i++) {
			if(army[i])
			army[i] = nullptr;
		}
		delete army;
	}
}
