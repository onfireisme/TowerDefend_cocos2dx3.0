#include "TowerDefend.h"

Scene* TowerDefend::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer= TowerDefend::create();

    // add layer as a child to scene
    scene->addChild(layer,1,1);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
/*init functions
 */
bool TowerDefend::init()
{
	this->isTowerAddPermit=false;
	this->towerType=FIRE;
    // 1. super init first
    if( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) //RGBA
    {
        return false;
    }
	//menu init

	// init the 
	this->initTowerDefend();
//	this->initMenu();
	this->initMouceClickEvent();
	this->initAddTowerButton();
	this->initPointArray(WAYPOINTNUMBER);
	this->drawWayLine();
	this->initScoreLabel();
	this->initCountdown();
	this->scheduleUpdate();
	this->initEnemyControlButton();
    return true;
}
void TowerDefend::initEnemyControlButton()
{
	TTFConfig config("fonts/Marker Felt.ttf",20);
	this->enemySpeedLabel=Label::createWithTTF(config,"enemy speed: 50"
			,TextHAlignment::LEFT);
	this->enemySpeedLabel->setColor(Color3B(138,54,15));
	this->enemySpeedLabel->setPosition(this->visibleWidthLength*4+20,this->visibleHeightLength*4);
	this->addChild(this->enemySpeedLabel);
	//
	this->enemySpeedUp=Sprite::create("speedUp.png");
	this->enemySpeedUp->setPosition(this->visibleWidthLength*4+this->enemySpeedUp->getContentSize().width,
			this->visibleHeightLength*4-30);
	this->addChild(this->enemySpeedUp);
	this->enemySpeedDown=Sprite::create("speedDown.png");
	this->enemySpeedDown->setPosition(this->visibleWidthLength*5,
			this->visibleHeightLength*4-30);
	this->addChild(this->enemySpeedDown);
	//
	this->enemyNumberLabel=Label::createWithTTF(config,"enemy number: 10 "
			,TextHAlignment::LEFT);
	this->enemyNumberLabel->setColor(Color3B(138,54,15));
	this->enemyNumberLabel->setPosition(this->visibleWidthLength*4+20,this->visibleHeightLength*3);
	this->addChild(this->enemyNumberLabel);
	//
	this->enemyNumberIncrease=Sprite::create("enemyNumberIncrease.png");
	this->enemyNumberIncrease->setPosition(this->visibleWidthLength*4+this->enemyNumberIncrease->getContentSize().width/2,
			this->visibleHeightLength*3-50);
	this->addChild(this->enemyNumberIncrease);
	this->enemyNumberDecrease=Sprite::create("enemyNumberDecrease.png");
	this->enemyNumberDecrease->setPosition(this->visibleWidthLength*5+
			this->enemyNumberDecrease->getContentSize().width/2,
			this->visibleHeightLength*3-50);
	this->addChild(this->enemyNumberDecrease);
	//
	this->enemyAddSpeedLabel=Label::createWithTTF(config,"enemy add Speed: 5"
			,TextHAlignment::LEFT);
	this->enemyAddSpeedLabel->setColor(Color3B(138,54,15));
	this->enemyAddSpeedLabel->setPosition(this->visibleWidthLength*4+20,this->visibleHeightLength*2-10);
	this->addChild(this->enemyAddSpeedLabel);
	//
	this->enemyAddSpeedUp=Sprite::create("enemyAddSpeedUp.png");
	this->enemyAddSpeedUp->setPosition(this->visibleWidthLength*4+this->enemyAddSpeedUp->getContentSize().width,
			this->visibleHeightLength*2-50);
	this->addChild(this->enemyAddSpeedUp);

	this->enemyAddSpeedDown=Sprite::create("enemyAddSpeedDown.png");
	this->enemyAddSpeedDown->setPosition(this->visibleWidthLength*5,
			this->visibleHeightLength*2-50);
	this->addChild(this->enemyAddSpeedDown);
	//set the listener
    auto _enemyControlListener= EventListenerTouchOneByOne::create();
    _enemyControlListener->onTouchBegan = CC_CALLBACK_2(TowerDefend::enemyControlClickBegin, this);
    _enemyControlListener->onTouchEnded = CC_CALLBACK_2(TowerDefend::enemyControlClickEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener, this->enemySpeedUp);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener->clone(), this->enemySpeedDown);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener->clone(), this->enemyNumberIncrease);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener->clone(), this->enemyNumberDecrease);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener->clone(), this->enemyAddSpeedUp);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_enemyControlListener->clone(), this->enemyAddSpeedDown);
}
//
bool TowerDefend::enemyControlClickBegin(Touch* touch, Event  *event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//Get the position of the current point relative to the button
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());

	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		target->setOpacity(180);
		return true;
	}
	return false;
}
void TowerDefend::enemyControlClickEnd(Touch* touch, Event  *event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setOpacity(255);
	char str1[100]="";
	char temp1[]="enemy speed: ";
	char temp2[]="enemy number: ";
	char temp3[]="enemy add speed: ";
	if(target==this->enemySpeedUp){
		this->enemySpeed++;
		sprintf(str1, "%d",this->enemySpeed);  
		strcat(temp1,str1);
		this->enemySpeedLabel->setString(temp1);
	}
	if(target==this->enemySpeedDown){
		if(this->enemySpeed<=1){
			return;
		}
		this->enemySpeed--;
		sprintf(str1, "%d",this->enemySpeed);  
		strcat(temp1,str1);
		this->enemySpeedLabel->setString(temp1);
	}
	if(target==this->enemyNumberIncrease){
		this->enemyNumber++;
		sprintf(str1, "%d",this->enemyNumber);  
		strcat(temp2,str1);
		this->enemyNumberLabel->setString(temp2);
	}
	if(target==this->enemyNumberDecrease){
		if(this->enemyNumber<=1){
			return;
		}
		this->enemyNumber--;
		sprintf(str1, "%d",this->enemyNumber);  
		strcat(temp2,str1);
		this->enemyNumberLabel->setString(temp2);
	}
	if(target==this->enemyAddSpeedUp){
		this->enemyAddSpeed=this->enemyAddSpeed+0.5f;
		sprintf(str1, "%f",this->enemyAddSpeed);  
		strcat(temp3,str1);
		this->enemyAddSpeedLabel->setString(temp3);
	}
	if(target==this->enemyAddSpeedDown){
		if(this->enemyAddSpeed<=1.0f){
			return;
		}
		this->enemyAddSpeed=this->enemyAddSpeed-0.5f;
		sprintf(str1, "%f",this->enemyAddSpeed);  
		strcat(temp3,str1);
		this->enemyAddSpeedLabel->setString(temp3);
	}
}
void TowerDefend::initScoreLabel(){
	TTFConfig config("fonts/Marker Felt.ttf",20);
	// init the life
	this->lifeLabel=Label::createWithTTF(config,"life: 30 ",
			TextHAlignment::LEFT);
	this->lifeLabel->setPosition(Point(visibleWidthLength*5+this->lifeLabel->getContentSize().width/2,
				visibleHeightLength*5+this->lifeLabel->getContentSize().height/2));
	this->lifeLabel->setColor(Color3B(255,215,0));
	this->addChild(this->lifeLabel,2);
	//
	Label *goldScore=Label::createWithTTF(config,"GOLD",
			TextHAlignment::LEFT);
	goldScore->setPosition(Point(visibleWidthLength,visibleHeightLength*5+70));
	goldScore->setColor(Color3B(255,215,0));
	this->addChild(goldScore,2);

	this->goldScoreLabel=Label::createWithTTF(config,"0",
			TextHAlignment::LEFT);
	this->goldScoreLabel->setPosition(Point(visibleWidthLength+goldScore->getContentSize().width+10
				,visibleHeightLength*5+70));
	this->goldScoreLabel->setColor(Color3B(255,215,0));
	this->addChild(this->goldScoreLabel,2);
	//
	Label *woodScore=Label::createWithTTF(config,"Wood",
			TextHAlignment::LEFT);
	woodScore->setPosition(Point(visibleWidthLength*2,visibleHeightLength*5+30));
	woodScore->setColor(Color3B(115,71,18));
	this->addChild(woodScore,2);

	this->woodScoreLabel=Label::createWithTTF(config,"0",
			TextHAlignment::LEFT);
	this->woodScoreLabel->setPosition(Point(visibleWidthLength*2+woodScore->getContentSize().width+10
				,visibleHeightLength*5+30));
	this->woodScoreLabel->setColor(Color3B(115,71,18));
	this->addChild(woodScoreLabel,2);
	//
	Label *waterScore=Label::createWithTTF(config,"Water",
			TextHAlignment::LEFT);
	waterScore->setPosition(Point(visibleWidthLength*3,visibleHeightLength*5+70));
	waterScore->setColor(Color3B(30,144,255));
	this->addChild(waterScore,2);

	this->waterScoreLabel=Label::createWithTTF(config,"0",
			TextHAlignment::LEFT);
	this->waterScoreLabel->setPosition(Point(visibleWidthLength*3+waterScore->getContentSize().width+10
				,visibleHeightLength*5+70));
	this->waterScoreLabel->setColor(Color3B(30,144,255));
	this->addChild(waterScoreLabel,2);
	//
	Label *fireScore=Label::createWithTTF(config,"Fire",
			TextHAlignment::LEFT);
	fireScore->setPosition(Point(visibleWidthLength*4,visibleHeightLength*5+30));
	fireScore->setColor(Color3B(255,0,0));
	this->addChild(fireScore,2);

	this->fireScoreLabel=Label::createWithTTF(config,"Fire",
			TextHAlignment::LEFT);
	this->fireScoreLabel->setPosition(Point(visibleWidthLength*4+fireScore->getContentSize().width+10
				,visibleHeightLength*5+30));
	this->fireScoreLabel->setColor(Color3B(255,0,0));
	this->addChild(fireScoreLabel,2);
	//
	Label *earthScore=Label::createWithTTF(config,"Earth",
			TextHAlignment::LEFT);
	earthScore->setPosition(Point(visibleWidthLength*5,visibleHeightLength*5+70));
	earthScore->setColor(Color3B(138,54,15));
	this->addChild(earthScore,2);

	this->earthScoreLabel=Label::createWithTTF(config,"0",
			TextHAlignment::LEFT);
	this->earthScoreLabel->setPosition(Point(visibleWidthLength*5+earthScore->getContentSize().width+10
				,visibleHeightLength*5+70));
	this->earthScoreLabel->setColor(Color3B(138,54,15));
	this->addChild(earthScoreLabel,2);
}
/*
void TowerDefend::initMenu(){
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TowerDefend::menuCloseCallback, this));
    
	closeItem->setPosition(Point(this->origin.x + this->visibleSize.width - closeItem->getContentSize().width/2 ,
                                this->origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}
*/
void TowerDefend::initTowerDefend(){
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
	this->visibleWidthLength=this->visibleSize.width/DIVIDED;
	this->visibleHeightLength=this->visibleSize.height/DIVIDED;
	this->originX=this->origin.x;
	this->originY=this->origin.y;
	this->enemyWave=0;
	this->enemyNumber=ENEMYNUMBR;
	this->isScheduleOn=true;
	this->enemyType=WATER;
	this->goldScore=0;
	this->woodScore=0;
	this->waterScore=0;
	this->fireScore=0;
	this->earthScore=0;
	this->enemySpeed=50;
	this->enemyAddSpeed=5.0f;
	this->isGameOver=false;
	this->life=LIFE;
}
void TowerDefend::initCountdown(){
	TTFConfig config("fonts/Marker Felt.ttf",30);
	this->countdownWordLabel=Label::createWithTTF(config,"the enemy is coming",
			TextHAlignment::LEFT);
	this->countdownWordLabel->setPosition(Point(visibleWidthLength*3-this->countdownWordLabel->getContentSize().width/2
				,visibleHeightLength*3));
	this->countdownWordLabel->setColor(Color3B(255,215,0));
	this->addChild(this->countdownWordLabel);
	//	
	this->countdownLabel=Label::createWithTTF(config,"10",
			TextHAlignment::LEFT);
	this->countdownLabel->setPosition(Point(visibleWidthLength*3-this->countdownLabel->getContentSize().width/2
				,visibleHeightLength*3-40.0f));
	this->countdownLabel->setColor(Color3B(255,215,0));
	this->addChild(this->countdownLabel);
	//
	this->isCountdownBegin=true;
	this->countdownNumber=COUNTDOWNTIME;
}
void TowerDefend::initMouceClickEvent(){
	// the listener of the mouse,which is used to check if we shoud add the tower
    auto _addTowerListener= EventListenerTouchOneByOne::create();
    _addTowerListener->onTouchBegan = CC_CALLBACK_2(TowerDefend::addTowerClickBegin, this);
    _addTowerListener->onTouchEnded = CC_CALLBACK_2(TowerDefend::addTowerClickEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerListener, this);
}
void TowerDefend::initPointArray(int size)
{
	int xArray[]={1,3,3,2,2,4,4,5};
	int yArray[]={5,5,4,4,1,1,5,5};
	int i=0;
	for(i=0;i<size;i++)
	{
		this->pointArray[2*i]=this->originX+this->visibleWidthLength*xArray[i];
		this->pointArray[2*i+1]=this->originY+this->visibleHeightLength*yArray[i];
	}
}
void TowerDefend::initAddTowerButton(){
	//the listener of the gold wood water button 
    auto _addTowerButtonListener= EventListenerTouchOneByOne::create();
    _addTowerButtonListener->onTouchBegan = CC_CALLBACK_2(TowerDefend::addTowerButtonClickBegin, this);
    _addTowerButtonListener->onTouchEnded = CC_CALLBACK_2(TowerDefend::addTowerButtonClickEnded, this);
	//we add the tower button 
	//glod button
	this->GoldTowerButton=Sprite::create("gold.png");
    this->GoldTowerButton->setPosition(Point(this->origin.
				x+this->GoldTowerButton->getContentSize().width/2+5,this->origin.y+
				this->GoldTowerButton->getContentSize().height/2 ));
    this->addChild(this->GoldTowerButton, 1);
	//wood button
	this->WoodTowerButton=Sprite::create("wood.png");
    this->WoodTowerButton->setPosition(Point(this->origin.
				x+this->visibleWidthLength+this->WoodTowerButton->getContentSize().width/2,this->origin.y+
				this->WoodTowerButton->getContentSize().height/2 ));
    this->addChild(this->WoodTowerButton, 1);
	//water button
	this->WaterTowerButton=Sprite::create("water.png");
    this->WaterTowerButton->setPosition(Point(this->origin.
				x+this->visibleWidthLength*2+this->WaterTowerButton->getContentSize().width/2,this->origin.y+
				this->WaterTowerButton->getContentSize().height/2 ));
    this->addChild(this->WaterTowerButton, 1);
	//fire button
	this->FireTowerButton= Sprite::create("fire.png");
    this->FireTowerButton->setPosition(Point(this->origin.
				x+this->visibleWidthLength*3+this->FireTowerButton->getContentSize().width/2,this->origin.y+
				this->FireTowerButton->getContentSize().height/2 ));
    this->addChild(this->FireTowerButton, 1);
	//earth button
	this->EarthTowerButton= Sprite::create("earth.png");
    this->EarthTowerButton->setPosition(Point(this->origin.
				x+this->visibleWidthLength*4+this->EarthTowerButton->getContentSize().width/2,this->origin.y+
				this->EarthTowerButton->getContentSize().height/2 ));
    this->addChild(this->EarthTowerButton, 1);
	//add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerButtonListener,this->GoldTowerButton);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerButtonListener->clone(),this->WoodTowerButton);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerButtonListener->clone(),this->WaterTowerButton);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerButtonListener->clone(),this->FireTowerButton);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_addTowerButtonListener->clone(),this->EarthTowerButton);
}
void TowerDefend::drawWayLine(){
	DrawNode* node = DrawNode::create();
	addChild(node,10);//Make sure your z-order is large enough
	int i=0;
	node->drawSegment(Point(this->visibleWidthLength,this->visibleHeightLength),
			Point(this->pointArray[0],this->pointArray[1])
			,5.0,Color4F(180,180,180,100));
	for(i=0;i<WAYPOINTNUMBER-1;i++){
		node->drawSegment(Point(this->pointArray[2*i],this->pointArray[2*i+1]),
				Point(this->pointArray[2*(i+1)],this->pointArray[2*(i+1)+1])
					,5.0,Color4F(180,180,180,100));
	}
}
/*
 * update function
 */
