#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, BulletManager& smallEnemyBulletM)
	:
	pos(x, -100.0f),
	resetX(x),
	smallExhaust(smallexhaust, 2),
	smallExplode(smallexplode, 3),
	smallExploSound(smallexplo),
	smallBManager(smallEnemyBulletM)
{}

void SmallEnemyShip::Attack(float dt)
{
	if (pos.y < Graphics::ScreenHeight && pos.y > 0.0f)
	{
		if ((bulletTimer += dt) > fireBullet)
		{
			smallBManager.FireBullet(pos, -600.0f, Colors::Cyan, 5, 10);
			smallBManager.ResetShotsFired();
			bulletTimer = 0.0f;
		}
	}
}

void SmallEnemyShip::Move(float dt, float playerX)
{
	pos.y += vel.y * dt;
	pos.x += vel.x * dt;
	if ((playerX - 200.0f) > pos.x)
	{
		vel.x = 200.0f;
	}
	else if ((playerX + 200.0f) < pos.x)
	{
		vel.x = -200.0f;
	}
	
	if (pos.x < 0.0f || (pos.x + width) > int(Graphics::ScreenWidth))
	{
		vel.x = -vel.x;
	}
}

void SmallEnemyShip::Update(float dt, float playerX)
{
	Move(dt, playerX);

	switch (state)
	{
	case AliveState:
		Attack(dt);
		if (coolDown)
		{
			if ((coolDownTime += dt) > coolDownOver)
			{
				coolDownTime = 0.0f;
				coolDown = false;
			}
		}

		smallExhaust.Advance();
		if (smallExhaust.AnimEnd())
		{
			smallExhaust.Reset();
		}

		if (hp <= 0)
		{
			state = DyingState;
			smallExploSound.Play(0.7f, 2.0f);
		}

		break;

	case DyingState:
		smallExplode.Advance();

		if (smallExplode.AnimEnd())
		{
			state = DeadState;
		}

		break;
	}
}

void SmallEnemyShip::Draw(Graphics & gfx)
{
	smallBManager.DrawBullets(gfx);
	switch (state)
	{
	case AliveState:
		smallExhaust.Draw(int(pos.x), int(pos.y), gfx);
		break;

	case DyingState:
		smallExplode.Draw(int(pos.x), int(pos.y), gfx);
		break;
	}
}
	
RectF SmallEnemyShip::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void SmallEnemyShip::Reset()
{
	pos.y = -100.0f;
	pos.x = resetX;
	smallExplode.Reset();
	state = AliveState;
	hp = 80;
}

void SmallEnemyShip::HandleCollision(int dmg)
{
	hp -= dmg;
	coolDown = true;
}

int SmallEnemyShip::GetCollisionDmg() const
{
	return collisionDmg;
}

bool SmallEnemyShip::IsAlive() const
{
	return state == AliveState;
}

bool SmallEnemyShip::GetCoolDown() const
{
	return coolDown;
}