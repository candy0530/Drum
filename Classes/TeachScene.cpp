#include "TeachScene.h"
#include "TeachBasicIntroScene.h"
#include "TeachHowToPlayScene.h"
#include "TeachPracticeScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

extern int data_mode;
extern int data_stage;

Scene* TeachScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TeachScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TeachScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    data_stage = 1;

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("NSMB.mp3",true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("teach_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto back = Button::create("Button_back.png");
    back->setPosition(Vec2(180, 180));
    back->addClickEventListener(CC_CALLBACK_1(TeachScene::backtomain, this));
    
    auto img = ImageView::create("main_teach_button.png");
    img->setPosition(Vec2(340, 1780));

    // create the pageview
    auto pageView = PageView::create();
    pageView->setTouchEnabled(true);
    pageView->setSize(windowSize);

    // first stage
    auto layout1 = Layout::create();
    layout1->setSize(windowSize);
    layout1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    log("layout1 h:%f,w:%f",visibleSize.height,visibleSize.width);

    // imageView
    auto button1 = Button::create("stage0.png");
    button1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button1->setPosition(Point(layout1->getSize().width / 2, layout1->getSize().height / 2));
    button1->setScale(1.0f);
    button1->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachOne, this)); // add the transition function event
    layout1->addChild(button1);
    pageView->addPage(layout1);

    // second stage
    auto layout2 = Layout::create();
    layout2->setSize(windowSize);
    layout2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button2 = Button::create("stage1.png");
    button2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button2->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button2->setScale(1.0f);
    button2->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachOne, this)); // add the transition function event
    layout2->addChild(button2);
    pageView->addPage(layout2);

    // third stage
    auto layout3 = Layout::create();
    layout3->setSize(windowSize);
    layout3->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button3 = Button::create("stage2.png");
    button3->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button3->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button3->setScale(1.0f);
    button3->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachThreeTeach, this)); // add the transition function event
    layout3->addChild(button3);
    pageView->addPage(layout3);

    auto layout4 = Layout::create();
    layout4->setSize(windowSize);
    layout4->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button4 = Button::create("stage3.png");
    button4->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button4->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button4->setScale(1.0f);
    button4->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout4->addChild(button4);
    pageView->addPage(layout4);

    auto layout5 = Layout::create();
    layout5->setSize(windowSize);
    layout5->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button5 = Button::create("stage4.png");
    button5->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button5->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button5->setScale(1.0f);
    button5->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout5->addChild(button5);
    pageView->addPage(layout5);

    auto layout6 = Layout::create();
    layout6->setSize(windowSize);
    layout6->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button6 = Button::create("stage5.png");
    button6->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button6->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button6->setScale(1.0f);
    button6->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout6->addChild(button6);
    pageView->addPage(layout6);

    auto layout7 = Layout::create();
    layout7->setSize(windowSize);
    layout7->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button7 = Button::create("stage6.png");
    button7->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button7->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button7->setScale(1.0f);
    button7->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout7->addChild(button7);
    pageView->addPage(layout7);

    auto layout8 = Layout::create();
    layout8->setSize(windowSize);
    layout8->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button8 = Button::create("stage7.png");
    button8->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button8->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button8->setScale(1.0f);
    button8->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout8->addChild(button8);
    pageView->addPage(layout8);

    auto layout9 = Layout::create();
    layout9->setSize(windowSize);
    layout9->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // imageView
    auto button9 = Button::create("stage8.png");
    button9->setAnchorPoint(Point::ANCHOR_MIDDLE);
    button9->setPosition(Point(layout2->getSize().width / 2, layout1->getSize().height / 2));
    button9->setScale(1.0f);
    button9->addClickEventListener(CC_CALLBACK_1(TeachScene::tranToTeachTwoIntro, this)); // add the transition function event
    layout9->addChild(button9);
    pageView->addPage(layout9);

    pageView->addEventListenerPageView(this, pagevieweventselector(TeachScene::pageviewCallBack));
    sprite->addChild(pageView);
    sprite->addChild(back);
    sprite->addChild(img);


       /* auto pageView = PageView::create();
        pageView->setTouchEnabled(true);
        pageView->setSize(windowSize);


        for (int i = 0; i < 40; i++) {


            auto layout = Layout::create();
            layout->setSize(windowSize);


            auto imageView = ImageView::create("teach_stage1.png");
            imageView->setAnchorPoint( Point::ANCHOR_BOTTOM_LEFT );
            imageView->setScale(1.5f);
            layout->addChild(imageView);


            auto label = Text::create(StringUtils::format("%d",(i+1)), "fonts/Marker Felt.ttf", 30);
            label->setColor(Color3B(Color3B::BLUE));
            label->setPosition(Point(layout->getSize().width / 2, layout->getSize().height / 2));
            layout->addChild(label);

            pageView->addPage(layout);
        }


        pageView->addEventListenerPageView(this, pagevieweventselector(TeachScene::pageviewCallBack));

        sprite->addChild(pageView);*/


    // add the sprite as a child to this layer
    this->addChild(sprite, 0);



    return true;
}

void TeachScene::pageviewCallBack(Ref* sender, PageViewEventType type){
    if(type == PAGEVIEW_EVENT_TURNING){
        auto pageView = dynamic_cast<PageView*>(sender);
        log("%ld", pageView->getCurPageIndex() + 1);
        data_stage = pageView->getCurPageIndex() + 1;
    }
}

void TeachScene::tranToTeachOne(Ref* sender){
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachBasicIntroScene::create());

    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.6f, scene);
    Director::getInstance()->pushScene(transitions);

}

void TeachScene::tranToTeachTwoIntro(Ref* sender){
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachHowToPlayScene::create());

    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.6f, scene);
    Director::getInstance()->pushScene(transitions);

}

void TeachScene::tranToTeachThreeTeach(Ref* sender){
    // create the next scene
    auto scene = Scene::create();
    scene->addChild(TeachPracticeScene::create());

    log("Enter:");
    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.1f, scene);
    Director::getInstance()->pushScene(transitions);

}

void TeachScene::backtomain(Ref* pSender){
    Director::getInstance()->popScene();
}


void TeachScene::menuCloseCallback(Ref* pSender)
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
