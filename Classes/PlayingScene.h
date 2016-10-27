#ifndef __PLAYING_SCENE_H__
#define __PLAYING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class PlayingScene : public cocos2d::Layer
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

    void Touch_bt1(Ref* pSender);
    void Touch_bt2(Ref* pSender);
    void Touch_bt3(Ref* pSender);
    void Touch_bt4(Ref* pSender);
    void Touch_bt5(Ref* pSender);

    void GameLogic(float dt);
    void Playmusic();
    void GetBluetoothResult();
    void create_obj1(int data);
    void create_obj2(int data);
    void create_obj3(int data);
    void create_obj4(int data);
    void create_obj5(int data);
    void create_dis1(cocos2d::CCNode* sender);
    void create_dis2(cocos2d::CCNode* sender);
    void create_dis3(cocos2d::CCNode* sender);
    void create_dis4(cocos2d::CCNode* sender);
    void create_dis5(cocos2d::CCNode* sender);
    void Readdata();
    void Run();
    void showEnd();
    void endSence(Ref* pSender);
    void Ai(int click);
    void Rope(int left);
    void Menu(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayingScene);
};

#endif // __PLAYING_SCENE_H__
