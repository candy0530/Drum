#include "MainScene.h"
#include "TeachBasicIntroScene.h"
#include "TeachHowToPlayScene.h"
#include "TeachScene.h"
USING_NS_CC;

const char* story_pic1 ;
extern int data_stage;

Scene* TeachBasicIntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TeachBasicIntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TeachBasicIntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    ReadData();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("teach_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the story content
    auto story = ImageView::create(story_pic1);
    story->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));


    auto button = Button::create("Button.png");
    button->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*2/7 + origin.y));
    button->addClickEventListener(CC_CALLBACK_1(TeachBasicIntroScene::tranToStory, this)); // add the transition function event
    story->addChild(button);
    sprite->addChild(story);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    

    return true;
}

void TeachBasicIntroScene::ReadData(){

    switch(data_stage){
    case 1:
        story_pic1 = "black_esp0.png";
        break;
    case 2:
        story_pic1 = "black_esp1.png";
        break;
    }
}

void TeachBasicIntroScene::tranToStory(Ref* pSender){
    Director::getInstance()->popScene();

}

void TeachBasicIntroScene::menuCloseCallback(Ref* pSender)
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
