#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // transition to story scene
    void tranToStory(cocos2d::Ref* pSender);

    // transition to game scene
    void tranToGame(Ref* pSender);
    void tranToMasterGame(Ref* pSender);
    // implement the "static create()" method manually
    void bluetooth(Ref* pSender);
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
