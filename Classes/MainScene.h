#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__
#include "cocos2d.h"
#include "TowerDefend.h"

USING_NS_CC;
class MainScene: public cocos2d::LayerColor{
	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();
		Scene *outScene;
		Scene *inScene;
		void menuCloseCallback(Object* pSender);
		bool restartButtonClickBegin(Touch* touch, Event  *event);
		void restartButtonClickEnd(Touch* touch, Event  *event);
		bool startLabelClickBegin(Touch* touch, Event  *event);
		void startLabelClickEnd(Touch* touch, Event  *event);

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  
		CREATE_FUNC(MainScene);
	private:
		void initMenu();
		Size visibleSize;
		Point origin;
		Sprite *restartButton;
		Label *startLabel;
};
#endif // 
