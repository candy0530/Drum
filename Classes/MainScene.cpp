#include "MainScene.h"
#include "TeachScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "../proj.android/jni/hellocpp/Function.h"
USING_NS_CC;

extern int data_mode;
extern int data_stage;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    Director::getInstance()->pushScene(scene);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("NSMB.mp3",true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Main_v2.png");

    log("h:%f,w:%f",visibleSize.height,visibleSize.width);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    // add main_teach_button
    auto main_teach_button = Button::create("main_teach_button.png", "main_teach_button.png");
    main_teach_button->setPosition(Vec2(visibleSize.width/2 + origin.x + 10, visibleSize.height/2 + origin.y));
    main_teach_button->addClickEventListener(CC_CALLBACK_1(MainScene::tranToStory, this)); // add the transition function event
    this->addChild(main_teach_button, 0);

    // add main_game_button
    auto main_game_button = Button::create("main_game_button.png", "main_game_button.png");
    main_game_button->setPosition(Vec2(visibleSize.width/2 + origin.x + 10, visibleSize.height*3/8 + origin.y));
    main_game_button->addClickEventListener(CC_CALLBACK_1(MainScene::tranToGame, this));
    this->addChild(main_game_button, 0);

    // add main_game_master_button
    auto main_game_master_button = Button::create("main_game_master_button.png", "main_game_master_button.png");
    main_game_master_button->setPosition(Vec2(visibleSize.width/2 + origin.x + 10, visibleSize.height*1/4 + origin.y));
    main_game_master_button->addClickEventListener(CC_CALLBACK_1(MainScene::tranToMasterGame, this));
    this->addChild(main_game_master_button, 0);

    // add bluetooth button
    auto main_bluetooth = Button::create("main_bluetooth.png");
    main_bluetooth->setPosition(Vec2(visibleSize.width*7/9 + origin.x, visibleSize.height/25 + origin.y));
    main_bluetooth->addClickEventListener(CC_CALLBACK_1(MainScene::bluetooth, this));
    this->addChild(main_bluetooth, 0);

    // add the bluetooth signal
//    auto led = Button::create("main_led_red.png", "main_led_blue.png");
//    led->setPosition(Vec2(visibleSize.width*2/3 + origin.x, visibleSize.height/25 + origin.y));
//    this->addChild(led, 0);

    return true;
}

void MainScene::tranToStory(Ref* pSender){
    data_mode = 0;
    // if bluetooth open, send data 'A' to Linkit
    if(get_bluetooth_status()){
        sent_data("A");
    }
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachScene::create());

    // do the transition effect
    auto transitions = TransitionFade::create(0.3f, scene);
    Director::getInstance()->pushScene(transitions);

}

void MainScene::tranToGame(Ref* pSender){
    // if bluetooth open, send data 'B' to Linkit
    data_mode = 1;
    if(get_bluetooth_status()){
        sent_data("B");
    }
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(GameScene::create());

    // do the transition effect
    auto transitions = TransitionFade::create(0.3f, scene);
    Director::getInstance()->pushScene(transitions);
}

void MainScene::tranToMasterGame(Ref* pSender){
    data_mode = 2;
    // if bluetooth open, send data 'C' to Linkit
    if(get_bluetooth_status()){
        sent_data("C");
    }
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(GameScene::create());

    // do the transition effect
    auto transitions = TransitionFade::create(0.3f, scene);
    Director::getInstance()->pushScene(transitions);
}

void MainScene::bluetooth(Ref* pSender){
    log("open bt");
    openBT();
}

void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
