#ifndef __Bullet_H__
#define __Bullet_H__
#include "cocos2d.h"
#include "Enemy.h"
USING_NS_CC;
class Bullet: public cocos2d::Sprite{
	public:
		static Bullet* create(const char *pszFileName);
		void initBullet(Enemy *enemy,int damage,float bulletSpeed);
	private:
		Enemy *attackedEnemy;
		int type;
		int damage;
		float bulletSpeed;
		void update(float delta);
		void moveToEnemy(Enemy *enemy);
		void shootEnemy();
};
#endif // 
