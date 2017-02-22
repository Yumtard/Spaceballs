#pragma once

#include "RectF.h"
#include "Vec2.h"
#include "BulletManager.h"
#include "Graphics.h"
#include "Animation.h"

class SmallEnemyShip
{
public:
	enum EnemyState
	{
		AliveState, DyingState, DeadState
	};
	SmallEnemyShip(float x, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, BulletManager& smallEnemyBulletM);
	void Attack(float dt);
	void Move(float dt, float playerX);
	void Update(float dt, float playerX);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect() const;
	void Reset();
	void HandleCollision(int dmg);
	int GetCollisionDmg() const;
	bool IsAlive() const;
	bool GetCoolDown() const;

private:
	bool coolDown = false;
	static constexpr float coolDownOver = 0.5f;
	float coolDownTime = 0.0f;
	Vec2 pos;
	float resetX;
	Vec2 vel = Vec2(200.0f, 100.0f);
	BulletManager bulletM;
	int hp = 80;
	static constexpr float width = 90.0f;
	static constexpr float height = 70.0f;
	static constexpr int collisionDmg = 50;
	EnemyState state = AliveState;
	Animation smallExhaust;
	Animation smallExplode;
	Sound& smallExploSound;
	BulletManager& smallBManager;
	float fireBullet = 0.5f;
	float bulletTimer = 0.0f;
};