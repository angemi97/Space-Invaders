#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"

class Game
{
	typedef enum {STATUS_START, STATUS_PLAYING, STATUS_END} status_t;
	Player * player = nullptr;
	bool player_initialized = false;
	float test = 0.0f;
	Enemy** army = nullptr; // pointer to pointers. (an army pointing to many enemies)
	Explosion* explosion = nullptr;
	Explosion* playerExplosion = nullptr;
	bool enemy_initialized = false;
	bool debug_mode = false;
	status_t status = STATUS_START;
	float enemiesKilled = 0.0f;
	float maxEnemiesKilled = 0.0f;
	unsigned int window_width = WINDOW_WIDTH,
		         window_height = WINDOW_HEIGHT;

	void spawnEnemies();
	void drawEnemies();
	bool checkEnemyCollision(Enemy* enemy, bool isPlayer);
	bool checkArmyPosition(Enemy* enemy);
	void updateStartScreen();
	void updateLevelScreen();
	void updateEndScreen();
	//void updateFinishScreen(); // gia ti teliki othoni.
	void drawStartScreen();
	void drawLevelScreen();
	void drawEndScreen();
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() { return debug_mode; }
	void update();
	void draw();
	void init();
	void drawUI();
	float getEnemiesKilled() { return enemiesKilled; }
	float getMaxEnemiesKilled() { return maxEnemiesKilled; }
	void enemyKill() { enemiesKilled += 1.0f; }
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2CanvasX(float x);
	float window2CanvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w;  window_height = h; }
	Game();
	~Game();
};