#ifndef __TEACHSCENE_H__
#define __TEACHSCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class TeachScene : public cocos2d::Layer
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

    // trans to teach one
    void tranToTeachOne(cocos2d::Ref* sender);

    // trans to the introduction
    void tranToTeachTwoIntro(cocos2d::Ref* sender);

    // trans to the teach mode
    void tranToTeachThreeTeach(cocos2d::Ref* sender);

    void backtomain(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(TeachScene);
};

#endif // __TEACHSCENE_H__
