#include "MainScene.h"
#include "TeachPracticeScene.h"
#include "TeachScene.h"
#include "SpongeScene.h"
#include <sstream>

using namespace std;
USING_NS_CC;

Scene* TeachPracticeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TeachPracticeScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TeachPracticeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->setKeypadEnabled(true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    log("background");
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("teach_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(1080/2, 1920/2));

    // add the pageview
    auto pageView = PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(windowSize);

    // add page2 to page4
    /*for( int i = 1; i <= 5; i++ ){
        auto layout = Layout::create();
        layout->setSize(windowSize);
        layout->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        std::stringstream ss;
        ss << i;

        auto imageView = ImageView::create("esp2_page" + ss.str() + ".png");
        imageView->setAnchorPoint( Point::ANCHOR_BOTTOM_LEFT );
        imageView->setScale(1.0f);
        layout->addChild(imageView);

        pageView->addPage(layout);
    }*/

    log("start");
    auto layout1 = Layout::create();
    layout1->setBackGroundImage("esp2_page1.png");
    layout1->setSize(windowSize);
    layout1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pageView->addPage(layout1);

    auto layout2 = Layout::create();
    layout2->setSize(windowSize);
    layout2->setBackGroundImage("esp2_page2.png");
    layout2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pageView->addPage(layout2);

    auto layout3 = Layout::create();
    layout3->setSize(windowSize);
    layout3->setBackGroundImage("esp2_page3.png");
    layout3->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pageView->addPage(layout3);

    auto layout4 = Layout::create();
    layout4->setSize(windowSize);
    layout4->setBackGroundImage("esp2_page4.png");
    layout4->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    pageView->addPage(layout4);

    auto layout5 = Layout::create();
    layout5->setSize(windowSize);
    layout5->setBackGroundImage("esp2_page5.png");
    layout5->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto battle = Button::create("Button_battle.png");
    battle->setPosition(Point(layout5->getSize().width/2+200, layout5->getSize().height*2/5));
    battle->addClickEventListener(CC_CALLBACK_1(TeachPracticeScene::battle_bt, this));
    layout5->addChild(battle);
    // add the transition function event
    auto cancel = Button::create("Button_cancel.png");
    cancel->setPosition(Point(layout5->getSize().width/2-200, layout5->getSize().height*2/5));
    cancel->addClickEventListener(CC_CALLBACK_1(TeachPracticeScene::tranToStory, this));
    layout5->addChild(cancel);

    pageView->addPage(layout5);
    log("end");

    sprite->addChild(pageView);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void TeachPracticeScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
    if( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
        CCLOG("You pressed back button");
        auto scene = Scene::create();
        scene->addChild(TeachScene::create());
        Director::getInstance()->replaceScene(scene);
    }
}

void TeachPracticeScene::tranToStory(Ref* pSender){
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachScene::create());

    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);

}
void TeachPracticeScene::battle_bt(Ref* pSender){

    auto scene = Scene::create();
    SpongeScene *layer = SpongeScene::create();
    layer->init();
    scene->addChild(layer);

    auto transitions = TransitionFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);
}

void TeachPracticeScene::menuCloseCallback(Ref* pSender)
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
