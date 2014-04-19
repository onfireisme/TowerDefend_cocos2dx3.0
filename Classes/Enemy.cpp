#include "Enemy.h"
Enemy* Enemy::create(const char *pszFileName)
{
    Enemy *pobSprite = new Enemy();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
void Enemy::initEnemy(Point enemyLocation,float *pointArray,int arraySize,int enemyType,int enemySpeed)
{
	enemySize=this->getContentSize();
	this->walkingSpeed=enemySpeed;
	this->enemyType=enemyType;
	this->enemyWayPointIndex=0;
	this->isAlive=true;
	this->maxHp=3;
	this->currentHp=3;
	this->enemyWayPointNumber=arraySize;
	this->startLocation=enemyLocation;
	this->setPosition(enemyLocation);
	this->pointArray=pointArray;
	this->isReached=false;
//	this->move(this->enemyWayPointIndex);
	//this should be the last one
	this->scheduleUpdate();
	/*
	for(i;i<8;i++){
		log("%f %f",this->pointArray[2*i],this->pointArray[2*i+1]);
	}
	*/
}
void Enemy::move(int wayPointIndex)
{
	Point beginPoint;
	Point endPoint;
	if(wayPointIndex==0){
		beginPoint=this->startLocation;
	}
	else{
		beginPoint=Point(this->pointArray[2*(wayPointIndex-1)],
				this->pointArray[2*(wayPointIndex-1)+1]);
	}
	endPoint=Point(this->pointArray[2*wayPointIndex],
			this->pointArray[2*wayPointIndex+1]);
	MoveTo* act1 = MoveTo::create(endPoint.getDistance(
				beginPoint)/this->walkingSpeed,endPoint);
	this->runAction(act1);
}
void Enemy::update(float delta){
	if(this->currentHp<=0){
		this->setVisible(false);
		this->isAlive=false;
		this->unscheduleAllSelectors();
		return;
	}
	if(this->getPosition()==Point(this->pointArray[2*(this->enemyWayPointNumber-1)],this->pointArray[2*(this->enemyWayPointNumber-1)+1])){
		log("reached");
		this->isReached=true;
		this->currentHp=0;
		return;
	}
	if(this->enemyWayPointIndex==this->enemyWayPointNumber){
		return;
	}
	if(this->enemyWayPointIndex==0){
		this->move(0);
		this->enemyWayPointIndex++;
	}
	if(this->getPosition()==Point(this->pointArray[2*(this->enemyWayPointIndex-1)],this->pointArray[2*(this->enemyWayPointIndex-1)+1])){
		this->move(this->enemyWayPointIndex);
		(this->enemyWayPointIndex)++;
	}
}
