#ifndef __TEACH_BASIC_INTRO_SCENE_H__
#define __TEACH_BASIC_INTRO_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class TeachBasicIntroScene : public cocos2d::Layer
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

    void ReadData();

    // implement the "static create()" method manually
    CREATE_FUNC(TeachBasicIntroScene);
};

#endif // __TEACH_BASIC_INTRO_SCENE_H__