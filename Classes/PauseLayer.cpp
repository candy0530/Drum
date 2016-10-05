/*
 * PauseLayer.cpp
 *
 *  Created on: 2015/6/25
 *      Author: Wei Shang Chieh
 */
#include "GameScene.h"
#include "PlayingScene.h"
#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "TeachScene.h"

USING_NS_CC;

extern int data_pause;
extern int data_mode;

Scene* PauseLayer::createScene(RenderTexture* sqr){
    Scene *m_scene = Scene::create();
    Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    _spr->setPosition(Vec2(540,960));
    _spr->setFlipY(true);
    _spr->setColor(cocos2d::ccGRAY);
    m_scene->addChild(_spr);

    // 'layer' is an autorelease object
    PauseLayer* layerr = PauseLayer::create();
    // add layer as a child to scene
    m_scene->addChild(layerr);
    // return the scene
    return m_scene;
}
bool PauseLayer::init(){

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto windowSize = Director::getInstance()->getWinSize();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Game_Pause_bk.png");
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    Button* resume = Button::create("Game_Pause_resume.png");
    resume->setPosition(Vec2(300,400));
    resume->addClickEventListener(CC_CALLBACK_1(PauseLayer::Resume_bt, this));

    Button* over = Button::create("Game_Pause_over.png");
    over->setPosition(Vec2(300,200));
    over->addClickEventListener(CC_CALLBACK_1(PauseLayer::Over_bt, this));

    sprite->addChild(resume);
    sprite->addChild(over);
    this->addChild(sprite);

    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

    return true;
}

void PauseLayer::Resume_bt(Ref* pSender){

    data_pause = 0;
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    Director::sharedDirector()->popScene();

}

void PauseLayer::Over_bt(Ref* pSender){

    data_pause = 0;

    auto scene = Scene::create();
    if(data_mode==0){
        scene->addChild(TeachScene::create());
    }else{
        scene->addChild(GameScene::create());
    }
    // do the transition effect
    auto transitions = TransitionCrossFade::create(0.2f, scene);
    Director::getInstance()->replaceScene(transitions);
}
