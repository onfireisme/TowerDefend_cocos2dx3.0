#include "TowerDefend.h"
TowerSprite* TowerSprite::create(const char *pszFileName)
{
    TowerSprite *pobSprite = new TowerSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
void TowerSprite::initTowerSprite(int towerType){
	this->towerType=towerType;
	this->attackRange=80;
	this->isActived=false;
	this->damage=1;
	this->attackedEnemy=NULL;
	this->bulletSpeed=7;
	this->fireRate=1.0f;
	this->bulletFather=Sprite::create();
	this->addChild(bulletFather);
	this->schedule(schedule_selector(TowerSprite::update),this->fireRate);
}
bool TowerSprite::isAtRange(Enemy *enemy){
	if(this->attackRange>=this->getPosition().getDistance(enemy->getPosition())){
		return true;
	}
	return false;
}
void TowerSprite::shootBullet(){
	Bullet *bullet;
	if(this->towerType==GOLD){
		bullet=Bullet::create("goldBullet.png");
	}
	if(this->towerType==WOOD){
		bullet=Bullet::create("woodBullet.png");
	}
	if(this->towerType==WATER){
		bullet=Bullet::create("waterBullet.png");
	}
	if(this->towerType==FIRE){
		bullet=Bullet::create("fireBullet.png");
	}
	if(this->towerType==EARTH){
		bullet=Bullet::create("earthBullet.png");
	}
	bullet->setPosition(0.0f+this->getContentSize().width/2,0.0f+getContentSize().height/2);
	this->addChild(bullet);
	bullet->initBullet(this->attackedEnemy,this->damage,this->bulletSpeed);
//	this->bulletVector.pushBack(bullet);
}
void TowerSprite::targetEnemy(Enemy *enemy){
	this->isActived=true;
	this->attackedEnemy=enemy;
}
/*
void TowerSprite::shootEnemy(Sprite *bullet){
	if(bullet->boundingBox().intersectsRect(this->attackedEnemy->boundingBox())){
		this->attackedEnemy->currentHp=this->attackedEnemy->currentHp-this->damage;
		bullet->setVisible(false);
//		this->bulletFather->removeChild(bullet);
//		this->removeChild(bullet);
		this->bulletVector.erase(bulletVector.find(bullet));
		return;
	}
	Point enemyPosition=this->attackedEnemy->getPosition();
	Point bulletWorldSpacePosition=bullet->getParent()->convertToWorldSpace(bullet->getPosition());
	MoveTo *moveTowardEnemy=MoveTo::create(bulletWorldSpacePosition.
			getDistance(enemyPosition)/bulletSpeed,this->convertToNodeSpace(this->attackedEnemy->getPosition()));
	bullet->runAction(moveTowardEnemy);
}
*/
void TowerSprite::update(float delta){
	if(this->attackedEnemy==NULL){
		this->isActived=false;
		return;
	}
	if(!this->attackedEnemy->isAlive){
		this->isActived=false;
		this->attackedEnemy=NULL;
		return;
	}
	if(!isAtRange(this->attackedEnemy)){
		this->isActived=false;
		this->attackedEnemy=NULL;
		return;
	}
	this->shootBullet();
	/*
	for(auto bullet:bulletVector){
		this->shootEnemy(bullet);
	}
	*/
}
