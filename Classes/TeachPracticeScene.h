#ifndef __TEACH_PRACTICE_SCENE_H__
#define __TEACH_PRACTICE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class TeachPracticeScene : public cocos2d::Layer
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
    void battle_bt(cocos2d::Ref* pSender);

    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    // implement the "static create()" method manually
    CREATE_FUNC(TeachPracticeScene);
};

#endif // __TEACH_PRACTICE_SCENE_H__
