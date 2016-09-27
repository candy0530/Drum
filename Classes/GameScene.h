#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // pageview log
    void pageviewCallBack(cocos2d::Ref* sender, cocos2d::ui::PageViewEventType type);

    // transition to battle scene
    void tranToBattle(Ref* pSender);
    void backtomain(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
