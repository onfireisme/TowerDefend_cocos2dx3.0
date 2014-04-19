#include "MainScene.h"
Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool MainScene::init()
{
    if( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) ) //RGBA
    {
        return false;
    }
    this->visibleSize = Director::getInstance()->getVisibleSize();
    this->origin = Director::getInstance()->getVisibleOrigin();
	this->initMenu();
	this->restartButton=Sprite::create("restartButton.png");
	this->restartButton->setPosition(Point(restartButton->getContentSize().width/2,this->getContentSize().height-restartButton->getContentSize().height/2));
	this->addChild(this->restartButton,3);
	//
	TTFConfig config("fonts/Marker Felt.ttf",20);
	startLabel=Label::createWithTTF(config,"start this game"
			,TextHAlignment::LEFT);
	this->startLabel->setColor(Color3B(138,54,15));
	this->startLabel->setPosition(this->getContentSize().width/2-this->startLabel->getContentSize().width/2,
			this->getContentSize().height/2-this->startLabel->getContentSize().height/2);
	this->addChild(this->startLabel);
    auto _restartButtonControlListener= EventListenerTouchOneByOne::create();
    _restartButtonControlListener->onTouchBegan = CC_CALLBACK_2(MainScene::restartButtonClickBegin, this);
    _restartButtonControlListener->onTouchEnded = CC_CALLBACK_2(MainScene::restartButtonClickEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_restartButtonControlListener, this->restartButton);
	//
    auto _startLabelControlListener= EventListenerTouchOneByOne::create();
    _startLabelControlListener->onTouchBegan = CC_CALLBACK_2(MainScene::startLabelClickBegin, this);
    _startLabelControlListener->onTouchEnded = CC_CALLBACK_2(MainScene::startLabelClickEnd, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_startLabelControlListener, startLabel);
	//
	this->inScene=NULL;
	this->outScene=NULL;
	return true;
}
void MainScene::initMenu(){
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(this->origin.x + this->visibleSize.width - closeItem->getContentSize().width/2 ,
                                this->origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 3);
}
bool MainScene::restartButtonClickBegin(Touch* touch, Event  *event){
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
void MainScene::restartButtonClickEnd(Touch* touch, Event  *event){
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setOpacity(255);
	if(this->inScene==NULL){
		return;
	}
	this->outScene=this->inScene;
	this->inScene=TowerDefend::createScene();
	this->removeChild(this->outScene);
	this->addChild(this->inScene,2);
}
bool MainScene::startLabelClickBegin(Touch* touch, Event  *event){
	auto target = static_cast<Label*>(event->getCurrentTarget());
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
void MainScene::startLabelClickEnd(Touch* touch, Event  *event){
	auto target = static_cast<Label*>(event->getCurrentTarget());
	target->setOpacity(255);
	if(this->inScene!=NULL){
		this->outScene=this->inScene;
		this->inScene=TowerDefend::createScene();
		this->removeChild(this->outScene);
		this->addChild(this->inScene,2);
		return;
	}
	this->inScene=TowerDefend::createScene();
	this->addChild(this->inScene,2);
}
void MainScene::menuCloseCallback(Object* pSender){
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