//in fact we don't need it ,what we need is the scheduleOnce
void TowerDefend::update(float delta){
	if(isGameOver){
		log("fuck");
		this->unscheduleAllSelectors();
	}
	this->checkEnemy();
	this->updateScoreLabel();
	if(this->isScheduleOn==true){
		if(this->isCountdownBegin==true){
			this->schedule(schedule_selector(TowerDefend::countdown),1.0f,ENEMYNUMBR,1.0f);
			this->isScheduleOn=false;
		}
		else{
			this->enemyType=this->getRandomEnemyType();
			this->schedule(schedule_selector(TowerDefend::addEnemy),this->enemyAddSpeed,ENEMYNUMBR,1.0f);
			this->isScheduleOn=false;
		}
	}
}
void TowerDefend::countdown(float delta){
	if(this->countdownNumber<=0){
		this->countdownLabel->setVisible(false);
		this->countdownWordLabel->setVisible(false);
		this->countdownNumber=COUNTDOWNTIME;
		this->isCountdownBegin=false;
		this->isScheduleOn=true;
		return;
	}
	this->countdownNumber--;
	char str[10]="";
	sprintf(str, "%d",this->countdownNumber);  
	this->countdownLabel->setString(str);
}
void TowerDefend::updateScoreLabel(){
	char str1[100]="0";
	char str2[100]="0";
	char str3[100]="0";
	char str4[100]="0";
	char str5[100]="0";
	//
	sprintf(str1, "%d",this->goldScore);  
	this->goldScoreLabel->setString(str1);
	//
	sprintf(str2, "%d",this->woodScore);  
	this->woodScoreLabel->setString(str2);
	//
	sprintf(str3, "%d",this->waterScore);  
	this->waterScoreLabel->setString(str3);
	//
	sprintf(str4, "%d",this->fireScore);  
	this->fireScoreLabel->setString(str4);
	//
	sprintf(str5, "%d",this->earthScore);  
	this->earthScoreLabel->setString(str5);
}
void TowerDefend::checkEnemy(){
	for(auto tower:towerVector){
		for(auto enemy:enemyVector){
			if(!enemy->isAlive){
				if(enemy->isReached){
					if(this->life>0){
						char str1[10]="0";
						char str2[]="life: ";
						this->life--;
						sprintf(str1, "%d",this->life);  
						strcat(str2,str1);
						this->lifeLabel->setString(str2);
					}
					else{
						char str2[]="game over!! ";
//						Director::getInstance()->replaceScene(TransitionFade::create(3.0f,this->getParent()));
						this->countdownWordLabel->setString(str2);
						this->countdownWordLabel->setVisible(true);
						this->isGameOver=true;
					}
				}
				else{
					if(this->enemyType==GOLD){
						this->goldScore++;
					}
					if(this->enemyType==WOOD){
						this->woodScore++;
					}
					if(this->enemyType==WATER){
						this->waterScore++;
					}
					if(this->enemyType==FIRE){
						this->fireScore++;
					}
					if(this->enemyType==EARTH){
						this->earthScore++;
					}
				}
				this->enemyVector.erase(enemyVector.find(enemy));
			}
			else{
				if(tower->isAtRange(enemy)&&!tower->isActived){
					tower->targetEnemy(enemy);
				}
			}
		}
	}
}
void  TowerDefend::addEnemy(float delta){
	if(this->enemyNumber<=0){
		this->countdownLabel->setVisible(true);
		this->countdownWordLabel->setVisible(true);
		this->enemyNumber=ENEMYNUMBR;
		this->isCountdownBegin=true;
		this->isScheduleOn=true;
		return;
	}
	Enemy *enemy;
	if(this->enemyType==GOLD){
		enemy=Enemy::create("goldEnemy.png");
	}
	if(this->enemyType==WOOD){
		enemy=Enemy::create("woodEnemy.png");
	}
	if(this->enemyType==WATER){
		enemy=Enemy::create("waterEnemy.png");
	}
	if(this->enemyType==FIRE){
		enemy=Enemy::create("fireEnemy.png");
	}
	if(this->enemyType==EARTH){
		enemy=Enemy::create("earthEnemy.png");
	}
	enemy->initEnemy(Point(this->visibleWidthLength,
				this->visibleHeightLength),&(this->pointArray[0]),WAYPOINTNUMBER,this->enemyType
			,this->enemySpeed);
	this->addChild(enemy);
	enemyVector.pushBack(enemy);
	this->enemyNumber--;
}
/*touch event functions
 */
