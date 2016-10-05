#include "MainScene.h"
#include "TeachHowToPlayScene.h"
#include "TeachScene.h"
#include "PlayingScene.h"
USING_NS_CC;

const char* story_pic2 ;
extern int data_stage;

Scene* TeachHowToPlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TeachHowToPlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TeachHowToPlayScene::init()
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
    auto story = ImageView::create(story_pic2);
    story->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));


    auto battle = Button::create("Button_battle.png");
    battle->setPosition(Vec2(visibleSize.width/2 + origin.x+200, visibleSize.height*2/7 + origin.y));
    battle->addClickEventListener(CC_CALLBACK_1(TeachHowToPlayScene::battle_bt, this));
    // add the transition function event
    auto cancel = Button::create("Button_cancel.png");
    cancel->setPosition(Vec2(visibleSize.width/2 + origin.x-200, visibleSize.height*2/7 + origin.y));
    cancel->addClickEventListener(CC_CALLBACK_1(TeachHowToPlayScene::tranToStory, this));

    story->addChild(battle);
    story->addChild(cancel);

    sprite->addChild(story);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    

    return true;
}
void TeachHowToPlayScene::ReadData(){

    switch(data_stage){
    case 4:
        story_pic2 = "black_esp4.png";
        break;
    case 5:
        story_pic2 = "black_esp5.png";
        break;
    case 6:
        story_pic2 = "black_esp6.png";
        break;
    case 7:
        story_pic2 = "black_esp7.png";
        break;
    case 8:
        story_pic2 = "black_esp8.png";
        break;
    case 9:
        story_pic2 = "black_esp9.png";
        break;

    }

}
void TeachHowToPlayScene::tranToStory(Ref* pSender){
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachScene::create());

    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);

}
void TeachHowToPlayScene::battle_bt(Ref* pSender){

    auto scene = Scene::create();
    PlayingScene *layer = PlayingScene::create();
//    layer->init();
    scene->addChild(layer);

    auto transitions = TransitionFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);
}

void TeachHowToPlayScene::menuCloseCallback(Ref* pSender)
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
