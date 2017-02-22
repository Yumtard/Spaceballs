#include "EnemyManager.h"

EnemyManager::EnemyManager(AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, BulletManager& smallEnemyBulletM)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 545.0f);
	for (int i = 0; i < nSmallShipMax; ++i)
	{
		smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ xDist(rng), smallexhaust, smallexplode, smallexplo, smallEnemyBulletM });
	}
}

void EnemyManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Draw(gfx);
	}
}

void EnemyManager::Reset()
{
	nSmallShip = 0;
	smallShipCounter = 0.0f;
	for (int i = 0; i < nSmallShipMax; ++i)
	{
		smallShip[i].Reset();
	}
}

void EnemyManager::Update(float dt, float playerX)
{
	if ((smallShipCounter += dt) >= newSmallShip && nSmallShip != nSmallShipMax)
	{
		smallShipCounter = 0.0f;
		nSmallShip++;
	}

	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Update(dt, playerX);
	}
}

int EnemyManager::GetSmallCount() const
{
	return nSmallShip;
}

SmallEnemyShip & EnemyManager::GetSmallShip(int Idx)
{
	return smallShip[Idx];
}

const SmallEnemyShip & EnemyManager::GetSmallShip(int Idx) const
{
	return smallShip[Idx];
}