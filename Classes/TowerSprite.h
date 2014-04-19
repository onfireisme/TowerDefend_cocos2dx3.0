#ifndef __TowerSprite_H__
#define __TowerSprite_H__
#define BULLETNUMBER 10

#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
#define GOLD 0
#define WOOD 1
#define WATER 2
#define FIRE 3
#define EARTH 4

USING_NS_CC;

class TowerSprite: public cocos2d::Sprite{
	private:
		int towerType;
		float attackRange;
		int damage;
		float fireRate;
		float bulletSpeed;
		Sprite *bulletFather;
		Enemy *attackedEnemy;
		Vector <Sprite *>bulletVector;
	public:
		bool isActived;
		static TowerSprite* create(const char *pszFileName);
		void initTowerSprite(int towerType);
		bool isAtRange(Enemy *enemy);
		void targetEnemy(Enemy *enemy);
		void shootBullet();
		void shootEnemy(Sprite *bullet);
		void move(float delta);
		void update(float delta);
};
#endif // __TowerDefend_SCENE_H__
