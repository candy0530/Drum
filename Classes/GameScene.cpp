#include "TeachScene.h"
#include "GameScene.h"
#include "SpongeScene.h"
#include "DataG.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

extern int data_mode;
extern int data_stage;

int ccc;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    data_mode = 1;
    data_stage = 1;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("NSMB.mp3",true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("game_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto back = Button::create("Button_back.png");
    back->setPosition(Vec2(180, 180));
    back->addClickEventListener(CC_CALLBACK_1(GameScene::backtomain, this));

    auto img = ImageView::create("main_game_button.png");
    img->setPosition(Vec2(340, 1780));

    // create the pageview
    auto pageView = PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(windowSize);

    // add the layouts
    for( int i = 1; i < 6; i++ ){
        std::stringstream ss;
        ss << i;
        auto layout = Layout::create();
        layout->setSize(windowSize);
        layout->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        auto button = Button::create("Game_cast_page" + ss.str() + ".png");
        button->setAnchorPoint(Point::ANCHOR_MIDDLE);
        button->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2));
        button->setScale(1.0f);
        button->addClickEventListener(CC_CALLBACK_1(GameScene::tranToBattle, this)); // add the transition function event
        layout->addChild(button);

        pageView->addPage(layout);
    }
    pageView->addEventListenerPageView(this, pagevieweventselector(GameScene::pageviewCallBack));

    sprite->addChild(pageView);
    sprite->addChild(back);
    sprite->addChild(img);
    this->addChild(sprite, 0);


    return true;
}

void GameScene::pageviewCallBack(Ref* sender, PageViewEventType type){
    if(type == PAGEVIEW_EVENT_TURNING){
        auto pageView = dynamic_cast<PageView*>(sender);
        log("%ld", pageView->getCurPageIndex() + 1);
        data_mode = 1;
        data_stage = pageView->getCurPageIndex() + 1;
    }
}

void GameScene::tranToBattle(Ref* pSender){

    log("Game click %d",++ccc);

    auto scene = Scene::create();
    SpongeScene *layer = SpongeScene::create();
    scene->addChild(layer);

    auto transitions = TransitionFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);

}

void GameScene::backtomain(Ref* pSender){
    auto scene = Scene::create();
    scene->addChild(MainScene::create());
    auto transitions = TransitionFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);
}

void GameScene::menuCloseCallback(Ref* pSender)
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