bool TowerDefend::addTowerButtonClickBegin(Touch* touch, Event  *event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//Get the position of the current point relative to the button
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());

	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	//Check the click area
	if (rect.containsPoint(locationInNode))
	{
		target->setOpacity(180);
		return true;
	}
	return false;
}
void TowerDefend::addTowerButtonClickEnded(Touch* touch, Event  *event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setOpacity(255);

	if(target==this->GoldTowerButton){
		this->towerType=GOLD;
		log("GOLD");
	}
	if(target==this->WoodTowerButton){
		this->towerType=WOOD;
		log("WOOD");
	}
	if(target==this->WaterTowerButton){
		this->towerType=WATER;
		log("WATER");
	}
	if(target==this->FireTowerButton){
		this->towerType=FIRE;
		log("Fire");
	}
	if(target==this->EarthTowerButton){
		this->towerType=EARTH;
		log("Earth");
	}
	this->isTowerAddPermit=true;
}
bool TowerDefend::addTowerClickBegin(Touch* touch, Event  *event){
	if(this->isTowerAddPermit==false){
		return false;
	}
	return true;
}
void TowerDefend::addTowerClickEnded(Touch* touch, Event  *event){
	if(this->isTowerAddPermit==false){
		return;
	}
	//Get the position of the current point relative to the button
	Point clickLocation=touch->getLocation();
	TowerDefend::addTower(clickLocation);
	log("%f %f",clickLocation.x,clickLocation.y);
	this->isTowerAddPermit=false;
}
/*
 * add towers and enemys
 */
void TowerDefend::addTower(Point towerLocation){
	TowerSprite *tower;
	if(this->towerType==GOLD){
		tower=TowerSprite::create("goldTower.png");
	}
	if(this->towerType==WOOD){
		tower=TowerSprite::create("woodTower.png");
	}
	if(this->towerType==WATER){
		tower=TowerSprite::create("waterTower.png");
	}
	if(this->towerType==EARTH){
		tower=TowerSprite::create("earthTower.png");
	}
	if(this->towerType==FIRE){
		tower=TowerSprite::create("fireTower.png");
	}
	tower->setPosition(towerLocation);
	tower->initTowerSprite(this->towerType);
	this->addChild(tower);
	this->towerVector.pushBack(tower);
}
int TowerDefend::getRandomEnemyType()
{
	return rand()%4;
}
/*
void TowerDefend::menuCloseCallback(Object* pSender){
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
*/
