#ifndef __Enemy_H__
#define __Enemy_H__
#include "cocos2d.h"

USING_NS_CC;

class Enemy: public cocos2d::Sprite{
	private:
		int enemyType;
		float walkingSpeed;
		float *pointArray;
		int enemyWayPointIndex;
		int enemyWayPointNumber;
		Point startLocation;
		Size enemySize;
	public:
		int maxHp;
		int currentHp;
		bool isAlive;
		bool isReached;
		static Enemy* create(const char *pszFileName);
		void initEnemy(Point enemyLocation,float *pointArray,int arraySize,int enemyType,int enemySpeed);
		void move(int wayPointIndex);
		void update(float delta);
};
#endif // 
