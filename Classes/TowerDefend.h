#ifndef __TowerDefend_SCENE_H__
#define __TowerDefend_SCENE_H__
#include "cocos2d.h"
#include "Enemy.h"
#include "TowerSprite.h"

#define LELELONE 10
#define WAYPOINTNUMBER 8
#define DIVIDED 6
#define WAVENUMBER 3
#define WAITTIME 20
#define ENEMYNUMBR 10
#define WORDSIZE 25
#define COUNTDOWNTIME 10
#define LIFE 30

USING_NS_CC;

class TowerDefend: public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	TowerDefend *currentLayer;
    // a selector callback
//    void menuCloseCallback(Object* pSender);
    CREATE_FUNC(TowerDefend);

	//listener fucntions
	bool addTowerButtonClickBegin(Touch* touch, Event  *event);
	void addTowerButtonClickEnded(Touch* touch, Event  *event);
	bool addTowerClickBegin(Touch* touch, Event  *event);
	void addTowerClickEnded(Touch* touch, Event  *event);
	bool enemyControlClickBegin(Touch* touch, Event  *event);
	void enemyControlClickEnd(Touch* touch, Event  *event);
	//add tower
	void addTower(Point towerLocation);
	void addEnemy(float delta);
	void update(float delta);
	void checkEnemy();
	bool isScheduleOn;
	//
	bool isGameOver;
    
    // implement the "static create()" method manually
	private :
	Sprite *GoldTowerButton;
	Sprite *WoodTowerButton;
	Sprite *WaterTowerButton;
	Sprite *FireTowerButton;
	Sprite *EarthTowerButton;
	//score label
	Label *goldScoreLabel;
	Label *woodScoreLabel;
	Label *waterScoreLabel;
	Label *fireScoreLabel;
	Label *earthScoreLabel;
	//
	Label *lifeLabel;
	//
	Label *enemyNumberLabel;
	Label *enemySpeedLabel;
	Label *enemyAddSpeedLabel;
	//count down label
	Label *countdownLabel;
	Label *countdownWordLabel;
	bool isCountdownBegin;
	int countdownNumber;
	void countdown(float delta);
	//
	Sprite *enemySpeedUp;
	Sprite *enemySpeedDown;
	Sprite *enemyNumberIncrease;
	Sprite *enemyNumberDecrease;
	Sprite *enemyAddSpeedUp;
	Sprite *enemyAddSpeedDown;
	//
//	UISlider *enemySpeedControl;
//	UISlider *enemyNumberControl;
	//
	int goldScore;
	int woodScore;
	int waterScore;
	int fireScore;
	int earthScore;
	int life;
	//
	int isTowerAddPermit;
	int towerType;
	int enemyType;
	int wayPointNumber;
	int enemyWave;
	int enemyNumber;
	int enemySpeed;
	float visibleHeightLength;
	float visibleWidthLength;
	float originX;
	float originY;
	//
	float enemyAddSpeed;
	Point origin;
	Size visibleSize;
	float pointArray[WAYPOINTNUMBER*2];
	Vector<Enemy*> enemyVector;
	Vector<TowerSprite*>towerVector;
//	PointArray *pointArray;
	//init fucntion
	void initMouceClickEvent();
	void initTowerDefend();
	void initPointArray(ssize_t size);
	void initAddTowerButton();
	void initMenu();
	void initScoreLabel();
	void initEnemyControlButton();
	void drawWayLine();
	void initCountdown();
	//update functions
	void updateScoreLabel();
	// the other functions
	int getRandomEnemyType();
};

#endif // __TowerDefend_SCENE_H__
