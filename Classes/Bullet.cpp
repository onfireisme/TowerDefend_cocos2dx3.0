#include "Bullet.h"
Bullet* Bullet::create(const char *pszFileName)
{
    Bullet *pobSprite = new Bullet();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void Bullet::initBullet(Enemy *enemy,int damage,float bulletSpeed){
	this->attackedEnemy=enemy;
	this->damage=damage;
	this->bulletSpeed=bulletSpeed;
	this->scheduleUpdate();
}
void Bullet::shootEnemy(){
	Point enemyNodePosition=
		this->getParent()->convertToNodeSpace(this->attackedEnemy->getPosition());
	Point bulletWorldSpacePosition=this->getParent()->convertToWorldSpace(this->getPosition());
	Point enemyPosition=this->attackedEnemy->getPosition();
	Size enemySize=this->attackedEnemy->getContentSize();
	Size bulletSize=this->getContentSize();
	Rect bulletRect=Rect(bulletWorldSpacePosition.x-bulletSize.width/2,
			bulletWorldSpacePosition.y-bulletSize.height/2,bulletSize.width,bulletSize.height);
	Rect enemyRect=Rect(enemyPosition.x-enemySize.width/2,enemyPosition.y-enemySize.height/2,
			enemySize.width,enemySize.height);
	if(enemyRect.intersectsRect(bulletRect)){
		this->attackedEnemy->currentHp=this->attackedEnemy->currentHp-this->damage;
		this->setScale(5.0f);
		this->unscheduleAllSelectors();
		this->setVisible(false);
		log("bang");
		return;
	}
//	log("bang");
	float distance=bulletWorldSpacePosition.getDistance(enemyPosition)/bulletSpeed;
	MoveTo *moveTowardEnemy=MoveTo::create(distance,enemyNodePosition);
	this->runAction(moveTowardEnemy);
}
void Bullet::update(float delta)
{
	this->shootEnemy();
}
